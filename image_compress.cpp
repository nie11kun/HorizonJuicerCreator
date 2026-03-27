#include "image_compress.h"

#include <libimagequant.h>
#include <png.h>
#include <zlib.h>

#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

namespace ImageCompress {

// ─────────────────────────────────────────────────────────────
//  内存写入回调，供 libpng 使用
// ─────────────────────────────────────────────────────────────
struct PngWriteBuffer {
    std::vector<unsigned char> data;
};

static void pngWriteCallback(png_structp png, png_bytep buf, png_size_t size) {
    auto *buffer = reinterpret_cast<PngWriteBuffer *>(png_get_io_ptr(png));
    buffer->data.insert(buffer->data.end(), buf, buf + size);
}

static void pngFlushCallback(png_structp) {}

// ─────────────────────────────────────────────────────────────
//  将量化后的调色板图像编码为 PNG 并写入文件
// ─────────────────────────────────────────────────────────────
static bool writePalettePng(
    const unsigned char *indexedPixels,   // 每像素 1 字节，调色板索引
    const liq_palette   *palette,          // libimagequant 调色板
    int width, int height,
    const std::string &filePath)
{
    // ── libpng 初始化 ─────────────────────────────────────────
    png_structp png = png_create_write_struct(
        PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) return false;

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        return false;
    }

    // 先写到内存，成功后再落盘，避免写到一半的损坏文件
    PngWriteBuffer buffer;
    png_set_write_fn(png, &buffer, pngWriteCallback, pngFlushCallback);

    // ── 压缩参数：最大无损压缩调色板数据 ─────────────────────
    png_set_compression_level(png, 9);
    png_set_filter(png, PNG_FILTER_TYPE_BASE, PNG_ALL_FILTERS);
    png_set_compression_strategy(png, Z_DEFAULT_STRATEGY);

    // ── 写 PNG 头：调色板类型（PNG_COLOR_TYPE_PALETTE）────────
    png_set_IHDR(png, info,
                 static_cast<png_uint_32>(width),
                 static_cast<png_uint_32>(height),
                 8,
                 PNG_COLOR_TYPE_PALETTE,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    // ── 填充调色板和透明度 ────────────────────────────────────
    int colorCount = static_cast<int>(palette->count);

    png_color pngPalette[256];
    png_byte  pngTrans[256];
    bool      hasTransparency = false;

    for (int i = 0; i < colorCount; ++i) {
        pngPalette[i].red   = palette->entries[i].r;
        pngPalette[i].green = palette->entries[i].g;
        pngPalette[i].blue  = palette->entries[i].b;
        pngTrans[i]         = palette->entries[i].a;
        if (palette->entries[i].a < 255) hasTransparency = true;
    }

    png_set_PLTE(png, info, pngPalette, colorCount);
    if (hasTransparency) {
        png_set_tRNS(png, info, pngTrans, colorCount, nullptr);
    }

    png_write_info(png, info);

    // ── 逐行写入索引像素 ──────────────────────────────────────
    for (int y = 0; y < height; ++y) {
        const unsigned char *row = indexedPixels + y * width;
        png_write_row(png, const_cast<png_bytep>(row));
    }

    png_write_end(png, info);
    png_destroy_write_struct(&png, &info);

    // ── 落盘 ──────────────────────────────────────────────────
    FILE *fp = std::fopen(filePath.c_str(), "wb");
    if (!fp) return false;
    std::fwrite(buffer.data.data(), 1, buffer.data.size(), fp);
    std::fclose(fp);

    return true;
}

// ─────────────────────────────────────────────────────────────
//  对外接口：PNG 有损压缩
// ─────────────────────────────────────────────────────────────
bool savePngLossy(const unsigned char *pixels,
                  int width, int height,
                  const std::string &filePath,
                  int quality)
{
    // ── 1. 初始化 libimagequant ───────────────────────────────
    liq_attr *attr = liq_attr_create();
    if (!attr) return false;

    // quality 范围：最低值越高 = 压缩越激进；最高值控制质量上限
    // 例如 quality=85 → liq_set_quality(attr, 70, 85)
    int qMin = std::max(0, quality - 15);
    liq_set_quality(attr, qMin, quality);

    // 最大颜色数：256 是调色板 PNG 上限
    liq_set_max_colors(attr, 256);

    // ── 2. 创建图像对象（输入为 RGBA，每像素 4 字节）─────────
    liq_image *image = liq_image_create_rgba(
        attr, pixels, width, height, 0);
    if (!image) {
        liq_attr_destroy(attr);
        return false;
    }

    // ── 3. 量化：生成最优调色板 ──────────────────────────────
    liq_result *result = nullptr;
    liq_error err = liq_image_quantize(image, attr, &result);
    if (err != LIQ_OK) {
        std::cerr << "libimagequant quantize error: " << err << std::endl;
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return false;
    }

    // 抖动强度：1.0 = 最高（视觉效果最好），0.0 = 无抖动
    liq_set_dithering_level(result, 1.0f);

    // ── 4. 将 RGBA 映射为调色板索引 ──────────────────────────
    std::vector<unsigned char> indexedPixels(
        static_cast<size_t>(width) * height);

    err = liq_write_remapped_image(
        result, image, indexedPixels.data(),
        indexedPixels.size());
    if (err != LIQ_OK) {
        liq_result_destroy(result);
        liq_image_destroy(image);
        liq_attr_destroy(attr);
        return false;
    }

    // ── 5. 取出调色板，编码为 PNG ─────────────────────────────
    const liq_palette *palette = liq_get_palette(result);
    bool ok = writePalettePng(
        indexedPixels.data(), palette, width, height, filePath);

    // ── 6. 释放资源 ───────────────────────────────────────────
    liq_result_destroy(result);
    liq_image_destroy(image);
    liq_attr_destroy(attr);

    return ok;
}

} // namespace ImageCompress
