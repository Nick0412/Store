#include "gtest/gtest.h"
#include "common/StringUtils.h"

#include <vector>
#include <string>

namespace
{
    using StringList = std::vector<std::string>;

    TEST(StringUtils, SplitString_MultipleDelimterInstance)
    {
        // Setup
        const StringList expected = {"This", "is", "a", "test"};
        const std::string test_string = "This,is,a,test";

        // Act
        auto actual = Common::StringUtils::Split(test_string, ',');

        // Verify
        EXPECT_EQ(actual, expected);
    }

    TEST(StringUtils, SplitString_EmptyString)
    {
        const std::string test_string = "";
        const StringList expected = {""};

        auto actual = Common::StringUtils::Split(test_string, '.');

        // Verify
        EXPECT_EQ(actual, expected);
    }

    TEST(StringUtils, SplitString_OnlyDelimterSingle)
    {
        const std::string test_string = ",";
        const StringList expected = {"", ""};

        auto actual = Common::StringUtils::Split(test_string, ',');

        // Verify
        EXPECT_EQ(actual, expected);
    }

    TEST(StringUtils, SplitString_OnlyDelimterMultiple)
    {
        const std::string test_string = ",,,";
        const StringList expected = {"", "", "", ""};

        auto actual = Common::StringUtils::Split(test_string, ',');

        // Verify
        EXPECT_EQ(actual, expected);
    }

    TEST(StringUtils, SplitString_IpTest)
    {
        const std::string test_string = "192.168.0.1";
        const StringList expected = {"192", "168", "0", "1"};

        auto actual = Common::StringUtils::Split(test_string, '.');

        // Verify
        EXPECT_EQ(actual, expected);
    }

    TEST(StringUtils, SplitString_DelimeterNotMatched)
    {
        const std::string test_string = "192.168.0.1";
        const StringList expected = {"192.168.0.1"};

        auto actual = Common::StringUtils::Split(test_string, '+');

        // Verify
        EXPECT_EQ(actual, expected);
    }
}

