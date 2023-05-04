#include "gtest/gtest.h"
#include "messages/MessageBase.h"
#include "messages/GetMessageResponse.h"
#include "messages/MessageType.h"
#include "messages/MessageHelper.h"
#include <algorithm>
#include <iostream>

namespace
{
    TEST(GetMessageResponse, SerializeDeserialize_Success)
    {
        std::string test_result = "my_result";
        Messages::GetMessageResponse message(test_result);

        auto byte_buffer = Messages::MessageBase<Messages::GetMessageResponse>::Serialize(message);
        auto msg_request = Messages::MessageBase<Messages::GetMessageResponse>::Deserialize(byte_buffer);
        auto message_type_result = Messages::MessageHelper::ExtractMessageTypeFromByteBuffer(byte_buffer);

        EXPECT_EQ(test_result, msg_request.getResult());
        EXPECT_EQ(message_type_result, Messages::MessageType::GET_MESSAGE_RESPONSE);
    }
}