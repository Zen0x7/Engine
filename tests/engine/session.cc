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

#include <gtest/gtest.h>

#include <engine/kernel.hpp>

#include <engine/state.hpp>

#include <engine/request.hpp>
#include <engine/response.hpp>
#include <engine/session.hpp>

#include <iostream>

using namespace engine;

TEST(session_test, it_can_handle_requests) {
    const auto _state = std::make_shared<state>();

    _state->push_action(PING, [](const request &request, response &response, std::shared_ptr<state> state) {
        response.set_status(200);
    });

    const auto _session = std::make_shared<session>(_state);

    const request _request(PING);
    const auto _response = _session->on_request(_request);

    ASSERT_EQ(_response.get_status(), 200);
    ASSERT_NE(_response.get_status(), 0);
    ASSERT_TRUE(_response.get_handled());
    ASSERT_GT(_response.get_handled_at(), 0);
}
