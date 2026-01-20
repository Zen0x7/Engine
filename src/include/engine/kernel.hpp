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

#ifndef ENGINE_KERNEL_HPP
#define ENGINE_KERNEL_HPP

#include <memory>
#include <boost/uuid/uuid.hpp>

namespace engine {
    /**
     * Forward State
     */
    class state;

    /**
     * Forward Request
     */
    class request;

    /**
     * Forward Response
     */
    class response;

    /**
     * Kernel
     */
    class kernel {
        /**
         * ID
         */
        boost::uuids::uuid id_;

        /**
         * State
         */
        std::shared_ptr<state> state_;

    public:
        /**
         * Constructor
         *
         * @param state
         */
        explicit kernel(const std::shared_ptr<state> &state);


        /**
         * Handle
         *
         * @param request
         * @return
         */
        response handle(const request & request);

        /**
         * Get ID
         *
         * @return
         */
        boost::uuids::uuid get_id() const;

        /**
         * Get State
         *
         * @return
         */
        std::shared_ptr<state> get_state() const;
    };
}

#endif // ENGINE_KERNEL_HPP
