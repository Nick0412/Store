#ifndef MESSAGES_CONSTANTS_H
#define MESSAGES_CONSTANTS_H

#include <cstddef>

namespace Messages::Constants
{
    constexpr std::size_t MESSAGE_SIZE_BYTES = 4;
    constexpr std::size_t MESSAGE_TYPE_BYTES = 4;

    constexpr std::size_t MESSAGE_SIZE_OFFSET = 0;
    constexpr std::size_t MESSAGE_TYPE_OFFSET = 4;
    constexpr std::size_t MESSAGE_DATA_OFFSET = 8;
}

#endif