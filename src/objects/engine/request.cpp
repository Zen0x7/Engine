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
#include <boost/endian.hpp>
#include <boost/uuid/uuid.hpp>

namespace engine {
    request::request(const action action, const boost::uuids::uuid id) : id_(id), action_(action) {
    }

    boost::uuids::uuid request::get_id() const {
        return id_;
    }

    action request::get_action() const {
        return action_;
    }

    std::vector<std::span<const std::byte> > &request::get_fields() {
        return fields_;
    }

    request request::from_binary(const std::span<const std::byte> data) {
        std::size_t _offset = 16;

        boost::uuids::uuid _id{};
        std::copy_n(
            reinterpret_cast<const unsigned char*>(data.data()),
            16,
            _id.begin()
        );

        const auto _action = static_cast<action>(std::to_integer<std::uint8_t>(data[_offset++]));
        request _request(_action, _id);

        const auto _fields_length = std::to_integer<std::uint8_t>(data[_offset++]);

        for (std::uint8_t _i = 0; _i < _fields_length; ++_i) {
            std::uint16_t _length_be;
            std::memcpy(&_length_be, data.data() + _offset, sizeof(_length_be));
            _offset += sizeof(_length_be);

            const std::uint16_t _length = boost::endian::big_to_native(_length_be);

            _request.fields_.push_back(data.subspan(_offset, _length));
            _offset += _length;
        }

        return _request;
    }

    std::vector<std::byte> request::to_binary() const {
        std::vector<std::byte> _result;
        std::size_t _total_size = 0;
        for (const auto& _field : fields_) {
            _total_size += 2 + static_cast<std::uint16_t>(_field.size());
        }

        _result.reserve(16 + 2 + _total_size);

        _result.insert(
            _result.end(),
            reinterpret_cast<const std::byte*>(id_.data()),
            reinterpret_cast<const std::byte*>(id_.data()) + 16
        );

        _result.push_back(std::byte{ static_cast<std::uint8_t>(action_) });
        _result.push_back(std::byte{ static_cast<std::uint8_t>(fields_.size()) });

        for (const auto& _field : fields_) {
            boost::endian::big_uint16_t _length = static_cast<std::uint16_t>(_field.size());
            const auto* _length_pointer = reinterpret_cast<const std::byte*>(&_length);

            _result.insert(_result.end(), _length_pointer, _length_pointer + sizeof(_length));
            _result.insert(_result.end(), _field.begin(), _field.end());
        }

        return _result;
    }
}
