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

#include <engine/action.hpp>
#include <span>
#include <vector>
#include <boost/uuid/random_generator.hpp>

#include <boost/uuid/uuid.hpp>

namespace engine {

    /**
     * Request
     */
    class request {
        /**
         * ID
         */
        boost::uuids::uuid id_;

        /**
         * Action
         */
        action action_ = UNDEFINED;

        /**
         * Fields
         */
        std::vector<std::span<const std::byte>> fields_;

    public:
        /**
         * Constructor
         *
         * @param action
         * @param id
         */
        explicit request(action action = UNDEFINED, boost::uuids::uuid id = boost::uuids::random_generator()());

        /**
         * Get ID
         *
         * @return
         */
        [[nodiscard]] boost::uuids::uuid get_id() const;

        /**
         * Get Action
         *
         * @return
         */
        [[nodiscard]] action get_action() const;

        /**
         * Get Fields
         *
         * @return
         */
        [[nodiscard]] std::vector<std::span<const std::byte>> &get_fields();

        /**
         * From Binary
         *
         * @param data
         * @return
         */
        static request from_binary(std::span<const std::byte> data);

        /**
         * To Binary
         *
         * @return
         */
        [[nodiscard]] std::vector<std::byte> to_binary() const;
    };
}

#endif // ENGINE_REQUEST_HPP
