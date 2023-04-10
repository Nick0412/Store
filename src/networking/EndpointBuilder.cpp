#include "networking/EndpointBuilder.h"

namespace Networking
{
    EndpointBuilder::EndpointBuilder()
    : ip_address{""}, port{0}
    {
        
    }

    EndpointBuilder& EndpointBuilder::withIpAddress(const std::string& ip_address)
    {
        this->ip_address = ip_address;
        return *this;
    }

    EndpointBuilder& EndpointBuilder::withPort(std::uint16_t port)
    {
        this->port = port;
        return *this;
    }

    Endpoint EndpointBuilder::build()
    {
        return Endpoint{ip_address, port};
    }
}