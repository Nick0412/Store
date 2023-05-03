#include "messages/PutMessageRequest.h"
#include "messages/Constants.h"

namespace Messages
{
    PutMessageRequest::PutMessageRequest(const std::string& key, const std::string& value)
    : key{key}, value{value}
    {

    }

    std::string PutMessageRequest::getKey() const
    {
        return key;
    }


    std::string PutMessageRequest::getValue() const
    {
        return value;
    }

    std::size_t PutMessageRequest::CalculateKeySizeOffset(const PutMessageRequest& message)
    {
        return Constants::MESSAGE_DATA_OFFSET;
    }

    std::size_t PutMessageRequest::CalculateKeyDataOffset(const PutMessageRequest& message)
    {
        auto offset = CalculateKeySizeOffset(message) + PutMessageRequest::KEY_SIZE_IN_BYTES;
        return offset;
    }

    std::size_t PutMessageRequest::CalculateValueSizeOffset(const PutMessageRequest& message)
    {
        auto offset = CalculateKeyDataOffset(message) + message.getKey().size();
        return offset;
    }

    std::size_t PutMessageRequest::CalculateValueDataOffset(const PutMessageRequest& message)
    {
        auto offset = CalculateValueSizeOffset(message) + PutMessageRequest::VALUE_SIZE_IN_BYTES;
        return offset;
    }

    std::size_t PutMessageRequest::CalculateTotalMessageSize(const PutMessageRequest& message)
    {
        return Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES +
               PutMessageRequest::KEY_SIZE_IN_BYTES + message.getKey().size() +
               PutMessageRequest::VALUE_SIZE_IN_BYTES + message.getValue().size();
    }

    void PutMessageRequest::PlaceKeySizeInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message)
    {
        // TODO: Buffer checking for all "Place*" functions
        auto offset = CalculateKeySizeOffset(message);
        MessageHelper::place32BitValueInByteBuffer(buffer, offset, message.getKey().size());
    }

    void PutMessageRequest::PlaceKeyDataInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message)
    {
        auto offset = CalculateKeyDataOffset(message);
        MessageHelper::placeStringInByteBuffer(buffer, offset, message.getKey());
    }

    void PutMessageRequest::PlaceValueSizeInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message)
    {
        auto offset = CalculateValueSizeOffset(message);
        MessageHelper::place32BitValueInByteBuffer(buffer, offset, message.getValue().size());
    }

    void PutMessageRequest::PlaceValueDataInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message)
    {
        auto offset = CalculateValueDataOffset(message);
        MessageHelper::placeStringInByteBuffer(buffer, offset, message.getValue());
    }

    std::uint32_t PutMessageRequest::ExtractKeySizeFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET;
        return MessageHelper::Extract32BitValueFromByteBuffer(buffer, offset);
    }

    std::string PutMessageRequest::ExtractKeyDataFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET + PutMessageRequest::KEY_SIZE_IN_BYTES;
        auto string_size = ExtractKeySizeFromBuffer(buffer);

        return MessageHelper::ExtractStringFromByteBuffer(buffer, offset, string_size);
    }

    std::uint32_t PutMessageRequest::ExtractValueSizeFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET + PutMessageRequest::KEY_SIZE_IN_BYTES +
                      ExtractKeySizeFromBuffer(buffer);

        return MessageHelper::Extract32BitValueFromByteBuffer(buffer, offset);
    }

    std::string PutMessageRequest::ExtractValueDataFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET + PutMessageRequest::KEY_SIZE_IN_BYTES +
                      ExtractKeySizeFromBuffer(buffer) + PutMessageRequest::VALUE_SIZE_IN_BYTES;
        auto string_size = ExtractValueSizeFromBuffer(buffer);

        return MessageHelper::ExtractStringFromByteBuffer(buffer, offset, string_size);
    }

    Common::Types::ByteVector PutMessageRequest::Serialize(const PutMessageRequest& message)
    {
        auto message_size = CalculateTotalMessageSize(message);
        Common::Types::ByteVector buffer(message_size);

        MessageHelper::placeMessageSizeInByteBuffer(buffer, message_size);
        MessageHelper::placeMessageTypeInByteBuffer(buffer, MessageType::PUT_MESSAGE);
        PlaceKeySizeInBuffer(buffer, message);
        PlaceKeyDataInBuffer(buffer, message);
        PlaceValueSizeInBuffer(buffer, message);
        PlaceValueDataInBuffer(buffer, message);

        return buffer;
    }

    PutMessageRequest PutMessageRequest::Deserialize(const Common::Types::ByteVector& buffer)
    {
        auto key = ExtractKeyDataFromBuffer(buffer);
        auto value = ExtractValueDataFromBuffer(buffer);

        return PutMessageRequest{key, value};
    }
}