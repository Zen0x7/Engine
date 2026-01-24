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

#ifndef ENGINE_LISTENER_HPP
#define ENGINE_LISTENER_HPP

#include <memory>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace engine {
    /**
     * Forward State
     */
    class state;

    /**
     * Listener
     */
    class listener : public std::enable_shared_from_this<listener> {
        /**
         * IO Context
         */
        boost::asio::io_context &io_context_;

        /**
         * Acceptor
         */
        boost::asio::ip::tcp::acceptor acceptor_;

        /**
         * State
         */
        std::shared_ptr<state> state_;
    public:
        /**
         * Constructor
         *
         * @param io_context
         * @param endpoint
         * @param state
         */
        listener(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint, const std::shared_ptr<state> &state);

        /**
         * Start
         */
        void start();

    private:
        /**
         * Do Accept
         */
        void do_accept();

        /**
         * On Accept
         *
         * @param error_code
         * @param socket
         */
        void on_accept(const boost::system::error_code &error_code, boost::asio::ip::tcp::socket socket);
    };
}

#endif // ENGINE_LISTENER_HPP
