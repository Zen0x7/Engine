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

#ifndef ENGINE_SESSION_HPP
#define ENGINE_SESSION_HPP

#include <engine/kernel.hpp>

#include <memory>

namespace engine {
    /**
     * Session
     */
    class session : public std::enable_shared_from_this<session> {
        /**
         * State
         */
        std::shared_ptr<state> state_;

        /**
         * Kernel
         */
        std::unique_ptr<kernel> kernel_;

    public:
        /**
         * Constructor
         *
         * @param state
         */
        explicit session(const std::shared_ptr<state> &state);

        /**
         * On Request
         *
         * @param request
         * @return
         */
        response on_request(const request & request) const;
    };
}

#endif // ENGINE_SESSION_HPP
