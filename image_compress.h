#pragma once
#include <string>

namespace ImageCompress {

/**
 * PNG 有损压缩保存
 * 使用 libimagequant 对图像做调色板量化（和 tinypng 同类算法）
 * 再用 libpng 无损编码调色板 PNG，体积可达原来的 30~50%
 *
 * @param pixels    RGBA 原始像素数据（每像素 4 字节）
 * @param width     图像宽度
 * @param height    图像高度
 * @param filePath  输出文件路径
 * @param quality   量化质量 0~100，建议 75~90
 * @return true 成功
 */
bool savePngLossy(const unsigned char *pixels,
                  int width, int height,
                  const std::string &filePath,
                  int quality = 85);

} // namespace ImageCompress
