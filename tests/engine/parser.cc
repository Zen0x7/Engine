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

#include <engine/parse.hpp>

using namespace engine;

TEST(parser_test, it_can_parse_join) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x14 },

        // Entry type (1 byte, ie: 2 = JOIN)
        std::byte{ 0x02 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x01 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), JOIN);
    ASSERT_EQ(_result[0].get_parameters().size(), 1);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
}

TEST(parser_test, it_can_parse_leave) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x14 },

        // Entry type (1 byte, ie: 3 = LEAVE)
        std::byte{ 0x03 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x01 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), LEAVE);
    ASSERT_EQ(_result[0].get_parameters().size(), 1);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
}

TEST(parser_test, it_can_parse_subscribe) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x1B },

        // Entry type (1 byte, ie: 4 = SUBSCRIBE)
        std::byte{ 0x04 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x02 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },

        // 2° parameter length (2 bytes, ie: 5)
        std::byte{ 0x00 },
        std::byte{ 0x05 },

        // 2° parameter value (5 bytes ... is "world")
        std::byte{ 0x77 },
        std::byte{ 0x6F },
        std::byte{ 0x72 },
        std::byte{ 0x6C },
        std::byte{ 0x64 },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), SUBSCRIBE);
    ASSERT_EQ(_result[0].get_parameters().size(), 2);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
    ASSERT_EQ(_result[0].get_parameters()[1].size(), 5);
    ASSERT_EQ(_result[0].get_parameters()[1][0], std::byte{ 0x77 });
    ASSERT_EQ(_result[0].get_parameters()[1][1], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[1][2], std::byte{ 0x72 });
    ASSERT_EQ(_result[0].get_parameters()[1][3], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[1][4], std::byte{ 0x64 });
}

TEST(parser_test, it_can_parse_unsubscribe) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x1B },

        // Entry type (1 byte, ie: 5 = UNSUBSCRIBE)
        std::byte{ 0x05 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x02 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },

        // 2° parameter length (2 bytes, ie: 5)
        std::byte{ 0x00 },
        std::byte{ 0x05 },

        // 2° parameter value (5 bytes ... is "world")
        std::byte{ 0x77 },
        std::byte{ 0x6F },
        std::byte{ 0x72 },
        std::byte{ 0x6C },
        std::byte{ 0x64 },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), UNSUBSCRIBE);
    ASSERT_EQ(_result[0].get_parameters().size(), 2);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
    ASSERT_EQ(_result[0].get_parameters()[1].size(), 5);
    ASSERT_EQ(_result[0].get_parameters()[1][0], std::byte{ 0x77 });
    ASSERT_EQ(_result[0].get_parameters()[1][1], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[1][2], std::byte{ 0x72 });
    ASSERT_EQ(_result[0].get_parameters()[1][3], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[1][4], std::byte{ 0x64 });
}

TEST(parser_test, it_can_parse_publish) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x22 },

        // Entry type (1 byte, ie: 6 = PUBLISH)
        std::byte{ 0x06 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x03 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },

        // 2° parameter length (2 bytes, ie: 5)
        std::byte{ 0x00 },
        std::byte{ 0x05 },

        // 2° parameter value (5 bytes ... is "world")
        std::byte{ 0x77 },
        std::byte{ 0x6F },
        std::byte{ 0x72 },
        std::byte{ 0x6C },
        std::byte{ 0x64 },

        // 3° parameter length (2 bytes, ie: 5)
        std::byte{ 0x00 },
        std::byte{ 0x05 },

        // 3° parameter value (5 bytes ... is "hello")
        std::byte{ 0x68 },
        std::byte{ 0x65 },
        std::byte{ 0x6C },
        std::byte{ 0x6C },
        std::byte{ 0x6F },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), PUBLISH);
    ASSERT_EQ(_result[0].get_parameters().size(), 3);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
    ASSERT_EQ(_result[0].get_parameters()[1].size(), 5);
    ASSERT_EQ(_result[0].get_parameters()[1][0], std::byte{ 0x77 });
    ASSERT_EQ(_result[0].get_parameters()[1][1], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[1][2], std::byte{ 0x72 });
    ASSERT_EQ(_result[0].get_parameters()[1][3], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[1][4], std::byte{ 0x64 });
    ASSERT_EQ(_result[0].get_parameters()[2].size(), 5);
    ASSERT_EQ(_result[0].get_parameters()[2][0], std::byte{ 0x68 });
    ASSERT_EQ(_result[0].get_parameters()[2][1], std::byte{ 0x65 });
    ASSERT_EQ(_result[0].get_parameters()[2][2], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[2][3], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[2][4], std::byte{ 0x6F });
}

TEST(parser_test, it_can_parse_broadcast) {
    std::array _stream = {
        std::byte{ 0x01 }, // Number of items (ie: 1)

        // Length of entry
        std::byte{ 0x00 },
        std::byte{ 0x1B },

        // Entry type (1 byte, ie: 7 = BROADCAST)
        std::byte{ 0x07 },

        // Entry parameters (1 byte, ie: 1)
        std::byte{ 0x02 },

        // 1° parameter length (2 bytes, ie: 16)
        std::byte{ 0x00 },
        std::byte{ 0x10 },

        // 1° parameter value (16 bytes ... is a uuid v4)
        std::byte{ 0xA2 },
        std::byte{ 0xCF },
        std::byte{ 0xAA },
        std::byte{ 0xCF },
        std::byte{ 0x6E },
        std::byte{ 0xBC },
        std::byte{ 0x4F },
        std::byte{ 0x18 },
        std::byte{ 0x91 },
        std::byte{ 0xDF },
        std::byte{ 0x20 },
        std::byte{ 0x80 },
        std::byte{ 0x6F },
        std::byte{ 0x0B },
        std::byte{ 0x54 },
        std::byte{ 0x2A },

        // 2° parameter length (2 bytes, ie: 5)
        std::byte{ 0x00 },
        std::byte{ 0x05 },

        // 2° parameter value (5 bytes ... is "hello")
        std::byte{ 0x68 },
        std::byte{ 0x65 },
        std::byte{ 0x6C },
        std::byte{ 0x6C },
        std::byte{ 0x6F },
    };

    auto _result = parse(_stream);

    ASSERT_EQ(_result.size(), 1);
    ASSERT_EQ(_result[0].get_action(), BROADCAST);
    ASSERT_EQ(_result[0].get_parameters().size(), 2);
    ASSERT_EQ(_result[0].get_parameters()[0].size(), 16);
    ASSERT_EQ(_result[0].get_parameters()[0][0], std::byte{ 0xA2 });
    ASSERT_EQ(_result[0].get_parameters()[0][1], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][2], std::byte{ 0xAA });
    ASSERT_EQ(_result[0].get_parameters()[0][3], std::byte{ 0xCF });
    ASSERT_EQ(_result[0].get_parameters()[0][4], std::byte{ 0x6E });
    ASSERT_EQ(_result[0].get_parameters()[0][5], std::byte{ 0xBC });
    ASSERT_EQ(_result[0].get_parameters()[0][6], std::byte{ 0x4F });
    ASSERT_EQ(_result[0].get_parameters()[0][7], std::byte{ 0x18 });
    ASSERT_EQ(_result[0].get_parameters()[0][8], std::byte{ 0x91 });
    ASSERT_EQ(_result[0].get_parameters()[0][9], std::byte{ 0xDF });
    ASSERT_EQ(_result[0].get_parameters()[0][10], std::byte{ 0x20 });
    ASSERT_EQ(_result[0].get_parameters()[0][11], std::byte{ 0x80 });
    ASSERT_EQ(_result[0].get_parameters()[0][12], std::byte{ 0x6F });
    ASSERT_EQ(_result[0].get_parameters()[0][13], std::byte{ 0x0B });
    ASSERT_EQ(_result[0].get_parameters()[0][14], std::byte{ 0x54 });
    ASSERT_EQ(_result[0].get_parameters()[0][15], std::byte{ 0x2A });
    ASSERT_EQ(_result[0].get_parameters()[1].size(), 5);
    ASSERT_EQ(_result[0].get_parameters()[1][0], std::byte{ 0x68 });
    ASSERT_EQ(_result[0].get_parameters()[1][1], std::byte{ 0x65 });
    ASSERT_EQ(_result[0].get_parameters()[1][2], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[1][3], std::byte{ 0x6C });
    ASSERT_EQ(_result[0].get_parameters()[1][4], std::byte{ 0x6F });
}

