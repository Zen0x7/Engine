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

#include <engine/server.hpp>
#include <engine/state.hpp>

using namespace engine;

TEST(server_test, it_can_be_instanced) {
    const auto _state = std::make_shared<state>();
    const auto _a = std::make_shared<server>(_state);
    const auto _b = std::make_shared<server>(_state);
    ASSERT_EQ(_a->get_state()->get_id(), _state->get_id());
    ASSERT_EQ(_a->get_state()->get_id(), _b->get_state()->get_id());
}
