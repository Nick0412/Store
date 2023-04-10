#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "networking/Endpoint.h"
#include "networking/EndpointBuilder.h"

TEST(NetworkingEndpoint, ValidEndpoint)
{
    const std::string ip_address = "192.70.43.20";
    const std::uint16_t port = 5000;

    auto endpoint = Networking::Endpoint::Builder()
        .withPort(port)
        .withIpAddress(ip_address)
        .build();

    EXPECT_EQ(endpoint.getIpAddress(), ip_address);
    EXPECT_EQ(endpoint.getPort(), port);
}

TEST(NetworkingEndpoint, InvalidIpException)
{
    const std::string ip_address = "192.700.43.20"; // Invalid
    const std::uint16_t port = 5000;

    EXPECT_THAT(
        [&]() {
            Networking::Endpoint::Builder()
                .withPort(port)
                .withIpAddress(ip_address)
                .build();     
        },
        ::testing::Throws<std::runtime_error>());
}

