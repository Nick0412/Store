#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <string>

namespace Networking
{
    // Forward declaration.
    class EndpointBuilder;

    /**
     * @brief Endpoint class representing a combination of an IPv4
     * address and a port number.
     * 
     */
    class Endpoint
    {
    private:
        std::string ip_address;
        std::uint16_t port;

    public:
        Endpoint() = delete;
        Endpoint(const std::string ip_address, std::uint16_t port);

        std::string getIpAddress() const;
        std::uint16_t getPort() const;

        static EndpointBuilder Builder();
    };
}

#endif