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

#include <engine/serialize.hpp>

using namespace engine;

TEST(serialize_test, it_can_serialize_requests) {
    request _join_request(JOIN);
    auto &_join_fields = _join_request.get_fields();
    _join_fields.reserve(2);
    std::array _id {
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
    _join_fields.emplace_back(_id);

    request _subscribe_request(SUBSCRIBE);
    auto &_subscribe_fields = _subscribe_request.get_fields();
    _subscribe_fields.reserve(2);
    _subscribe_fields.emplace_back(_id);
    std::array _channel {
        std::byte{ 0x77 },
        std::byte{ 0x6F },
        std::byte{ 0x72 },
        std::byte{ 0x6C },
        std::byte{ 0x64 },
      };
    _subscribe_fields.emplace_back(_channel);

    auto _serialized = serialize_requests({ _join_request, _subscribe_request });

    ASSERT_EQ(_serialized.size(), 88);
    ASSERT_EQ(_serialized[0], std::byte{ 0x02 });
    ASSERT_EQ(_serialized[1], std::byte{ 0x00 });
    ASSERT_EQ(_serialized[2], std::byte{ 0x24 });
    ASSERT_EQ(_serialized[3], std::byte{ _join_request.get_id().data[0] });
    ASSERT_EQ(_serialized[4], std::byte{ _join_request.get_id().data[1] });
    ASSERT_EQ(_serialized[5], std::byte{ _join_request.get_id().data[2] });
    ASSERT_EQ(_serialized[6], std::byte{ _join_request.get_id().data[3] });
    ASSERT_EQ(_serialized[7], std::byte{ _join_request.get_id().data[4] });
    ASSERT_EQ(_serialized[8], std::byte{ _join_request.get_id().data[5] });
    ASSERT_EQ(_serialized[9], std::byte{ _join_request.get_id().data[6] });
    ASSERT_EQ(_serialized[10], std::byte{ _join_request.get_id().data[7] });
    ASSERT_EQ(_serialized[11], std::byte{ _join_request.get_id().data[8] });
    ASSERT_EQ(_serialized[12], std::byte{ _join_request.get_id().data[9] });
    ASSERT_EQ(_serialized[13], std::byte{ _join_request.get_id().data[10] });
    ASSERT_EQ(_serialized[14], std::byte{ _join_request.get_id().data[11] });
    ASSERT_EQ(_serialized[15], std::byte{ _join_request.get_id().data[12] });
    ASSERT_EQ(_serialized[16], std::byte{ _join_request.get_id().data[13] });
    ASSERT_EQ(_serialized[17], std::byte{ _join_request.get_id().data[14] });
    ASSERT_EQ(_serialized[18], std::byte{ _join_request.get_id().data[15] });

    ASSERT_EQ(_serialized[19], std::byte{ 0x02 });
    ASSERT_EQ(_serialized[20], std::byte{ 0x01 });
    ASSERT_EQ(_serialized[21], std::byte{ 0x00 });
    ASSERT_EQ(_serialized[22], std::byte{ 0x10 });

    ASSERT_EQ(_serialized[23], std::byte{ 0xA2 });
    ASSERT_EQ(_serialized[24], std::byte{ 0xCF });
    ASSERT_EQ(_serialized[25], std::byte{ 0xAA });
    ASSERT_EQ(_serialized[26], std::byte{ 0xCF });
    ASSERT_EQ(_serialized[27], std::byte{ 0x6E });
    ASSERT_EQ(_serialized[28], std::byte{ 0xBC });
    ASSERT_EQ(_serialized[29], std::byte{ 0x4F });
    ASSERT_EQ(_serialized[30], std::byte{ 0x18 });
    ASSERT_EQ(_serialized[31], std::byte{ 0x91 });
    ASSERT_EQ(_serialized[32], std::byte{ 0xDF });
    ASSERT_EQ(_serialized[33], std::byte{ 0x20 });
    ASSERT_EQ(_serialized[34], std::byte{ 0x80 });
    ASSERT_EQ(_serialized[35], std::byte{ 0x6F });
    ASSERT_EQ(_serialized[36], std::byte{ 0x0B });
    ASSERT_EQ(_serialized[37], std::byte{ 0x54 });
    ASSERT_EQ(_serialized[38], std::byte{ 0x2A });

    ASSERT_EQ(_serialized[39], std::byte{ 0x00 });
    ASSERT_EQ(_serialized[40], std::byte{ 0x2B });


    ASSERT_EQ(_serialized[41], std::byte{ _subscribe_request.get_id().data[0] });
    ASSERT_EQ(_serialized[42], std::byte{ _subscribe_request.get_id().data[1] });
    ASSERT_EQ(_serialized[43], std::byte{ _subscribe_request.get_id().data[2] });
    ASSERT_EQ(_serialized[44], std::byte{ _subscribe_request.get_id().data[3] });
    ASSERT_EQ(_serialized[45], std::byte{ _subscribe_request.get_id().data[4] });
    ASSERT_EQ(_serialized[46], std::byte{ _subscribe_request.get_id().data[5] });
    ASSERT_EQ(_serialized[47], std::byte{ _subscribe_request.get_id().data[6] });
    ASSERT_EQ(_serialized[48], std::byte{ _subscribe_request.get_id().data[7] });
    ASSERT_EQ(_serialized[49], std::byte{ _subscribe_request.get_id().data[8] });
    ASSERT_EQ(_serialized[50], std::byte{ _subscribe_request.get_id().data[9] });
    ASSERT_EQ(_serialized[51], std::byte{ _subscribe_request.get_id().data[10] });
    ASSERT_EQ(_serialized[52], std::byte{ _subscribe_request.get_id().data[11] });
    ASSERT_EQ(_serialized[53], std::byte{ _subscribe_request.get_id().data[12] });
    ASSERT_EQ(_serialized[54], std::byte{ _subscribe_request.get_id().data[13] });
    ASSERT_EQ(_serialized[55], std::byte{ _subscribe_request.get_id().data[14] });
    ASSERT_EQ(_serialized[56], std::byte{ _subscribe_request.get_id().data[15] });

    ASSERT_EQ(_serialized[57], std::byte{ 0x04 });
    ASSERT_EQ(_serialized[58], std::byte{ 0x02 });

    ASSERT_EQ(_serialized[59], std::byte{ 0x00 });
    ASSERT_EQ(_serialized[60], std::byte{ 0x10 });

    ASSERT_EQ(_serialized[61], std::byte{ 0xA2 });
    ASSERT_EQ(_serialized[62], std::byte{ 0xCF });
    ASSERT_EQ(_serialized[63], std::byte{ 0xAA });
    ASSERT_EQ(_serialized[64], std::byte{ 0xCF });
    ASSERT_EQ(_serialized[65], std::byte{ 0x6E });
    ASSERT_EQ(_serialized[66], std::byte{ 0xBC });
    ASSERT_EQ(_serialized[67], std::byte{ 0x4F });
    ASSERT_EQ(_serialized[68], std::byte{ 0x18 });
    ASSERT_EQ(_serialized[69], std::byte{ 0x91 });
    ASSERT_EQ(_serialized[70], std::byte{ 0xDF });
    ASSERT_EQ(_serialized[71], std::byte{ 0x20 });
    ASSERT_EQ(_serialized[72], std::byte{ 0x80 });
    ASSERT_EQ(_serialized[73], std::byte{ 0x6F });
    ASSERT_EQ(_serialized[74], std::byte{ 0x0B });
    ASSERT_EQ(_serialized[75], std::byte{ 0x54 });
    ASSERT_EQ(_serialized[76], std::byte{ 0x2A });
    ASSERT_EQ(_serialized[77], std::byte{ 0x00 });
    ASSERT_EQ(_serialized[78], std::byte{ 0x05 });
    ASSERT_EQ(_serialized[79], std::byte{ 0x77 });
    ASSERT_EQ(_serialized[80], std::byte{ 0x6F });
    ASSERT_EQ(_serialized[81], std::byte{ 0x72 });
    ASSERT_EQ(_serialized[82], std::byte{ 0x6C });
    ASSERT_EQ(_serialized[83], std::byte{ 0x64 });
}