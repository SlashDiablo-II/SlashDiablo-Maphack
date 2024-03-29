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

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "bh/common/string_util/integer.h"

static const char kDigitChars[] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
  'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
  'u', 'v', 'w', 'x', 'y', 'z'
};

enum {
  kDigitCharCount = sizeof(kDigitChars) / sizeof(kDigitChars[0])
};

static void BeforeAllSetUp(void) {}

struct EachContext {
  unsigned char unused;
};

typedef void TestFunc(struct EachContext* context);

static void BeforeEach(struct EachContext* context) {}

static void AfterEach(struct EachContext* context) {}

static void FromDigitCharOfBase_DigitChars_Converted(struct EachContext* context) {
  size_t i;

  for (i = 0; i < kDigitCharCount; ++i) {
    int* value_convert_result;
    int value;

    value_convert_result =
        Integer_FromDigitCharOfBase(&value, kDigitChars[i], kDigitCharCount);

    assert(value_convert_result != NULL);
    assert(value == i);
  }
}

static void FromDigitCharOfBase_InvalidBase_ReturnsNull(
    struct EachContext* context) {
  int value;
  int* value_convert_result;

  value_convert_result = Integer_FromDigitCharOfBase(&value, '0', 9999);

  assert(value_convert_result == NULL);
}

static void FromDigitCharOfBase_OutOfBaseRange_ReturnsNull(
    struct EachContext* context) {
  int value;
  int* value_convert_result;

  value_convert_result = Integer_FromDigitCharOfBase(&value, '9', 8);

  assert(value_convert_result == NULL);
}

static void FromStrToInt_Decimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 42);
}

static void FromStrToInt_NegativeDecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == -42);
}

static void FromStrToInt_MaxDecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "%d", INT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MAX);
}

static void FromStrToInt_MinDecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "%d", INT_MIN);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MIN);
}

static void FromStrToInt_Octal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 042);
}

static void FromStrToInt_NegativeOctal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == -042);
}

static void FromStrToInt_MaxOctal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "0%o", INT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MAX);
}

static void FromStrToInt_MinOctal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "-0%o", INT_MIN);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MIN);
}

static void FromStrToInt_Hexadecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrToInt_NegativeHexadecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == -0x42);
}

static void FromStrToInt_MaxHexadecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "0x%X", INT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MAX);
}

static void FromStrToInt_MinHexadecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "-0x%x", INT_MIN);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MIN);
}

static void FromStrToInt_Empty_ReturnsNull(
    struct EachContext* context) {
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, "", 0);

  assert(result == NULL);
}

static void FromStrToInt_InvalidChars_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "Hello world!";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToInt_NotInDecimalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "1000a";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToInt_NotInOctalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0888";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToInt_NotInHexadecimalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x00G";
  int value;
  int* result;

  result = Integer_FromStrToInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToInt_OutOfMinRange_ReturnsNull(
    struct EachContext* context) {
  enum {
    kStrCapacity = 1024
  };
  size_t i;
  char str[kStrCapacity];
  int value;
  int* result;

  memset(str, '9', kStrCapacity - 1);
  str[0] = '-';
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result == NULL);
}

static void FromStrToInt_OutOfMaxRange_ReturnsNull(
    struct EachContext* context) {
  enum {
    kStrCapacity = 1024
  };
  size_t i;
  char str[kStrCapacity];
  int value;
  int* result;

  memset(str, '9', kStrCapacity - 1);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToInt(&value, str, strlen(str));

  assert(result == NULL);
}

static void FromStrToUInt_Decimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 42u);
}

static void FromStrToUInt_MaxDecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "%u", UINT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToUInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == UINT_MAX);
}

static void FromStrToUInt_MinDecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 0u);
}

static void FromStrToUInt_Octal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 042u);
}

static void FromStrToUInt_MaxOctal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "0%o", UINT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToUInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == UINT_MAX);
}

static void FromStrToUInt_MinOctal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrToUInt_Hexadecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrToUInt_MaxHexadecimal_Converted(
    struct EachContext* context) {
  enum {
    kStrCapacity = 128
  };
  char str[kStrCapacity];
  int value;
  int* result;

  _snprintf(str, kStrCapacity, "0x%X", INT_MAX);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToUInt(&value, str, strlen(str));

  assert(result != NULL);
  assert(value == INT_MAX);
}

static void FromStrToUInt_MinHexadecimal_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrToUInt_Empty_ReturnsNull(
    struct EachContext* context) {
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, "", 0);

  assert(result == NULL);
}

static void FromStrToUInt_InvalidChars_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "Hello world!";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NegativeDecimal_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NegativeOctal_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NegativeHexadecimal_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NotInDecimalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "1000a";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NotInOctalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0888";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_NotInHexadecimalBase_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x00G";
  int value;
  int* result;

  result = Integer_FromStrToUInt(&value, kStr, strlen(kStr));

  assert(result == NULL);
}

static void FromStrToUInt_OutOfMinRange_ReturnsNull(
    struct EachContext* context) {
  enum {
    kStrCapacity = 1024
  };
  size_t i;
  char str[kStrCapacity];
  int value;
  int* result;

  memset(str, '9', kStrCapacity - 1);
  str[0] = '-';
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToUInt(&value, str, strlen(str));

  assert(result == NULL);
}

static void FromStrToUInt_OutOfMaxRange_ReturnsNull(
    struct EachContext* context) {
  enum {
    kStrCapacity = 1024
  };
  size_t i;
  char str[kStrCapacity];
  int value;
  int* result;

  memset(str, '9', kStrCapacity - 1);
  str[kStrCapacity - 1] = '\0';

  result = Integer_FromStrToUInt(&value, str, strlen(str));

  assert(result == NULL);
}

static void FromStrOfBaseToInt_OctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 042);
}

static void FromStrOfBaseToInt_NegativeOctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == -1 * 042);
}

static void FromStrOfBaseToInt_OctalZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "00";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_OctalNegativeZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-00";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_PrefixlessOctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 042);
}

static void FromStrOfBaseToInt_PrefixlessNegativeOctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == -1 * 042);
}

static void FromStrOfBaseToInt_PrefixlessZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_PrefixlessNegativeZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_NonOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "08";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeNonOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-08";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_HexadecimalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeHexadecimalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_DecimalBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == 42);
}

static void FromStrOfBaseToInt_NegativeDecimalBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == -42);
}

static void FromStrOfBaseToInt_DecimalZeroBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_DecimalNegativeZeroBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_OctalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeOctalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_HexadecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeHexadecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NonDecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "a";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeNonDecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-a";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_HexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrOfBaseToInt_NegativeHexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == -1 * 0x42);
}

static void FromStrOfBaseToInt_HexadecimalZeroBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_HexadecimalNegativeZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0x0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_PrefixlessHexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrOfBaseToInt_PrefixlessNegativeHexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == -1 * 0x42);
}

static void FromStrOfBaseToInt_PrefixlessZeroBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_PrefixlessNegativeZeroBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToInt_OctalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeOctalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NonHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0xg";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_NegativeNonHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0xg";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_OnlyHexdecimalPrefixBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_OnlyNegativeHexdecimalPrefixBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_Empty_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_Base0_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 0);

  assert(result == NULL);
}

static void FromStrOfBaseToInt_BaseAbove36_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int value;
  int* result;

  result = Integer_FromStrOfBaseToInt(&value, kStr, strlen(kStr), 37);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 042);
}

static void FromStrOfBaseToUInt_NegativeOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OctalZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "00";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToUInt_OctalNegativeZeroBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-00";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_PrefixlessOctalBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 042);
}

static void FromStrOfBaseToUInt_PrefixlessNegativeOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_PrefixlessZeroBase8_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToUInt_PrefixlessNegativeZeroBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NonOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "08";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeNonOctalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-08";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_HexadecimalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeHexadecimalBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 8);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_DecimalBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == 42);
}

static void FromStrOfBaseToUInt_NegativeDecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_DecimalZeroBase10_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToUInt_DecimalNegativeZeroBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OctalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeOctalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_HexadecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeHexadecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NonDecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "a";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeNonDecimalBase10_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-a";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 10);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_HexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrOfBaseToUInt_NegativeHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_HexadecimalZeroBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0x0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToUInt_HexadecimalNegativeZeroBase8_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_PrefixlessHexadecimalBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0x42);
}

static void FromStrOfBaseToUInt_PrefixlessNegativeHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_PrefixlessZeroBase16_Converted(
    struct EachContext* context) {
  static const char kStr[] = "0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result != NULL);
  assert(value == 0);
}

static void FromStrOfBaseToUInt_PrefixlessNegativeZeroBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OctalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeOctalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NonHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0xg";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_NegativeNonHexadecimalBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0xg";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OnlyHexdecimalPrefixBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "0x";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_OnlyNegativeHexdecimalPrefixBase16_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "-0x";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_Empty_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 16);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_Base0_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 0);

  assert(result == NULL);
}

static void FromStrOfBaseToUInt_BaseAbove36_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "42";
  unsigned int value;
  unsigned int* result;

  result = Integer_FromStrOfBaseToUInt(&value, kStr, strlen(kStr), 37);

  assert(result == NULL);
}

static void GetBaseFromPrefixStr_Octal_Base8(struct EachContext* context) {
  static const char kStr[] = "042";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 8);
}

static void GetBaseFromPrefixStr_NegativeOctal_Base8(
    struct EachContext* context) {
  static const char kStr[] = "-042";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 8);
}

static void GetBaseFromPrefixStr_OctalZero_Base8(struct EachContext* context) {
  static const char kStr[] = "00";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 8);
}

static void GetBaseFromPrefixStr_OctalNegativeZero_Base8(
    struct EachContext* context) {
  static const char kStr[] = "-00";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 8);
}

static void GetBaseFromPrefixStr_Decimal_Base10(struct EachContext* context) {
  static const char kStr[] = "42";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 10);
}

static void GetBaseFromPrefixStr_NegativeDecimal_Base10(
    struct EachContext* context) {
  static const char kStr[] = "-42";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 10);
}

static void GetBaseFromPrefixStr_Zero_Base10(struct EachContext* context) {
  static const char kStr[] = "0";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 10);
}

static void GetBaseFromPrefixStr_NegativeZero_Base10(
    struct EachContext* context) {
  static const char kStr[] = "-0";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 10);
}

static void GetBaseFromPrefixStr_Hexadecimal_Base16(
    struct EachContext* context) {
  static const char kStr[] = "0x42";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 16);
}

static void GetBaseFromPrefixStr_NegativeHexadecimal_Base16(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result != NULL);
  assert(base == 16);
}

static void GetBaseFromPrefixStr_Empty_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, 0);

  assert(base_get_result == NULL);
}

static void GetBaseFromPrefixStr_Missing0Hexadecimal_ReturnsNull(
    struct EachContext* context) {
  static const char kStr[] = "x42";

  int base;
  int* base_get_result;

  base_get_result = Integer_GetBaseFromPrefixStr(&base, kStr, strlen(kStr));

  assert(base_get_result == NULL);
}

static void IsDigitCharOfBase_DigitChars_ReturnsNonZero(
    struct EachContext* context) {
  size_t i;

  for (i = 0; i < kDigitCharCount; ++i) {
    int result;

    result = Integer_IsDigitCharOfBase(kDigitChars[i], 36);

    assert(result);
  }
}

static void IsDigitCharOfBase_Base0_ReturnsZero(
    struct EachContext* context) {
  int result;

  result = Integer_IsDigitCharOfBase('0', 0);

  assert(!result);
}

static void IsDigitCharOfBase_AboveBase36_ReturnsZero(
    struct EachContext* context) {
  int result;

  result = Integer_IsDigitCharOfBase('0', 37);

  assert(!result);
}

static void IsDigitCharOfBase_OutOfBaseRange_ReturnsZero(
    struct EachContext* context) {
  int result;

  result = Integer_IsDigitCharOfBase('8', 8);

  assert(!result);
}

static void IsStrOfBase_OctalBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_NegativeOctalBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_OctalZeroBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "00";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_OctalNegativeZeroBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-00";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_PrefixlessOctalBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_PrefixlessNegativeOctalBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_PrefixlessZeroBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_PrefixlessNegativeZeroBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(result);
}

static void IsStrOfBase_NonOctalBase8_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "08";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(!result);
}

static void IsStrOfBase_NegativeNonOctalBase8_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-08";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(!result);
}

static void IsStrOfBase_HexadecimalBase8_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(!result);
}

static void IsStrOfBase_NegativeHexadecimalBase8_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 8);

  assert(!result);
}

static void IsStrOfBase_DecimalBase10_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(result);
}

static void IsStrOfBase_NegativeDecimalBase10_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(result);
}

static void IsStrOfBase_DecimalZeroBase10_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(result);
}

static void IsStrOfBase_DecimalNegativeZeroBase10_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(result);
}

static void IsStrOfBase_OctalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_NegativeOctalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_HexadecimalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_NegativeHexadecimalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_NonDecimalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "a";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_NegativeNonDecimalBase10_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-a";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_HexadecimalBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_NegativeHexadecimalBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_HexadecimalZeroBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "0x0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_HexadecimalNegativeZeroBase8_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_PrefixlessHexadecimalBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_PrefixlessNegativeHexadecimalBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-42";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_PrefixlessZeroBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_PrefixlessNegativeZeroBase16_ReturnsNonZero(
    struct EachContext* context) {
  static const char kStr[] = "-0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(result);
}

static void IsStrOfBase_OctalBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_NegativeOctalBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-042";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_NonHexadecimalBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "0xG";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_NegativeNonHexadecimalBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-0xG";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_OnlyHexdecimalPrefixBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "0x";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_OnlyNegativeHexdecimalPrefixBase16_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "-0x";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 16);

  assert(!result);
}

static void IsStrOfBase_Empty_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 10);

  assert(!result);
}

static void IsStrOfBase_Base0_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 0);

  assert(!result);
}

static void IsStrOfBase_BaseAbove36_ReturnsZero(
    struct EachContext* context) {
  static const char kStr[] = "0";
  int result;

  result = Integer_IsStrOfBase(kStr, strlen(kStr), 37);

  assert(!result);
}

int main(int argc, char** argv) {
#ifdef NDEBUG

  printf("Tests must run in debug mode, with NDEBUG not defined.\n");

#else

  static TestFunc* const kTests[] = {
    &FromDigitCharOfBase_DigitChars_Converted,
    &FromDigitCharOfBase_InvalidBase_ReturnsNull,
    &FromDigitCharOfBase_OutOfBaseRange_ReturnsNull,

    &FromStrToInt_Decimal_Converted,
    &FromStrToInt_NegativeDecimal_Converted,
    &FromStrToInt_MaxDecimal_Converted,
    &FromStrToInt_MinDecimal_Converted,
    &FromStrToInt_Octal_Converted,
    &FromStrToInt_NegativeOctal_Converted,
    &FromStrToInt_MaxOctal_Converted,
    &FromStrToInt_MinOctal_Converted,
    &FromStrToInt_Hexadecimal_Converted,
    &FromStrToInt_NegativeHexadecimal_Converted,
    &FromStrToInt_MaxHexadecimal_Converted,
    &FromStrToInt_MinHexadecimal_Converted,
    &FromStrToInt_Empty_ReturnsNull,
    &FromStrToInt_InvalidChars_ReturnsNull,
    &FromStrToInt_NotInDecimalBase_ReturnsNull,
    &FromStrToInt_NotInOctalBase_ReturnsNull,
    &FromStrToInt_NotInHexadecimalBase_ReturnsNull,
    &FromStrToInt_OutOfMinRange_ReturnsNull,
    &FromStrToInt_OutOfMaxRange_ReturnsNull,

    &FromStrToUInt_Decimal_Converted,
    &FromStrToUInt_MaxDecimal_Converted,
    &FromStrToUInt_MinDecimal_Converted,
    &FromStrToUInt_Octal_Converted,
    &FromStrToUInt_MaxOctal_Converted,
    &FromStrToUInt_MinOctal_Converted,
    &FromStrToUInt_Hexadecimal_Converted,
    &FromStrToUInt_MaxHexadecimal_Converted,
    &FromStrToUInt_MinHexadecimal_Converted,
    &FromStrToUInt_Empty_ReturnsNull,
    &FromStrToUInt_InvalidChars_ReturnsNull,
    &FromStrToUInt_NegativeDecimal_ReturnsNull,
    &FromStrToUInt_NegativeOctal_ReturnsNull,
    &FromStrToUInt_NegativeHexadecimal_ReturnsNull,
    &FromStrToUInt_NotInDecimalBase_ReturnsNull,
    &FromStrToUInt_NotInOctalBase_ReturnsNull,
    &FromStrToUInt_NotInHexadecimalBase_ReturnsNull,
    &FromStrToUInt_OutOfMinRange_ReturnsNull,
    &FromStrToUInt_OutOfMaxRange_ReturnsNull,

    &FromStrOfBaseToInt_OctalBase8_Converted,
    &FromStrOfBaseToInt_NegativeOctalBase8_Converted,
    &FromStrOfBaseToInt_OctalZeroBase8_Converted,
    &FromStrOfBaseToInt_OctalNegativeZeroBase8_Converted,
    &FromStrOfBaseToInt_PrefixlessOctalBase8_Converted,
    &FromStrOfBaseToInt_PrefixlessNegativeOctalBase8_Converted,
    &FromStrOfBaseToInt_PrefixlessZeroBase8_Converted,
    &FromStrOfBaseToInt_PrefixlessNegativeZeroBase8_Converted,
    &FromStrOfBaseToInt_NonOctalBase8_ReturnsNull,
    &FromStrOfBaseToInt_NegativeNonOctalBase8_ReturnsNull,
    &FromStrOfBaseToInt_HexadecimalBase8_ReturnsNull,
    &FromStrOfBaseToInt_NegativeHexadecimalBase8_ReturnsNull,
    &FromStrOfBaseToInt_DecimalBase10_Converted,
    &FromStrOfBaseToInt_NegativeDecimalBase10_Converted,
    &FromStrOfBaseToInt_DecimalZeroBase10_Converted,
    &FromStrOfBaseToInt_DecimalNegativeZeroBase10_Converted,
    &FromStrOfBaseToInt_OctalBase10_ReturnsNull,
    &FromStrOfBaseToInt_NegativeOctalBase10_ReturnsNull,
    &FromStrOfBaseToInt_HexadecimalBase10_ReturnsNull,
    &FromStrOfBaseToInt_NegativeHexadecimalBase10_ReturnsNull,
    &FromStrOfBaseToInt_NonDecimalBase10_ReturnsNull,
    &FromStrOfBaseToInt_NegativeNonDecimalBase10_ReturnsNull,
    &FromStrOfBaseToInt_HexadecimalBase16_Converted,
    &FromStrOfBaseToInt_NegativeHexadecimalBase16_Converted,
    &FromStrOfBaseToInt_HexadecimalZeroBase16_Converted,
    &FromStrOfBaseToInt_HexadecimalNegativeZeroBase8_Converted,
    &FromStrOfBaseToInt_PrefixlessHexadecimalBase16_Converted,
    &FromStrOfBaseToInt_PrefixlessNegativeHexadecimalBase16_Converted,
    &FromStrOfBaseToInt_PrefixlessZeroBase16_Converted,
    &FromStrOfBaseToInt_PrefixlessNegativeZeroBase16_Converted,
    &FromStrOfBaseToInt_OctalBase16_ReturnsNull,
    &FromStrOfBaseToInt_NegativeOctalBase16_ReturnsNull,
    &FromStrOfBaseToInt_NonHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToInt_NegativeNonHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToInt_OnlyHexdecimalPrefixBase16_ReturnsNull,
    &FromStrOfBaseToInt_OnlyNegativeHexdecimalPrefixBase16_ReturnsNull,
    &FromStrOfBaseToInt_Empty_ReturnsNull,
    &FromStrOfBaseToInt_Base0_ReturnsNull,
    &FromStrOfBaseToInt_BaseAbove36_ReturnsNull,

    &FromStrOfBaseToUInt_OctalBase8_Converted,
    &FromStrOfBaseToUInt_NegativeOctalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_OctalZeroBase8_Converted,
    &FromStrOfBaseToUInt_OctalNegativeZeroBase8_ReturnsNull,
    &FromStrOfBaseToUInt_PrefixlessOctalBase8_Converted,
    &FromStrOfBaseToUInt_PrefixlessNegativeOctalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_PrefixlessZeroBase8_Converted,
    &FromStrOfBaseToUInt_PrefixlessNegativeZeroBase8_ReturnsNull,
    &FromStrOfBaseToUInt_NonOctalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeNonOctalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_HexadecimalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeHexadecimalBase8_ReturnsNull,
    &FromStrOfBaseToUInt_DecimalBase10_Converted,
    &FromStrOfBaseToUInt_NegativeDecimalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_DecimalZeroBase10_Converted,
    &FromStrOfBaseToUInt_DecimalNegativeZeroBase10_ReturnsNull,
    &FromStrOfBaseToUInt_OctalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeOctalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_HexadecimalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeHexadecimalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_NonDecimalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeNonDecimalBase10_ReturnsNull,
    &FromStrOfBaseToUInt_HexadecimalBase16_Converted,
    &FromStrOfBaseToUInt_NegativeHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_HexadecimalZeroBase16_Converted,
    &FromStrOfBaseToUInt_HexadecimalNegativeZeroBase8_ReturnsNull,
    &FromStrOfBaseToUInt_PrefixlessHexadecimalBase16_Converted,
    &FromStrOfBaseToUInt_PrefixlessNegativeHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_PrefixlessZeroBase16_Converted,
    &FromStrOfBaseToUInt_PrefixlessNegativeZeroBase16_ReturnsNull,
    &FromStrOfBaseToUInt_OctalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeOctalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_NonHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_NegativeNonHexadecimalBase16_ReturnsNull,
    &FromStrOfBaseToUInt_OnlyHexdecimalPrefixBase16_ReturnsNull,
    &FromStrOfBaseToUInt_OnlyNegativeHexdecimalPrefixBase16_ReturnsNull,
    &FromStrOfBaseToUInt_Empty_ReturnsNull,
    &FromStrOfBaseToUInt_Base0_ReturnsNull,
    &FromStrOfBaseToUInt_BaseAbove36_ReturnsNull,

    &GetBaseFromPrefixStr_Octal_Base8,
    &GetBaseFromPrefixStr_NegativeOctal_Base8,
    &GetBaseFromPrefixStr_OctalZero_Base8,
    &GetBaseFromPrefixStr_OctalNegativeZero_Base8,
    &GetBaseFromPrefixStr_Decimal_Base10,
    &GetBaseFromPrefixStr_NegativeDecimal_Base10,
    &GetBaseFromPrefixStr_Zero_Base10,
    &GetBaseFromPrefixStr_NegativeZero_Base10,
    &GetBaseFromPrefixStr_Hexadecimal_Base16,
    &GetBaseFromPrefixStr_NegativeHexadecimal_Base16,
    &GetBaseFromPrefixStr_Empty_ReturnsNull,
    &GetBaseFromPrefixStr_Missing0Hexadecimal_ReturnsNull,

    &IsDigitCharOfBase_DigitChars_ReturnsNonZero,
    &IsDigitCharOfBase_Base0_ReturnsZero,
    &IsDigitCharOfBase_AboveBase36_ReturnsZero,
    &IsDigitCharOfBase_OutOfBaseRange_ReturnsZero,

    &IsStrOfBase_OctalBase8_ReturnsNonZero,
    &IsStrOfBase_NegativeOctalBase8_ReturnsNonZero,
    &IsStrOfBase_OctalZeroBase8_ReturnsNonZero,
    &IsStrOfBase_OctalNegativeZeroBase8_ReturnsNonZero,
    &IsStrOfBase_PrefixlessOctalBase8_ReturnsNonZero,
    &IsStrOfBase_PrefixlessNegativeOctalBase8_ReturnsNonZero,
    &IsStrOfBase_PrefixlessZeroBase8_ReturnsNonZero,
    &IsStrOfBase_PrefixlessNegativeZeroBase8_ReturnsNonZero,
    &IsStrOfBase_NonOctalBase8_ReturnsZero,
    &IsStrOfBase_NegativeNonOctalBase8_ReturnsZero,
    &IsStrOfBase_HexadecimalBase8_ReturnsZero,
    &IsStrOfBase_NegativeHexadecimalBase8_ReturnsZero,
    &IsStrOfBase_DecimalBase10_ReturnsNonZero,
    &IsStrOfBase_NegativeDecimalBase10_ReturnsNonZero,
    &IsStrOfBase_DecimalZeroBase10_ReturnsNonZero,
    &IsStrOfBase_DecimalNegativeZeroBase10_ReturnsNonZero,
    &IsStrOfBase_OctalBase10_ReturnsZero,
    &IsStrOfBase_NegativeOctalBase10_ReturnsZero,
    &IsStrOfBase_HexadecimalBase10_ReturnsZero,
    &IsStrOfBase_NegativeHexadecimalBase10_ReturnsZero,
    &IsStrOfBase_NonDecimalBase10_ReturnsZero,
    &IsStrOfBase_NegativeNonDecimalBase10_ReturnsZero,
    &IsStrOfBase_HexadecimalBase16_ReturnsNonZero,
    &IsStrOfBase_NegativeHexadecimalBase16_ReturnsNonZero,
    &IsStrOfBase_HexadecimalZeroBase16_ReturnsNonZero,
    &IsStrOfBase_HexadecimalNegativeZeroBase8_ReturnsNonZero,
    &IsStrOfBase_PrefixlessHexadecimalBase16_ReturnsNonZero,
    &IsStrOfBase_PrefixlessNegativeHexadecimalBase16_ReturnsNonZero,
    &IsStrOfBase_PrefixlessZeroBase16_ReturnsNonZero,
    &IsStrOfBase_PrefixlessNegativeZeroBase16_ReturnsNonZero,
    &IsStrOfBase_OctalBase16_ReturnsZero,
    &IsStrOfBase_NegativeOctalBase16_ReturnsZero,
    &IsStrOfBase_NonHexadecimalBase16_ReturnsZero,
    &IsStrOfBase_NegativeNonHexadecimalBase16_ReturnsZero,
    &IsStrOfBase_OnlyHexdecimalPrefixBase16_ReturnsZero,
    &IsStrOfBase_OnlyNegativeHexdecimalPrefixBase16_ReturnsZero,
    &IsStrOfBase_Empty_ReturnsZero,
    &IsStrOfBase_Base0_ReturnsZero,
    &IsStrOfBase_BaseAbove36_ReturnsZero
  };

  enum {
    kTestsCount = sizeof(kTests) / sizeof(kTests[0])
  };

  size_t i;

  BeforeAllSetUp();

  printf("Running %u test(s).\n", kTestsCount);
  for (i = 0; i < kTestsCount; ++i) {
    struct EachContext context;

    BeforeEach(&context);
    kTests[i](&context);
    AfterEach(&context);
  }
  printf("Ran %u test(s).\n", kTestsCount);

#endif

  return 0;
}
