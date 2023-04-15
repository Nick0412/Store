#include "messages/MessageHelper.h"
#include <arpa/inet.h>
#include "messages/Constants.h"

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

        std::uint32_t value_network_order = htonl(value);

        byte_buffer[offset] = value_network_order & 0xFF;
        byte_buffer[offset + 1] = (value_network_order >> 8) & 0xFF;
        byte_buffer[offset + 2] = (value_network_order >> 16) & 0xFF;
        byte_buffer[offset + 3] = (value_network_order >> 24) & 0xFF;
    }

}