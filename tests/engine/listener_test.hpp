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

#include <gtest/gtest.h>

#include <thread>
#include <memory>

#include <engine/state.hpp>
#include <engine/server.hpp>

class listener_test : public testing::Test {
protected:
    /**
     * Thread
     */
    std::unique_ptr<std::jthread> thread_;

    /**
     * State
     */
    std::shared_ptr<engine::state> state_ = std::make_shared<engine::state>();

    /**
     * Server
     */
    std::shared_ptr<engine::server> server_ = std::make_shared<engine::server>(state_);

    /**
     * Set Up
     */
    void SetUp() override {
        thread_ = std::make_unique<std::jthread>([this]() {
            server_->start();
        });

        while (server_->get_state()->get_port() == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    /**
     * Tears Down
     */
    void TearDown() override {
        server_->stop();
        thread_->join();
    }
};
