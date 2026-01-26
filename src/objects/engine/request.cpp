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

#include <engine/request.hpp>

#include <cstdint>
#include <boost/endian/conversion.hpp>

namespace engine {
    request::request(const action action) : action_(action) {
    }

    action request::get_action() const {
        return action_;
    }

    std::vector<std::span<const std::byte> > &request::get_fields() {
        return fields_;
    }

    request request::from_binary(const std::span<const std::byte> data) {
        std::size_t _offset = 0;

        const auto _action = static_cast<action>(std::to_integer<std::uint8_t>(data[_offset++]));
        request _req(_action);

        const auto _fields_length = std::to_integer<std::uint8_t>(data[_offset++]);

        for (std::uint8_t _i = 0; _i < _fields_length; ++_i) {
            std::uint16_t _length_be;
            std::memcpy(&_length_be, data.data() + _offset, sizeof(_length_be));
            _offset += sizeof(_length_be);

            const std::uint16_t _length =
                boost::endian::big_to_native(_length_be);

            _req.fields_.push_back(data.subspan(_offset, _length));
            _offset += _length;
        }

        return _req;
    }

    std::vector<std::byte> request::to_binary() const {
        std::vector<std::byte> _result;
        std::size_t _total_size = 0;
        for (const auto& _field : fields_) {
            _total_size += 2 + static_cast<std::uint16_t>(_field.size());
        }

        _result.reserve(2 + _total_size);

        _result.push_back(std::byte{ static_cast<std::uint8_t>(action_) });
        _result.push_back(std::byte{ static_cast<std::uint8_t>(fields_.size()) });

        for (const auto& _field : fields_) {

            const std::uint16_t _length =
                boost::endian::native_to_big(
                    static_cast<std::uint16_t>(_field.size())
                );

            const auto* _p = reinterpret_cast<const std::byte*>(&_length);
            _result.insert(_result.end(), _p, _p + sizeof(_length));

            _result.insert(_result.end(), _field.begin(), _field.end());
        }

        return _result;
    }
}
