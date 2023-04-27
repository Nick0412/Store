#ifndef MESSAGE_HELPER_H
#define MESSAGE_HELPER_H

#include "common/Types.h"
#include "MessageType.h"
#include <string>
#include <type_traits>

namespace Messages::MessageHelper
{   
    template <typename T>
    concept HasSerialize = requires(T obj)
    {
        { T::Serialize(obj) } -> std::same_as<Common::Types::ByteVector>;
    };

    template <typename T>
    concept HasDeserialize = requires(Common::Types::ByteVector byte_buffer)
    {
        { T::Deserialize(byte_buffer) } -> std::same_as<T>;
    };

    // TODO: Consider helper writer class that keeps track of index where it is writing.
    void placeMessageSizeInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t size_bytes);
    void placeMessageTypeInByteBuffer(Common::Types::ByteVector& byte_buffer, MessageType message_type);
    void place32BitValueInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::uint32_t value);
    void placeStringInByteBuffer(Common::Types::ByteVector& byte_buffer, std::size_t offset, std::string str);

    std::uint32_t Extract32BitValueFromByteBuffer(const Common::Types::ByteVector& byte_buffer, std::size_t offset);
    std::uint32_t ExtractMessageSizeFromByteBuffer(const Common::Types::ByteVector& byte_buffer);
    MessageType ExtractMessageTypeFromByteBuffer(const Common::Types::ByteVector& byte_buffer);
}


#endif