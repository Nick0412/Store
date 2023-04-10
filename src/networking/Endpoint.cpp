#include "networking/Endpoint.h"
#include "networking/EndpointBuilder.h"
#include "networking/Common.h"

namespace Networking
{
    Endpoint::Endpoint(const std::string ip_address, std::uint16_t port)
    : ip_address{ip_address}, port{port}
    {
        Common::ValidateIpAddress(ip_address);
    }

    std::string Endpoint::getIpAddress() const
    {
        return ip_address;
    }

    std::uint16_t Endpoint::getPort() const
    {
        return port;
    }

    EndpointBuilder Endpoint::Builder()
    {
        return EndpointBuilder();
    }
}