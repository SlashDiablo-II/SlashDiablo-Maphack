# SlashDiablo Maphack
# Copyright (C) 2012-2022  SlashDiablo Team
#
# This file is part of SlashDiablo Maphack.
#
# SlashDiablo Maphack is free software: you can redistribute it
# and/or modify it under the terms of the GNU Affero General Public
# License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public
# License along with this program.  If not, see
# <http://www.gnu.org/licenses/>.

target_sources(${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/assign_statement.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/assign_statement.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/const_expr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/const_expr.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/const_expr_type.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/const_expr_type.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/key_expr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/key_expr.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/parser_line.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/parser_line.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/parser_line_type.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/parser_line_type.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/subscript.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/subscript.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/toggle_expr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/toggle_expr.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/value_expr.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/value_expr.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/value_expr_type.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/value_expr_type.h"
)
