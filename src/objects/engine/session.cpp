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

#include <iostream>
#include <engine/session.hpp>

#include <engine/kernel.hpp>
#include <engine/response.hpp>

#include <boost/asio/read.hpp>
#include <boost/endian/conversion.hpp>

#include <boost/core/ignore_unused.hpp>

#include <boost/algorithm/hex.hpp>

#include <iostream>


namespace engine {
    session::session(const std::shared_ptr<state> &state, boost::asio::ip::tcp::socket socket) : state_(state),
        kernel_(std::make_unique<kernel>(state)),
        socket_(std::move(socket)) {
    }

    response session::on_request(const request &request) const {
        return kernel_->handle(request);
    }

    void session::start() {
        read_header();
    }

    void session::read_header() {
        auto _self = shared_from_this();

        async_read(
            socket_,
            boost::asio::buffer(header_.data(), 4),
            boost::asio::transfer_exactly(4),
            [_self](const boost::system::error_code &error_code, std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);

                if (error_code) {
                    return;
                }

                const auto _data = static_cast<unsigned char const *>(
                    static_cast<void const *>(
                        _self->header_.data()
                    )
                );

                const std::uint32_t _value = boost::endian::load_big_u32(_data);
                _self->read_payload(_value);
            });
    }

    void session::read_payload(const std::uint32_t pending_bytes) {
        auto _self = shared_from_this();

        auto &_buffer = get_buffer();

        async_read(
            socket_,
            boost::asio::buffer(_buffer.storage_.data(), pending_bytes),
            boost::asio::transfer_exactly(pending_bytes),
            [_self](const boost::system::error_code &error_code, std::size_t bytes_transferred) {
                if (error_code) {
                    return;
                }

                _self->on_payload(_self->buffer_offset_, bytes_transferred);
                _self->buffer_offset_++;
                _self->read_header();
            });
    }

    void session::on_payload(const std::size_t offset, const std::size_t bytes) {
        auto _self = shared_from_this();

        auto &_buffer = buffers_[offset];

        std::span _bytes(_buffer.storage_.data(), bytes);
        std::string _printable;
        _printable.reserve(_bytes.size() * 2);
        boost::algorithm::hex(
            reinterpret_cast<const unsigned char *>(_bytes.data()),
            reinterpret_cast<const unsigned char *>(_bytes.data()) + _bytes.size(),
            std::back_inserter(_printable)
        );

        std::cout << _printable << std::endl;

        // post(socket_.get_executor(), [_bytes, _self]() {
        //     // Handle stream of bytes...
        // });
    }

    bool session::buffer_is_last() const {
        return buffer_offset_ == ENGINE_SESSION_BUFFERS_LENGTH;
    }

    buffer &session::get_buffer() {
        if (buffer_is_last()) {
            buffer_offset_ = 0;
        }

        return buffers_[buffer_offset_];
    }
}
