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

#include <iostream>

using namespace engine;

TEST(kernel_test, it_can_be_instanced) {
  const auto _state = std::make_shared<state>();
  const auto _kernel = std::make_shared<kernel>(_state);

  ASSERT_NE(_state->get_id(), _kernel->get_id());
  ASSERT_EQ(_state->get_id(), _kernel->get_state()->get_id());
}

TEST(kernel_test, it_can_handle_requests) {
  const auto _state = std::make_shared<state>();
  const auto _kernel = std::make_shared<kernel>(_state);

  constexpr request _request;
  const auto _response = _kernel->handle(_request);
  ASSERT_TRUE(_response.get_resolved());
}

TEST(kernel_test, it_can_be_benchmarked) {
  const auto _state = std::make_shared<state>();
  const auto _kernel = std::make_shared<kernel>(_state);
  constexpr request _request;


  const auto _start_at = std::chrono::high_resolution_clock::now().time_since_epoch().count();

  auto ITERATIONS = 1'000'000;

  for (auto _i = 0; _i < ITERATIONS; _i++) {
    _kernel->handle(_request);
  }

  const auto _finished_at = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  const auto _time_spent = _finished_at - _start_at;

  std::cout << "CPU time used: " << _time_spent << " nanoseconds" << std::endl;

  const double _it_per_seconds = ITERATIONS * (1'000'000'000 / _time_spent);

  std::cout << "Iterations: " << std::fixed << std::setprecision(0) << _it_per_seconds << " per second" << std::endl;

}