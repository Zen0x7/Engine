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

#ifndef ENGINE_STATE_HPP
#define ENGINE_STATE_HPP

#include <engine/action.hpp>
#include <engine/callback.hpp>

#include <memory>
#include <boost/uuid/uuid.hpp>
#include <unordered_map>
#include <atomic>
#include <shared_mutex>

namespace engine {
    /**
     * Forward Session
     */
    class session;

    /**
     * State
     */
    class state : public std::enable_shared_from_this<state> {
        /**
         * ID
         */
        boost::uuids::uuid id_;

        /**
         * Callbacks
         */
        std::unordered_map<action, callback> actions_;

        /**
         * Port
         */
        std::atomic<unsigned short> port_ = 0;

        /**
         * Sessions
         */
        std::unordered_map<boost::uuids::uuid, std::shared_ptr<session>> sessions_;

        /**
         * Sessions Mutex
         */
        std::shared_mutex sessions_mutex_;
    public:
        /**
         * Constructor
         */
        state();

        /**
         * Get ID
         *
         * @return
         */
        boost::uuids::uuid get_id() const;

        /**
         * Get Actions
         *
         * @return
         */
        const std::unordered_map<action, callback> &get_actions() const;

        /**
         * Push Action
         *
         * @param action
         * @param callback
         */
        void push_action(action action, callback callback);

        /**
         * Set Port
         *
         * @param port
         */
        void set_port(unsigned short port);

        /**
         * Get Port
         */
        unsigned short get_port() const;

        /**
         * Add Session
         *
         * @param session
         */
        void add_session(const std::shared_ptr<session> &session);

        /**
         * Remove Session
         *
         * @param id
         */
        void remove_session(boost::uuids::uuid id);

        /**
         * Get Sessions
         *
         * @return
         */
        std::unordered_map<boost::uuids::uuid, std::shared_ptr<session>> &get_sessions();
    };
}

#endif // ENGINE_STATE_HPP
