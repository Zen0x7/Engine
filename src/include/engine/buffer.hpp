// Copyright (C) 2026 Ian Torres
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef ENGINE_BUFFER_HPP
#define ENGINE_BUFFER_HPP

#ifndef ENGINE_BUFFER_SIZE
#define ENGINE_BUFFER_SIZE 65536
#endif

#include <array>

namespace engine {
    /**
     * Buffer
     */
    struct buffer {
        /**
         * Storage
         */
        std::array<std::byte, ENGINE_BUFFER_SIZE> storage_{};

        /**
         * Used
         */
        bool used_ = false;
    };
}

#endif // ENGINE_BUFFER_HPP
