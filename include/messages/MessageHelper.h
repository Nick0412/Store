#ifndef MESSAGE_HELPER_H
#define MESSAGE_HELPER_H

#include "common/Types.h"
#include "MessageType.h"

namespace Messages::MessageHelper
{
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes);
    void placeMessageTypeInByteBuffer(Common::Types::ByteVector& byte_buffer, MessageType message_type);
}


#endif