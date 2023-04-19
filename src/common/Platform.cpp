#include "common/Platform.h"

uint32_t Common::Platform::NetworkByteOrderLong(uint32_t value)
{
    return htonl(value);
}
