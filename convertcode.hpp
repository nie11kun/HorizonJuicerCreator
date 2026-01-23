/**
 * @file convertcode.hpp
 * @brief Character encoding conversion utilities header
 * @author Marco Nie
 * @date 2018
 * @copyright Copyright © 2018-2024 Marco Nie. All rights reserved.
 */

#ifndef CONVERTCODE_HPP
#define CONVERTCODE_HPP

#include <string>

/**
 * @class ConvertCode
 * @brief Utility class for character encoding conversions
 *
 * Provides methods for converting between Unicode, UTF-8, and GBK encodings.
 * Windows-specific implementations use Win32 API.
 */
class ConvertCode {
public:
  ConvertCode();
  ~ConvertCode();

  /**
   * @brief Convert Unicode (wstring) to UTF-8 string
   * @param ws Wide string in Unicode encoding
   * @return UTF-8 encoded string
   */
  std::string UnicodeToUTF8(const std::wstring &ws);

  /**
   * @brief Convert GBK string to UTF-8
   * @param input GBK encoded string
   * @return UTF-8 encoded string
   */
  std::string GBKToUTF8(const std::string input);

  /**
   * @brief Convert UTF-8 string to GBK
   * @param input UTF-8 encoded string
   * @return GBK encoded string
   */
  std::string UTF8ToGBK(const std::string input);
};

#endif // CONVERTCODE_HPP
