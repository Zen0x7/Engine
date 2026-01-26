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

#ifndef ENGINE_CRC_HPP
#define ENGINE_CRC_HPP

#include <memory>
#include <span>
#include <boost/crc.hpp>
#include <boost/endian/conversion.hpp>

namespace engine {
    inline bool crc_check(const std::span<const std::byte> payload_with_crc) {
        const std::size_t _payload_size = payload_with_crc.size() - 4;

        boost::crc_32_type _crc;
        _crc.process_bytes(payload_with_crc.data(), _payload_size);

        const auto* _p = payload_with_crc.data() + _payload_size;

        std::uint32_t _received =
            (static_cast<std::uint32_t>(std::to_integer<uint8_t>(_p[0])) << 24) |
            (static_cast<std::uint32_t>(std::to_integer<uint8_t>(_p[1])) << 16) |
            (static_cast<std::uint32_t>(std::to_integer<uint8_t>(_p[2])) << 8)  |
            (static_cast<std::uint32_t>(std::to_integer<uint8_t>(_p[3])));

        return _crc.checksum() == _received;
    }
}

#endif // ENGINE_CRC_HPP
