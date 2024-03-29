/**
 * SlashDiablo Maphack
 * Copyright (C) 2012-2022  SlashDiablo Team
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

#ifndef BH_CONFIG_COLONINI_INTERNAL_PARSER_VALUE_EXPR_H_
#define BH_CONFIG_COLONINI_INTERNAL_PARSER_VALUE_EXPR_H_

#include "bh/config/colonini/internal/lexer/lexer_string.h"
#include "bh/config/colonini/internal/parser/const_expr.h"
#include "bh/config/colonini/internal/parser/toggle_expr.h"
#include "bh/config/colonini/internal/parser/value_expr_type.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct ValueExpr {
  enum ValueExprType type;
  union {
    struct ConstExpr as_constexpr;
    struct ToggleExpr as_toggleexpr;
  } variant;
};

/**
 * Starting from begin_src, parses a ValueExpr constituted of tokens
 * and whitespace no further than end_src. Returns a non-NULL on
 * success, or else returns NULL and sets error column.
 */
struct ValueExpr* ValueExpr_Parse(
    struct ValueExpr* expr,
    const struct LexerString* begin_src,
    const struct LexerString* end_src,
    size_t* error_column);

/**
 * Deinitializes a ValueExpr, freeing up resources that were allocated.
 */
void ValueExpr_Deinit(struct ValueExpr* expr);

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif  /* BH_CONFIG_COLONINI_INTERNAL_PARSER_VALUE_EXPR_H_ */