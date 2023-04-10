#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "networking/Common.h"

namespace
{
    using namespace ::testing;

    TEST(NetworkingCommon, ValidateIpAddress_TooManyBytes)
    {
        const std::string test_ip = "1.2.3.4.5";

        auto substring_matcher_1 = HasSubstr("Number of IP bytes does not equal 4");
        auto substring_matcher_2 = HasSubstr("Invalid IP: " + test_ip);
        auto matchers = AllOf(substring_matcher_1, substring_matcher_2);

        EXPECT_THAT(
            [&]() { 
                Networking::Common::ValidateIpAddress(test_ip); 
            }, 
            ThrowsMessage<std::runtime_error>(matchers));
    }

    TEST(NetworkingCommon, ValidateIpAddress_IpBlockOutOfRange)
    {
        const std::string test_ip = "1.2.300.4";

        auto substring_matcher_1 = HasSubstr("IP block number is not in the range of [0, 255]");
        auto substring_matcher_2 = HasSubstr("Invalid IP: " + test_ip);
        auto matchers = AllOf(substring_matcher_1, substring_matcher_2);

        EXPECT_THAT(
            [&](){ 
                Networking::Common::ValidateIpAddress(test_ip); 
            }, 
            ThrowsMessage<std::runtime_error>(matchers));
    }

    TEST(NetworkingCommon, ValidateIpAddress_ValidIp)
    {
        const std::string test_ip = "192.168.0.1";

        EXPECT_NO_THROW(Networking::Common::ValidateIpAddress(test_ip));
    }
}