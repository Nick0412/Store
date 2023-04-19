#ifndef MESSAGE_HELPER_H
#define MESSAGE_HELPER_H

#include "common/Types.h"
#include "MessageType.h"
#include <string>

namespace Messages::MessageHelper
{   
    using ConstBufferRef = const Common::Types::ByteVector&;

    // TODO: Consider helper writer class that keeps track of index where it is writing.
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes);
    void placeMessageTypeInByteBuffer(Common::Types::ByteVector& byte_buffer, MessageType message_type);
    void place32BitValueInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::uint32_t value);
    void placeStringInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::string str);

    std::uint32_t get32BitValueFromByteBuffer(ConstBufferRef byte_buffer, std::size_t offset);
}


#endif