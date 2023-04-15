#ifndef MESSAGE_HELPER_H
#define MESSAGE_HELPER_H

#include "common/Types.h"
#include "MessageType.h"
#include <string>

namespace Messages::MessageHelper
{   
    // TODO: Consider helper writer class that keeps track of index where it is writing.
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes);
    void place32BitValueInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::uint32_t value);
    void placeStringInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::string str);
}


#endif