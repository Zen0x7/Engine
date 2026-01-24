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
#include <queue>
#include <engine/session.hpp>

#include <engine/kernel.hpp>
#include <engine/response.hpp>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/endian/conversion.hpp>

#include <boost/core/ignore_unused.hpp>

#include <boost/algorithm/hex.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <engine/state.hpp>

namespace engine {
    session::session(const std::shared_ptr<state> &state,
                     boost::asio::ip::tcp::socket socket) : id_(boost::uuids::random_generator()()),
                                                            state_(state),
                                                            kernel_(std::make_unique<kernel>(state)),
                                                            socket_(std::move(socket)) {
    }

    session::~session() {
        std::cout << "[" << to_string(id_) << "] session released" << std::endl;
    }

    response session::on_request(const request &request) const {
        return kernel_->handle(request);
    }

    void session::start() {
        read_header();
    }

    boost::uuids::uuid session::get_id() const {
        return id_;
    }

    void session::send(std::shared_ptr<std::vector<std::byte> const> const &data) {
        post(
            socket_.get_executor(),
            boost::beast::bind_front_handler(
                &session::on_send,
                shared_from_this(),
                data));
    }

    void session::read_header() {
        async_read(
            socket_,
            boost::asio::buffer(header_.data(), ENGINE_SESSION_HEADER_LENGTH),
            boost::asio::transfer_exactly(ENGINE_SESSION_HEADER_LENGTH),
            boost::beast::bind_front_handler(&session::on_header, shared_from_this())
        );
    }

    void session::read_payload(const std::uint32_t pending_bytes) {
        auto &_buffer = get_buffer();

        async_read(
            socket_,
            boost::asio::buffer(_buffer.storage_.data(), pending_bytes),
            boost::asio::transfer_exactly(pending_bytes),
            boost::beast::bind_front_handler(&session::on_payload, shared_from_this()));
    }

    void session::handle_payload(const std::size_t offset, const std::size_t bytes) {
        auto &_buffer = buffers_[offset];

        const std::span _bytes(_buffer.storage_.data(), bytes);
        std::string _printable;
        _printable.reserve(_bytes.size() * 2);
        boost::algorithm::hex(
            reinterpret_cast<const unsigned char *>(_bytes.data()),
            reinterpret_cast<const unsigned char *>(_bytes.data()) + _bytes.size(),
            std::back_inserter(_printable)
        );

        std::cout << _printable << std::endl;

        std::vector _response = {std::byte{0x00}, std::byte{0x01}};
        send(std::make_shared<std::vector<std::byte> const>(_response));
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

    void session::on_header(const boost::system::error_code &error_code, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (error_code) {
            state_->remove_session(get_id());
            return;
        }

        const auto _data = static_cast<unsigned char const *>(
            static_cast<void const *>(
                header_.data()
            )
        );

        const std::uint32_t _value = boost::endian::load_big_u32(_data);
        read_payload(_value);
    }

    void session::on_payload(const boost::system::error_code &error_code, const std::size_t bytes_transferred) {
        if (error_code) {
            state_->remove_session(get_id());
            return;
        }

        handle_payload(buffer_offset_, bytes_transferred);
        buffer_offset_++;
        read_header();
    }

    void session::on_send(std::shared_ptr<std::vector<std::byte> const> const &data) {
        queue_.push_back(data);

        if (queue_.size() > 1)
            return;

        async_write(
            socket_,
            boost::asio::buffer(*queue_.front()),
            boost::beast::bind_front_handler(
                &session::on_write,
                shared_from_this()
            ));
    }

    void session::on_write(const boost::system::error_code &error_code, std::size_t bytes_transferred) {
        if (error_code) {
            return;
        }

        queue_.erase(queue_.begin());

        if (!queue_.empty()) {
            async_write(
                socket_,
                boost::asio::buffer(*queue_.front()),
                boost::beast::bind_front_handler(
                    &session::on_write, shared_from_this()
                )
            );
        }
    }
}
