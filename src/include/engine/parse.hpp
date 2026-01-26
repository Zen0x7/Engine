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

#ifndef ENGINE_PARSE_HPP
#define ENGINE_PARSE_HPP

#include <engine/request.hpp>

#include <boost/endian/conversion.hpp>
#include <cstring>

namespace engine {
    inline std::vector<request> parse(std::span<std::byte> data) {
        std::vector<request> _result;

        const auto _items = std::to_integer<uint8_t>(data[0]);
        std::size_t _offset = 1;

        for (std::uint8_t _i = 0; _i < _items; ++_i) {
            std::uint16_t _length_be;
            std::memcpy(&_length_be, data.data() + _offset, sizeof(_length_be));
            _offset += sizeof(_length_be);

            const std::uint16_t _length =
                boost::endian::big_to_native(_length_be);

            const auto _entry = std::span<const std::byte>(data.data() + _offset, _length);
            _offset += _length;
            _result.push_back(request::from_binary(_entry));
        }

        return _result;
    }
}

#endif // ENGINE_PARSE_HPP
