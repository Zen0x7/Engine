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

#include <engine/server.hpp>
#include <engine/state.hpp>
#include <engine/listener.hpp>

#include <thread>

namespace engine {
    server::server(const std::shared_ptr<state> &state, const unsigned short port) : state_(state), port_(port) {
    }

    std::shared_ptr<state> server::get_state() const {
        return state_;
    }

    void server::start(const int number_of_threads) {
        auto _endpoint =  boost::asio::ip::tcp::endpoint{
            boost::asio::ip::make_address(
                "0.0.0.0"),
            port_
        };

        const auto _listener = std::make_shared<listener>(io_context_, _endpoint, state_);
        _listener->start();

        std::vector<std::jthread> _threads;
        _threads.reserve(number_of_threads - 1);
        for (int _i = 0; _i < number_of_threads - 1; _i++) {
            _threads.emplace_back([this]() {
                io_context_.run();
            });
        }
        io_context_.run();
    }

    void server::stop() {
        io_context_.stop();
    }
}
