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
        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_char.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_char.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_char_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_str.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_str.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_lower_str_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_char.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_char.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_char_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_str.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_str.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/to_upper_str_template.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/trim_whitespace_chars.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/trim_whitespace_chars.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/trim_whitespace_chars_template.h"
)
