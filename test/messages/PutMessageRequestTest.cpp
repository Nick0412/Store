#include "gtest/gtest.h"
#include "messages/MessageBase.h"
#include "messages/PutMessageRequest.h"

namespace
{
    TEST(PutMessageRequest, SerializeDeserialize_Success)
    {
        std::string test_key = "MyKey";
        std::string test_value = "MyValue";
        Messages::PutMessageRequest message{test_key, test_value};

        auto byte_buffer = Messages::MessageBase<Messages::PutMessageRequest>::Serialize(message);
        auto message_result = Messages::MessageBase<Messages::PutMessageRequest>::Deserialize(byte_buffer);

        EXPECT_EQ(message_result.getKey(), message.getKey());
        EXPECT_EQ(message_result.getValue(), message.getValue());
    }
}