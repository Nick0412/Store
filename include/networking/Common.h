#ifndef NETWORKING_COMMON_H
#define NETWORKING_COMMON_H

#include <string>
#include <vector>

namespace Networking::Common
{
    void ValidateIpAddress(const std::string& ip_address);
    void ValidateIpNumberOfBytes(const std::vector<std::string>& ip_blocks);
    void ValidateIpBlocksAreInRange(const std::vector<std::string>& ip_blocks);
}

#endif