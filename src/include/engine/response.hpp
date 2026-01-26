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

#ifndef ENGINE_RESPONSE_HPP
#define ENGINE_RESPONSE_HPP

#include <cstdint>
#include <vector>

namespace engine {
    /**
     * Response
     */
    class response {
        /**
         * Resolved
         */
        bool resolved_ = false;

        /**
         * Resolved At
         */
        std::uint64_t resolved_at_ = 0;

        /**
         * Handled
         */
        bool handled_ = false;

        /**
         * Handled At
         */
        std::uint64_t handled_at_ = 0;

        /**
         * Status
         */
        int status_ = 0;
    public:
        /**
         * Mark As Resolved
         */
        void mark_as_resolved();

        /**
         * Mark As Handled
         */
        void mark_as_handled();

        /**
         * Get Resolved
         *
         * @return
         */
        [[nodiscard]] bool get_resolved() const;

        /**
         * Get Resolved At
         *
         * @return
         */
        [[nodiscard]] std::uint64_t get_resolved_at() const;

        /**
         * Get Handled
         *
         * @return
         */
        [[nodiscard]] bool get_handled() const;

        /**
         * Get Handled At
         *
         * @return
         */
        [[nodiscard]] std::uint64_t get_handled_at() const;

        /**
         * Get Status
         *
         * @return
         */
        [[nodiscard]] int get_status() const;

        /**
         * Set Status
         *
         * @param status
         */
        void set_status(int status);

        /**
         * To Binary
         *
         * @return
         */
        [[nodiscard]] std::vector<std::byte> to_binary() const;
    };
}

#endif // ENGINE_RESPONSE_HPP
