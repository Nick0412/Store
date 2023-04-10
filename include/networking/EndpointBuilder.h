#ifndef ENDPOINT_BUILDER_H
#define ENDPOINT_BUILDER_H

#include "Endpoint.h"

namespace Networking
{
    class EndpointBuilder
    {
    private:
        std::string ip_address;
        std::uint16_t port;

    public:
        EndpointBuilder();

        EndpointBuilder& withIpAddress(const std::string& ip_address);
        EndpointBuilder& withPort(std::uint16_t port);
        
        Endpoint build();
    };
}


#endif