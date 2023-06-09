#include "messages/MessageHelper.h"
#include "messages/Constants.h"
#include "common/Platform.h"
#include <stdexcept>

namespace Messages::MessageHelper
{
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes)
    {
        // TODO: Check that the byte buffer is large enough

        // Convert to a known size as std::size_t is variable on systems.
        std::uint32_t size_bytes_converted = static_cast<uint32_t>(size_bytes);
        place32BitValueInByteBuffer(byte_buffer, Messages::Constants::MESSAGE_SIZE_OFFSET, size_bytes_converted);
    }

    void placeMessageTypeInByteBuffer(Common::Types::ByteVector& byte_buffer, MessageType message_type)
    {
        // TODO: Check that buffer is large enough to type bytes

        std::uint32_t message_type_converted = static_cast<std::uint32_t>(message_type);
        place32BitValueInByteBuffer(byte_buffer, Messages::Constants::MESSAGE_TYPE_OFFSET, message_type_converted);
    }

    void place32BitValueInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::uint32_t value)
    {
        // TODO: Check for out of bounds and size of buffer
        // TODO: htonl is platform specific code, this should be generalized later.
        std::uint32_t value_network_order = htonl(value);

        byte_buffer[offset] = value_network_order & 0xFF;
        byte_buffer[offset + 1] = (value_network_order >> 8) & 0xFF;
        byte_buffer[offset + 2] = (value_network_order >> 16) & 0xFF;
        byte_buffer[offset + 3] = (value_network_order >> 24) & 0xFF;
    }

    void placeStringInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::string str)
    {
        auto offset_iterator = byte_buffer.begin() + offset;
        
        std::copy(str.begin(), str.end(), offset_iterator);
    }

    std::uint32_t Extract32BitValueFromByteBuffer(const Common::Types::ByteVector& byte_buffer, std::size_t offset)
    {
        std::uint32_t value{};
        value |= byte_buffer[offset];
        value |= (byte_buffer[offset + 1] << 8);
        value |= (byte_buffer[offset + 2] << 16);
        value |= (byte_buffer[offset + 3] << 24);
        value = ntohl(value);

        return value;
    }

    std::uint32_t ExtractMessageSizeFromByteBuffer(const Common::Types::ByteVector& byte_buffer)
    {
        auto size_offset = Constants::MESSAGE_SIZE_OFFSET;
        auto message_size = Extract32BitValueFromByteBuffer(byte_buffer, size_offset);

        return message_size;
    }

    MessageType ExtractMessageTypeFromByteBuffer(const Common::Types::ByteVector& byte_buffer)
    {
        auto type_offset = Constants::MESSAGE_TYPE_OFFSET;
        auto message_type = Extract32BitValueFromByteBuffer(byte_buffer, type_offset);

        return static_cast<MessageType>(message_type);
    }

    std::string ExtractStringFromByteBuffer(const Common::Types::ByteVector& byte_buffer, std::size_t offset, std::size_t string_size)
    {
        if (offset + string_size > byte_buffer.size())
        {
            throw std::runtime_error("Expected extracted string exceeds buffer size.");
        }

        auto string_start = byte_buffer.begin() + offset;
        auto string_end = string_start + string_size;
        std::string str{string_start, string_end};

        return str;
    }
}