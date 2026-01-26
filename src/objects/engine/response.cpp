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

#include <engine/response.hpp>
#include <chrono>

namespace engine {
    void response::mark_as_resolved() {
        resolved_ = true;
        resolved_at_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    void response::mark_as_handled() {
        handled_ = true;
        handled_at_ = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    bool response::get_resolved() const {
        return resolved_;
    }

    std::uint64_t response::get_resolved_at() const {
        return resolved_at_;
    }

    bool response::get_handled() const {
        return handled_;
    }

    std::uint64_t response::get_handled_at() const {
        return handled_at_;
    }

    int response::get_status() const {
        return status_;
    }

    void response::set_status(const int status) {
        status_ = status;
    }

    std::vector<std::byte> response::to_binary() const {

    }
}
