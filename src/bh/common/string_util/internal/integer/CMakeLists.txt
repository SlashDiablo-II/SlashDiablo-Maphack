# SlashDiablo Maphack
# Copyright (C) 2012-2023  SlashDiablo Team
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
        "${CMAKE_CURRENT_SOURCE_DIR}/from_digit_char_of_base.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_digit_char_of_base.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_digit_char_of_base_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_to_int.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_to_int.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_to_int_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_of_base_to_int.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_of_base_to_int.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/from_str_of_base_to_int_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/get_base_from_prefix_str.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_base_from_prefix_str.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/get_base_from_prefix_str_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/is_digit_char_of_base.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_digit_char_of_base.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_digit_char_of_base_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_decimal.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_decimal.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_decimal_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_hexadecimal.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_hexadecimal.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_hexadecimal_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_octal.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_octal.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_octal_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_of_base.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_of_base.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/is_str_of_base_template.h"
)
