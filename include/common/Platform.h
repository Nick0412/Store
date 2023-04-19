#ifndef PLATFORM_H
#define PLATFORM_H

/*
 * Utilities to abstract platform-specific code
 */

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif
#include <cstdint>

namespace Common::Platform
{
    uint32_t NetworkByteOrderLong(uint32_t value);
}

#endif