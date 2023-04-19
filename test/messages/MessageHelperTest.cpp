#include "gtest/gtest.h"
#include "messages/MessageHelper.h"
#include <arpa/inet.h>

TEST(MessageHelper, PlaceMessageSize_Success)
{
    Common::Types::ByteVector buffer(8);
    std::size_t size = 0x12345678;

    Messages::MessageHelper::placeMessageSizeInByteBuffer(buffer, size);

    // Verify that the buffer holds bytes in big endian order
    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
    EXPECT_EQ(buffer[2], 0x56);
    EXPECT_EQ(buffer[3], 0x78);
}

TEST(MessageHelper, PlaceMessageType_Success)
{
    Common::Types::ByteVector buffer(8);
    // PUT_MESSAGE is a uint32 value 1 -> 0x00000001
    Messages::MessageType msg_type = Messages::MessageType::PUT_MESSAGE;

    Messages::MessageHelper::placeMessageTypeInByteBuffer(buffer, msg_type);

    EXPECT_EQ(buffer[4], 0x00);
    EXPECT_EQ(buffer[5], 0x00);
    EXPECT_EQ(buffer[6], 0x00);
    EXPECT_EQ(buffer[7], 0x01);
}

TEST(MessageHelper, Place32BitValueInByteBuffer_Success)
{
    Common::Types::ByteVector buffer(8);
    std::uint32_t value = 0xFEDCBA98;

    Messages::MessageHelper::place32BitValueInByteBuffer(buffer, 2, value);

    EXPECT_EQ(buffer[2], 0xFE);
    EXPECT_EQ(buffer[3], 0xDC);
    EXPECT_EQ(buffer[4], 0xBA);
    EXPECT_EQ(buffer[5], 0x98);
}

TEST(MessageHelper, PlaceStringInByteBuffer_Success)
{
    std::string test_string = "bla";
    Common::Types::ByteVector buffer = {'1', '2', '3', '4', '5'};

    Messages::MessageHelper::placeStringInByteBuffer(buffer, 1, test_string);

    Common::Types::ByteVector expected = {'1', 'b', 'l', 'a', '5'};
    EXPECT_EQ(buffer, expected);
}

TEST(MessageHelper, Get32BitValueFromByteBuffer_Success)
{
    Common::Types::ByteVector buffer = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54};

    auto actual_value = Messages::MessageHelper::get32BitValueFromByteBuffer(buffer, 1);

    // Bytes 1 through 4 in the buffer but reversed then converted to host order
    std::uint32_t exepcted_value = ntohl(0x7698BADC);
    EXPECT_EQ(exepcted_value, actual_value);
}

TEST(MessageHelper, Get32BitValueFromByteBuffer_SuccessAfterPlacement)
{
    Common::Types::ByteVector buffer{10};
    std::uint32_t value = 3100200400;
    auto offset = 3;

    Messages::MessageHelper::place32BitValueInByteBuffer(buffer, offset, value);
    auto actual_result = Messages::MessageHelper::get32BitValueFromByteBuffer(buffer, offset);

    EXPECT_EQ(value, actual_result);
}