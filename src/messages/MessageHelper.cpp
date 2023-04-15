#include "messages/MessageHelper.h"
#include <arpa/inet.h>

namespace Messages::MessageHelper
{
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes)
    {
        // TODO: Check that the byte buffer is large enough

        // Convert to a known size as std::size_t is variable on systems.
        std::uint32_t size_bytes_uint32 = static_cast<uint32_t>(size_bytes);
        std::uint32_t size_bytes_network_order = htonl(size_bytes_uint32);

        byte_buffer[0] = size_bytes_network_order & 0xFF;
        byte_buffer[1] = (size_bytes_network_order >> 8) & 0xFF;
        byte_buffer[2] = (size_bytes_network_order >> 16) & 0xFF;
        byte_buffer[3] = (size_bytes_network_order >> 24) & 0xFF;
    }

    void placeMessageTypeInByteBuffer(Common::Types::ByteVector& byte_buffer, MessageType message_type)
    {
        // TODO: Check that buffer is large enough to type bytes

        std::uint32_t message_type_converted = static_cast<std::uint32_t>(message_type);
        std::uint32_t message_type_network_order = htonl(message_type_converted);

        byte_buffer[4] = message_type_network_order & 0xFF;
        byte_buffer[5] = (message_type_network_order >> 8) & 0xFF;
        byte_buffer[6] = (message_type_network_order >> 16) & 0xFF;
        byte_buffer[7] = (message_type_network_order >> 24) & 0xFF;
    }
}