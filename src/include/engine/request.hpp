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

#ifndef ENGINE_REQUEST_HPP
#define ENGINE_REQUEST_HPP

#include <algorithm>
#include <engine/action.hpp>

namespace engine {

    /**
     * Request
     */
    class request {
        /**
         * Action
         */
        action action_ = UNDEFINED;

    public:
        /**
         * Constructor
         *
         * @param action
         */
        explicit request(action action = UNDEFINED);


        /**
         * Get Action
         *
         * @return
         */
        action get_action() const;
    };
}

#endif // ENGINE_REQUEST_HPP
