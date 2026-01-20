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

#ifndef ENGINE_STATE_HPP
#define ENGINE_STATE_HPP

#include <memory>
#include <boost/uuid/uuid.hpp>

namespace engine {
    /**
     * State
     */
    class state : public std::enable_shared_from_this<state> {
        /**
         * ID
         */
        boost::uuids::uuid id_;
    public:
        /**
         * Constructor
         */
        state();

        /**
         * Get ID
         *
         * @return
         */
        boost::uuids::uuid get_id() const;
    };
}

#endif // ENGINE_STATE_HPP
