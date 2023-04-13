#ifndef NETWORKING_TYPES_H
#define NEWWORKING_TYPES_H

#include <cstddef>
#include <vector>

namespace Networking::Types
{
    using ByteVector = std::vector<std::byte>;
    using SocketHandle = int;
}

#endif