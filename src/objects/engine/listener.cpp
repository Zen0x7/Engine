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

#include <engine/listener.hpp>

#include <engine/session.hpp>
#include <engine/state.hpp>

#include <boost/asio/strand.hpp>
#include <boost/beast/core/bind_handler.hpp>

namespace engine {
    listener::listener(boost::asio::io_context &io_context, const boost::asio::ip::tcp::endpoint &endpoint, const std::shared_ptr<state> &state) :
        io_context_(io_context),
        acceptor_(make_strand(io_context)), state_(state) {
        boost::system::error_code _error_code;
        acceptor_.open(endpoint.protocol(), _error_code);
        acceptor_.set_option(boost::asio::ip::tcp::no_delay(true), _error_code);
        acceptor_.set_option(boost::asio::socket_base::reuse_address(true), _error_code);
        acceptor_.bind(endpoint, _error_code);
        acceptor_.listen(boost::asio::socket_base::max_listen_connections, _error_code);
        state_->set_port(acceptor_.local_endpoint().port());
    }

    void listener::start() {
        do_accept();
    }

    void listener::do_accept() {
        acceptor_.async_accept(make_strand(io_context_), boost::beast::bind_front_handler(
            &listener::on_accept,
            shared_from_this()
        ));
    }

    void listener::on_accept(const boost::system::error_code &error_code, boost::asio::ip::tcp::socket socket) {
        if (!error_code) {
            auto _session = std::make_shared<session>(state_, std::move(socket));
            _session->start();
        }
        do_accept();
    }
}
