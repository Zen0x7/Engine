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

#ifndef ENGINE_SERVER_HPP
#define ENGINE_SERVER_HPP

#include <memory>
#include <boost/asio/io_context.hpp>

namespace engine {
    /**
     * Forward State
     */
    class state;

    /**
     * Forward Listener
     */
    class listener;

    /**
     * Server
     */
    class server : public std::enable_shared_from_this<server> {
        /**
         * State
         */
        std::shared_ptr<state> state_;

        /**
         * IO Context
         */
        boost::asio::io_context io_context_;

        /**
         * Port
         */
        unsigned short port_ = 0;
      public:
        /**
         * Constructor

         * @param state
         * @param port
         */
        explicit server(const std::shared_ptr<state> & state, unsigned short port = 0);

        /**
         * Get State
         *
         * @return
         */
        std::shared_ptr<state> get_state() const;

        /**
         * Start
         *
         * @param number_of_threads
         */
        void start(int number_of_threads = 1);


        /**
         * Stop
         */
        void stop();

    private:
        /**
         * Register Actions
         */
        void register_actions() const;
    };
}

#endif // ENGINE_SERVER_HPP
