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

#ifndef BH_COMMON_DATA_STRUCT_RED_BLACK_TREE_RED_BLACK_COLOR_H_
#define BH_COMMON_DATA_STRUCT_RED_BLACK_TREE_RED_BLACK_COLOR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

enum RedBlackColor {
  RedBlackColor_kUnspecified = 0,

  RedBlackColor_kRed = 1,
  RedBlackColor_kBlack = 2,
  RedBlackColor_kDoubleBlack = 3
};

const char* RedBlackColor_GetDisplayName(
    enum RedBlackColor color, size_t* length);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* BH_COMMON_DATA_STRUCT_RED_BLACK_TREE_RED_BLACK_COLOR_H_ */