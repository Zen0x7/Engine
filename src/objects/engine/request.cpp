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
#include <cstring>

namespace engine {
    request::request(const action action) : action_(action) {
    }

    action request::get_action() const {
        return action_;
    }

    std::vector<std::span<const std::byte> > &request::get_parameters() {
        return parameters_;
    }

    request request::from_binary(const std::span<const std::byte> data) {
        std::size_t _offset = 0;

        const auto _action = static_cast<action>(std::to_integer<std::uint8_t>(data[_offset++]));
        request _req(_action);

        const auto _parameters_length = std::to_integer<std::uint8_t>(data[_offset++]);

        for (std::uint8_t _i = 0; _i < _parameters_length; ++_i) {
            const std::uint16_t _length =
                    std::to_integer<uint8_t>(data[_offset]) << 8 |
                    std::to_integer<uint8_t>(data[_offset + 1]);

            _offset += 2;

            _req.parameters_.push_back(data.subspan(_offset, _length));
            _offset += _length;
        }

        return _req;
    }
}
