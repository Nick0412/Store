#include "gtest/gtest.h"
#include "messages/MessageBase.h"
#include "messages/GetMessageRequest.h"
#include <algorithm>
#include <iostream>

namespace
{
    TEST(GetMessageRequest, SerializeDeserialize_Success)
    {
        std::string test_key = "MyKey";
        Messages::GetMessageRequest message(test_key);

        auto byte_buffer = Messages::MessageBase<Messages::GetMessageRequest>::Serialize(message);
        auto msg_request = Messages::MessageBase<Messages::GetMessageRequest>::Deserialize(byte_buffer);

        EXPECT_EQ(test_key, msg_request.getKey());
    }
}