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

#ifndef ENGINE_SESSION_HPP
#define ENGINE_SESSION_HPP

#include <engine/kernel.hpp>

#include <memory>
#include <array>
#include <boost/asio/ip/tcp.hpp>

#include <engine/buffer.hpp>

#ifndef ENGINE_SESSION_BUFFERS_LENGTH
#define ENGINE_SESSION_BUFFERS_LENGTH 128
#endif


namespace engine {
    /**
     * Session
     */
    class session : public std::enable_shared_from_this<session> {
        /**
         * State
         */
        std::shared_ptr<state> state_;

        /**
         * Kernel
         */
        std::unique_ptr<kernel> kernel_;

        /**
         * Socket
         */
        boost::asio::ip::tcp::socket socket_;

        /**
         * Buffer Offset
         */
        std::size_t buffer_offset_ = 0;

        /**
         * Buffers
         */
        std::vector<buffer> buffers_;

        /**
         * Current Header
         */
        std::vector<std::byte> header_;
    public:
        /**
         * Constructor
         *
         * @param state
         * @param socket
         */
        explicit session(const std::shared_ptr<state> &state, boost::asio::ip::tcp::socket socket);

        /**
         * On Request
         *
         * @param request
         * @return
         */
        response on_request(const request & request) const;

        /**
         * Start
         */
        void start();
    private:
        /**
         * Read Header
         */
        void read_header();

        /**
         * Read Payload
         *
         * @param pending_bytes
         */
        void read_payload(std::uint32_t pending_bytes);

        /**
         * On Payload
         *
         * @param offset
         * @param bytes
         */
        void on_payload(std::size_t offset, std::size_t bytes);

        /**
         * Buffer Is Last
         *
         * @return
         */
        bool buffer_is_last() const;

        /**
         * Get Buffer
         *
         * @return
         */
        buffer & get_buffer();
    };
}

#endif // ENGINE_SESSION_HPP
