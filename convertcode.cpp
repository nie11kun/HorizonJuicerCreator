/**
 * @file convertcode.cpp
 * @brief Character encoding conversion utilities implementation
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#include "convertcode.hpp"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

ConvertCode::ConvertCode() {}

ConvertCode::~ConvertCode() {}

string ConvertCode::UnicodeToUTF8(const wstring &ws) {
  string result;
  for (size_t i = 0; i < ws.size(); ++i) {
    wchar_t wc = ws[i];

    // 1-byte UTF-8 (ASCII)
    if (0 <= wc && wc <= 0x7f) {
      result += static_cast<char>(wc);
    }
    // 2-byte UTF-8
    else if (0x80 <= wc && wc <= 0x7ff) {
      result += static_cast<char>(0xc0 | (wc >> 6));
      result += static_cast<char>(0x80 | (wc & 0x3f));
    }
    // 3-byte UTF-8
    else if (0x800 <= wc && wc <= 0xffff) {
      result += static_cast<char>(0xe0 | (wc >> 12));
      result += static_cast<char>(0x80 | ((wc >> 6) & 0x3f));
      result += static_cast<char>(0x80 | (wc & 0x3f));
    }
    // 4-byte UTF-8
    else if (0x10000 <= wc && wc <= 0x1fffff) {
      result += static_cast<char>(0xf0 | (wc >> 18));
      result += static_cast<char>(0x80 | ((wc >> 12) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 6) & 0x3f));
      result += static_cast<char>(0x80 | (wc & 0x3f));
    }
    // 5-byte UTF-8 (rarely used)
    else if (0x200000 <= wc && wc <= 0x3ffffff) {
      result += static_cast<char>(0xf8 | (wc >> 24));
      result += static_cast<char>(0x80 | ((wc >> 18) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 12) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 6) & 0x3f));
      result += static_cast<char>(0x80 | (wc & 0x3f));
    }
    // 6-byte UTF-8 (rarely used)
    else if (0x4000000 <= wc && wc <= 0x7fffffff) {
      result += static_cast<char>(0xfc | (wc >> 30));
      result += static_cast<char>(0x80 | ((wc >> 24) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 18) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 12) & 0x3f));
      result += static_cast<char>(0x80 | ((wc >> 6) & 0x3f));
      result += static_cast<char>(0x80 | (wc & 0x3f));
    }
  }
  return result;
}

string ConvertCode::GBKToUTF8(const string input) {
#ifdef _WIN32
  const char *strGBK = input.c_str();

  // Convert GBK to Unicode (UTF-16)
  int wideLen = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
  wchar_t *wideStr = new wchar_t[wideLen + 1];
  memset(wideStr, 0, (wideLen + 1) * sizeof(wchar_t));
  MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wideStr, wideLen);

  // Convert Unicode to UTF-8
  int utf8Len =
      WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
  char *utf8Str = new char[utf8Len + 1];
  memset(utf8Str, 0, utf8Len + 1);
  WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, utf8Len, NULL, NULL);

  string result = utf8Str;
  delete[] wideStr;
  delete[] utf8Str;
  return result;
#else
  return input;
#endif
}

string ConvertCode::UTF8ToGBK(const string input) {
#ifdef _WIN32
  const char *strUTF8 = input.c_str();

  // Convert UTF-8 to Unicode (UTF-16)
  int wideLen = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
  wchar_t *wideStr = new wchar_t[wideLen + 1];
  memset(wideStr, 0, (wideLen + 1) * sizeof(wchar_t));
  MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wideStr, wideLen);

  // Convert Unicode to GBK
  int gbkLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
  char *gbkStr = new char[gbkLen + 1];
  memset(gbkStr, 0, gbkLen + 1);
  WideCharToMultiByte(CP_ACP, 0, wideStr, -1, gbkStr, gbkLen, NULL, NULL);

  string result(gbkStr);
  delete[] wideStr;
  delete[] gbkStr;
  return result;
#else
  return input;
#endif
}
