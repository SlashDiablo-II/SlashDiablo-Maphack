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

/**
 * BH
 * Copyright (C) 2011  McGod
 *
 * All rights reserved.
 */

#ifndef BH_D2_STORM_FUNCTION_V1_00_FILE_GET_FILE_SIZE_HPP_
#define BH_D2_STORM_FUNCTION_V1_00_FILE_GET_FILE_SIZE_HPP_

#include <stdint.h>
#include <windows.h>

namespace bh::d2::storm::v1_00 {

uint32_t SFileGetFileSize(HANDLE file, uint32_t* file_size_high);

}  // namespace bh::d2::storm::v1_00

#endif  // BH_D2_STORM_FUNCTION_V1_00_FILE_GET_FILE_SIZE_HPP_
