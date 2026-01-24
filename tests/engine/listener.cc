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

#include "listener_test.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

TEST_F(listener_test, it_can_open_a_local_port) {
    ASSERT_NE(server_->get_state()->get_port(), 0);
}

TEST_F(listener_test, it_can_accept_connections) {
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::socket _socket(_io_context);
    boost::asio::ip::tcp::resolver _resolver{ make_strand(_io_context) };
    const auto _results = _resolver.resolve("localhost", std::to_string(server_->get_state()->get_port()));
    boost::asio::connect(_socket, _results);

    ASSERT_TRUE(_socket.is_open());
    ASSERT_TRUE(_socket.remote_endpoint().port() == server_->get_state()->get_port());
}

TEST_F(listener_test, it_can_handle_headers) {
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::socket _socket(_io_context);
    boost::asio::ip::tcp::resolver _resolver{ make_strand(_io_context) };
    const auto _results = _resolver.resolve("localhost", std::to_string(server_->get_state()->get_port()));
    boost::asio::connect(_socket, _results);

    std::array _header { std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x04} };
    boost::asio::write(_socket, boost::asio::buffer(_header));

    std::array _payload { std::byte{0x00}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00} };
    boost::asio::write(_socket, boost::asio::buffer(_payload));

    std::array<std::byte, 2> _response;
    boost::asio::read(_socket, boost::asio::buffer(_response, 2));

    ASSERT_EQ(_response[0], std::byte{ 0x00 });
    ASSERT_EQ(_response[1], std::byte{ 0x01 });
}