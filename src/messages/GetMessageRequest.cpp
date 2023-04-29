#include "messages/GetMessageRequest.h"
#include "messages/Constants.h"
#include <iostream>

namespace Messages
{
    GetMessageRequest::GetMessageRequest(const std::string& key)
    : key{key}
    {

    }

    std::string GetMessageRequest::getKey() const
    {
        return key;
    }

    std::size_t GetMessageRequest::CalculateKeySizeOffset(const GetMessageRequest& message)
    {
        return Constants::MESSAGE_DATA_OFFSET;
    }

    std::size_t GetMessageRequest::CalculateKeyDataOffset(const GetMessageRequest& message)
    {
        return GetMessageRequest::CalculateKeySizeOffset(message) +
               GetMessageRequest::KEY_SIZE_IN_BYTES;
    }

    void GetMessageRequest::PlaceKeySizeInBuffer(Common::Types::ByteVector& buffer, const GetMessageRequest& message)
    {
        if (buffer.size() < CalculateTotalMessageSize(message))
        {
            throw std::runtime_error("Buffer size is too small to hold GetMessageRequest.");
        }

        auto key_size_offset = CalculateKeySizeOffset(message);
        MessageHelper::place32BitValueInByteBuffer(buffer, key_size_offset, message.getKey().size());
    }

    void GetMessageRequest::PlaceKeyDataInBuffer(Common::Types::ByteVector& buffer, const GetMessageRequest& message)
    {
        if (buffer.size() < CalculateTotalMessageSize(message))
        {
            throw std::runtime_error("Buffer size is too small to hold GetMessageRequest.");
        }

        auto key_data_offset = CalculateKeyDataOffset(message);
        MessageHelper::placeStringInByteBuffer(buffer, key_data_offset, message.getKey());
    }

    std::size_t GetMessageRequest::CalculateTotalMessageSize(const GetMessageRequest& message)
    {
        return Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES +
               GetMessageRequest::KEY_SIZE_IN_BYTES + message.getKey().size();
    }

    Common::Types::ByteVector GetMessageRequest::Serialize(const GetMessageRequest& message)
    {
        std::size_t size = CalculateTotalMessageSize(message);
        Common::Types::ByteVector buffer(size);

        MessageHelper::placeMessageSizeInByteBuffer(buffer, size);
        MessageHelper::placeMessageTypeInByteBuffer(buffer, MessageType::GET_MESSAGE);
        PlaceKeySizeInBuffer(buffer, message);
        PlaceKeyDataInBuffer(buffer, message);

        return buffer;
    }

    GetMessageRequest GetMessageRequest::Deserialize(const Common::Types::ByteVector& buffer)
    {
        auto message_size = MessageHelper::ExtractMessageSizeFromByteBuffer(buffer);
        auto type_size = MessageHelper::ExtractMessageTypeFromByteBuffer(buffer);
        auto key_size = ExtractKeySizeFromBuffer(buffer);
        auto key_data = ExtractKeyDataFromBuffer(buffer);

        return GetMessageRequest(key_data);
    }

    std::uint32_t GetMessageRequest::ExtractKeySizeFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET;
        return MessageHelper::Extract32BitValueFromByteBuffer(buffer, offset);
    }

    std::string GetMessageRequest::ExtractKeyDataFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET + GetMessageRequest::KEY_SIZE_IN_BYTES;
        auto string_size = ExtractKeySizeFromBuffer(buffer);

        return MessageHelper::ExtractStringFromByteBuffer(buffer, offset, string_size);
    }
}