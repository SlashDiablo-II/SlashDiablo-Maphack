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
        "${CMAKE_CURRENT_SOURCE_DIR}/file_reader.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/file_reader.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/lexer.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/lexer.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/parser.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/parser.h"

        "${CMAKE_CURRENT_SOURCE_DIR}/semantic_analyzer.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/semantic_analyzer.h"
)

add_subdirectory("lexer")
add_subdirectory("parser")
add_subdirectory("semantic_analyzer")
