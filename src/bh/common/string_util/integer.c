/**
 * SlashDiablo Maphack
 * Copyright (C) 2012-2023  SlashDiablo Team
 *
 * This file is part of SlashDiablo Maphack.
 *
 * SlashDiablo Maphack is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Affero General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/**
 * BH
 * Copyright (C) 2011  McGod
 *
 * All rights reserved.
 */

#include "bh/common/string_util/integer.h"

#include <limits.h>
#include <stddef.h>
#include <wchar.h>

#include "bh/common/preprocessor/template/typedef.h"
#include "bh/common/string_util/ascii.h"
#include "bh/common/string_util/internal/integer/from_digit_char_of_base.h"
#include "bh/common/string_util/internal/integer/from_str_to_int.h"
#include "bh/common/string_util/internal/integer/from_str_of_base_to_int.h"
#include "bh/common/string_util/internal/integer/get_base_from_prefix_str.h"
#include "bh/common/string_util/internal/integer/is_digit_char_of_base.h"
#include "bh/common/string_util/internal/integer/is_str_decimal.h"
#include "bh/common/string_util/internal/integer/is_str_hexadecimal.h"
#include "bh/common/string_util/internal/integer/is_str_octal.h"
#include "bh/common/string_util/internal/integer/is_str_of_base.h"

/**
 * External
 */

int* Integer_FromDigitCharOfBase(int* value, char ch, int base) {
  return T_Integer_FromDigitCharOfBase(char)(value, ch, base);
}

int* Integer_FromDigitWCharOfBase(int* value, wchar_t ch, int base) {
  return T_Integer_FromDigitCharOfBase(wchar_t)(value, ch, base);
}

int* Integer_FromStrToInt(int* value, const char* str, size_t length) {
  return T_Integer_FromStrToInt(char, int)(value, str, length);
}

int* Integer_FromWStrToInt(int* value, const wchar_t* str, size_t length) {
  return T_Integer_FromStrToInt(wchar_t, int)(value, str, length);
}

unsigned int* Integer_FromStrToUInt(
    unsigned int* value, const char* str, size_t length) {
  return T_Integer_FromStrToInt(char, unsigned_int)(value, str, length);
}

unsigned int* Integer_FromWStrToUInt(
    unsigned int* value, const wchar_t* str, size_t length) {
  return T_Integer_FromStrToInt(wchar_t, unsigned_int)(value, str, length);
}
int* Integer_FromStrOfBaseToInt(
    int* value, const char* str, size_t length, int base) {
  return T_Integer_FromStrOfBaseToInt(char, int)(value, str, length, base);
}

int* Integer_FromWStrOfBaseToInt(
    int* value, const wchar_t* str, size_t length, int base) {
  return T_Integer_FromStrOfBaseToInt(wchar_t, int)(value, str, length, base);
}

int* Integer_FromStrOfBaseToUInt(
    unsigned int* value, const char* str, size_t length, int base) {
  return T_Integer_FromStrOfBaseToInt(char, unsigned_int)(
      value, str, length, base);
}

int* Integer_FromWStrOfBaseToUInt(
    unsigned int* value, const wchar_t* str, size_t length, int base) {
  return T_Integer_FromStrOfBaseToInt(wchar_t, unsigned_int)(
      value, str, length, base);
}

int* Integer_GetBaseFromPrefixStr(int* base, const char* str, size_t length) {
  return T_Integer_GetBaseFromPrefixStr(char)(base, str, length);
}

int* Integer_GetBaseFromPrefixWStr(
    int* base, const wchar_t* str, size_t length) {
  return T_Integer_GetBaseFromPrefixStr(wchar_t)(base, str, length);
}

int Integer_IsDigitCharOfBase(char ch, int base) {
  return T_Integer_IsDigitCharOfBase(char)(ch, base);
}

int Integer_IsDigitWCharOfBase(wchar_t ch, int base) {
  return T_Integer_IsDigitCharOfBase(wchar_t)(ch, base);
}

int Integer_IsStrDecimal(const char* str, size_t length) {
  return T_Integer_IsStrDecimal(char)(str, length);
}

int Integer_IsWStrDecimal(const wchar_t* str, size_t length) {
  return T_Integer_IsStrDecimal(wchar_t)(str, length);
}

int Integer_IsStrHexadecimal(const char* str, size_t length) {
  return T_Integer_IsStrHexadecimal(char)(str, length);
}

int Integer_IsWStrHexadecimal(const wchar_t* str, size_t length) {
  return T_Integer_IsStrHexadecimal(wchar_t)(str, length);
}

int Integer_IsStrOctal(const char* str, size_t length) {
  return T_Integer_IsStrOctal(char)(str, length);
}

int Integer_IsWStrOctal(const wchar_t* str, size_t length) {
  return T_Integer_IsStrOctal(wchar_t)(str, length);
}

int Integer_IsStrOfBase(const char* str, size_t length, int base) {
  return T_Integer_IsStrOfBase(char)(str, length, base);
}

int Integer_IsWStrOfBase(const wchar_t* str, size_t length, int base) {
  return T_Integer_IsStrOfBase(wchar_t)(str, length, base);
}
