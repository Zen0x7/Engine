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

#include <engine/kernel.hpp>

#include <engine/response.hpp>

#include <boost/uuid/random_generator.hpp>
#include <engine/request.hpp>

#include <engine/state.hpp>

namespace engine {
    kernel::kernel(const std::shared_ptr<state> &state) : id_(boost::uuids::random_generator()()), state_(state) {
    }

    response kernel::handle(const request &request) const {
        response _response;

        const auto _actions = state_->get_actions();

        if (const auto _exists = _actions.contains(request.get_action()); _exists) {
            auto & _action = _actions.at(request.get_action());
            _action(request, _response, state_);
            _response.mark_as_handled();
        }

        _response.mark_as_resolved();

        return _response;
    }

    boost::uuids::uuid kernel::get_id() const {
        return id_;
    }

    std::shared_ptr<state> kernel::get_state() const {
        return state_;
    }
}
