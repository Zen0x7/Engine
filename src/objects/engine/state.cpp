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

#include <engine/state.hpp>

#include <boost/uuid/random_generator.hpp>

namespace engine {
    state::state() : id_(boost::uuids::random_generator()()) { }

    boost::uuids::uuid state::get_id() const {
        return id_;
    }

    const std::unordered_map<action, callback> & state::get_actions() const {
        return actions_;
    }

    void state::push_action(const action action, callback callback) {
        actions_[action] = std::move(callback);
    }

    void state::set_port(const unsigned short port) {
        port_.store(port, std::memory_order_release);
    }

    unsigned short state::get_port() const {
        return port_.load(std::memory_order_acquire);
    }
}
