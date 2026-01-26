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

#include <engine/request.hpp>

using namespace engine;

TEST(request_test, it_can_converted_to_bytes) {
  request _request(SUBSCRIBE);
  auto &_fields = _request.get_fields();
  _fields.reserve(2);

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
  _fields.emplace_back(_id);

  std::array _channel {
    std::byte{ 0x77 },
    std::byte{ 0x6F },
    std::byte{ 0x72 },
    std::byte{ 0x6C },
    std::byte{ 0x64 },
  };
  _fields.emplace_back(_channel);

  auto _bytes = _request.to_binary();
  ASSERT_EQ(_bytes.size(), 27);
  ASSERT_EQ(_bytes[0], std::byte{0x04});
  ASSERT_EQ(_bytes[1], std::byte{0x02});

  ASSERT_EQ(_bytes[2], std::byte{0x00});
  ASSERT_EQ(_bytes[3], std::byte{0x10});

  ASSERT_EQ(_bytes[4], std::byte{0xA2});
  ASSERT_EQ(_bytes[5], std::byte{0xCF});
  ASSERT_EQ(_bytes[6], std::byte{0xAA});
  ASSERT_EQ(_bytes[7], std::byte{0xCF});
  ASSERT_EQ(_bytes[8], std::byte{0x6E});
  ASSERT_EQ(_bytes[9], std::byte{0xBC});
  ASSERT_EQ(_bytes[10], std::byte{0x4F});
  ASSERT_EQ(_bytes[11], std::byte{0x18});
  ASSERT_EQ(_bytes[12], std::byte{0x91});
  ASSERT_EQ(_bytes[13], std::byte{0xDF});
  ASSERT_EQ(_bytes[14], std::byte{0x20});
  ASSERT_EQ(_bytes[15], std::byte{0x80});
  ASSERT_EQ(_bytes[16], std::byte{0x6F});
  ASSERT_EQ(_bytes[17], std::byte{0x0B});
  ASSERT_EQ(_bytes[18], std::byte{0x54});
  ASSERT_EQ(_bytes[19], std::byte{0x2A});

  ASSERT_EQ(_bytes[20], std::byte{0x00});
  ASSERT_EQ(_bytes[21], std::byte{0x05});

  ASSERT_EQ(_bytes[22], std::byte{0x77});
  ASSERT_EQ(_bytes[23], std::byte{0x6F});
  ASSERT_EQ(_bytes[24], std::byte{0x72});
  ASSERT_EQ(_bytes[25], std::byte{0x6C});
  ASSERT_EQ(_bytes[26], std::byte{0x64});
}