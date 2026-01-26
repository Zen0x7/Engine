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
#include <boost/uuid/uuid_io.hpp>

#include <engine/request.hpp>
#include <engine/serialize.hpp>

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

TEST_F(listener_test, it_can_handle_requests) {
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::socket _socket(_io_context);
    boost::asio::ip::tcp::resolver _resolver{ make_strand(_io_context) };
    const auto _results = _resolver.resolve("localhost", std::to_string(server_->get_state()->get_port()));
    boost::asio::connect(_socket, _results);

    engine::request _join_request(engine::JOIN);
    auto& _join_fields = _join_request.get_fields();
    std::array _id{
        std::byte{0xA2}, std::byte{0xCF}, std::byte{0xAA}, std::byte{0xCF},
        std::byte{0x6E}, std::byte{0xBC}, std::byte{0x4F}, std::byte{0x18},
        std::byte{0x91}, std::byte{0xDF}, std::byte{0x20}, std::byte{0x80},
        std::byte{0x6F}, std::byte{0x0B}, std::byte{0x54}, std::byte{0x2A},
    };
    _join_fields.emplace_back(_id);

    auto _payload = engine::serialize_requests({ _join_request });

    const std::uint32_t _payload_size =
        boost::endian::native_to_big(
            static_cast<std::uint32_t>(_payload.size() - 4)
        );

    std::array<std::byte, 4> _header;
    std::memcpy(_header.data(), &_payload_size, sizeof(_payload_size));

    boost::asio::write(_socket, boost::asio::buffer(_header));
    boost::asio::write(_socket, boost::asio::buffer(_payload));

    std::vector<std::byte> _response(17);
    boost::asio::read(_socket, boost::asio::buffer(_response));

    boost::uuids::uuid _received_id;
    std::memcpy(_received_id.data, _response.data(), 16);
    const uint8_t status = static_cast<uint8_t>(_response[16]);

    ASSERT_EQ(std::byte{ _join_request.get_id().data[0] }, std::byte{ _received_id.data[0] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[1] }, std::byte{ _received_id.data[1] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[2] }, std::byte{ _received_id.data[2] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[3] }, std::byte{ _received_id.data[3] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[4] }, std::byte{ _received_id.data[4] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[5] }, std::byte{ _received_id.data[5] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[6] }, std::byte{ _received_id.data[6] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[7] }, std::byte{ _received_id.data[7] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[8] }, std::byte{ _received_id.data[8] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[9] }, std::byte{ _received_id.data[9] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[10] }, std::byte{ _received_id.data[10] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[11] }, std::byte{ _received_id.data[11] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[12] }, std::byte{ _received_id.data[12] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[13] }, std::byte{ _received_id.data[13] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[14] }, std::byte{ _received_id.data[14] });
    ASSERT_EQ(std::byte{ _join_request.get_id().data[15] }, std::byte{ _received_id.data[15] });
}