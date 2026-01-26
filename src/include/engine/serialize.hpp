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

#ifndef ENGINE_SERIALIZE_HPP
#define ENGINE_SERIALIZE_HPP

#include <vector>
#include <cstdint>

#include <engine/request.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/crc.hpp>

namespace engine {
    inline std::vector<std::byte> serialize_requests(const std::vector<request>& requests) {
        std::vector<std::byte> _result;
        std::size_t _total_length = 0;
        for (auto _request : requests) {
            _total_length += 20;
            for (auto &_fields = _request.get_fields(); const auto & _field: _fields) {
                _total_length += 2 + _field.size();
            }
        }
        _result.reserve(_total_length + 4);

        _result.push_back(std::byte{ static_cast<std::uint8_t>(requests.size()) });

        for (const auto& _request : requests) {
            auto _entry = _request.to_binary();

            std::uint16_t _length =
                      boost::endian::native_to_big(
                          static_cast<std::uint16_t>(_entry.size())
                      );

            const auto* _p = reinterpret_cast<const std::byte*>(&_length);
            _result.insert(_result.end(), _p, _p + sizeof(_length));
            _result.insert(_result.end(), _entry.begin(), _entry.end());
        }

        boost::crc_32_type _crc;
        _crc.process_bytes(_result.data(), _result.size());

        const std::uint32_t _crc_value =
            boost::endian::native_to_big(_crc.checksum());

        const auto* _c = reinterpret_cast<const std::byte*>(&_crc_value);
        _result.insert(_result.end(), _c, _c + sizeof(_crc_value));

        return _result;
    }
}

#endif // ENGINE_SERIALIZE_HPP
