#ifndef MESSAGE_TYPE
#define MESSAGE_TYPE

#include <cstdint>

namespace Messages
{
    enum class MessageType : std::uint32_t
    {
        PUT_MESSAGE = 1,
        GET_MESSAGE = 2,
        GET_MESSAGE_RESPONSE = 3
    };
}

#endif