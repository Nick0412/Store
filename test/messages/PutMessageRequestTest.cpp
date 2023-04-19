#include "gtest/gtest.h"
#include "messages/PutMessageRequest.h"
#include "messages/Constants.h"
#include <string>
#include "messages/MessageHelper.h"

namespace
{
    TEST(PutMessageRequest, VerifySerialize)
    {
        // Setup
        std::string test_key = "my-key";
        std::string test_value = "my-value";
        Messages::PutMessageRequest request(test_key, test_value);

        // Act
        auto buffer = Messages::PutMessageRequest::Serialize(request);

        // Verify
        auto expected_size = Messages::Constants::MESSAGE_SIZE_BYTES + 
            Messages::Constants::MESSAGE_TYPE_BYTES +
            Messages::PutMessageRequest::KEY_SIZE_BYTES +
            test_key.size() +
            Messages::PutMessageRequest::VALUE_SIZE_BYTES +
            test_value.size();

        auto offset_to_key_data = Messages::PutMessageRequest::GetKeyDataOffset(request);
        auto offset_to_value_data = Messages::PutMessageRequest::GetValueDataOffset(request);
        auto offset_to_key_size = Messages::PutMessageRequest::GetKeySizeOffset(request);
        auto offset_to_value_size = Messages::PutMessageRequest::GetValueSizeOffset(request);

        std::string actual_key{
            buffer.cbegin() + offset_to_key_data, 
            buffer.cbegin() + offset_to_key_data + test_key.size()};
        
        std::string actual_value{
            buffer.cbegin() + offset_to_value_data,
            buffer.cbegin() + offset_to_value_data + test_value.size()};

        auto actual_key_size = Messages::MessageHelper::get32BitValueFromByteBuffer(buffer, offset_to_key_size);
        auto actual_value_size = Messages::MessageHelper::get32BitValueFromByteBuffer(buffer, offset_to_value_size);

        EXPECT_EQ(expected_size, buffer.size());
        EXPECT_EQ(test_key, actual_key);
        EXPECT_EQ(test_value, actual_value);
        EXPECT_EQ(test_key.size(), actual_key_size);
        EXPECT_EQ(test_value.size(), actual_value_size);
    }
}