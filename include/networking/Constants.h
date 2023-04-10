#ifndef NETWORKING_CONSTANTS_H
#define NETWORKING_CONSTANTS_H

#include <cstddef>

namespace Networking::Constants
{
    constexpr std::size_t IP_NUMBER_OF_BYTES = 4;
    constexpr int MAX_VALUE_OF_IP_BLOCK = 255;
    constexpr int MIN_VALUE_OF_IP_BLOCK = 0;
}

#endif