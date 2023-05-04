#include "messages/GetMessageResponse.h"
#include "messages/Constants.h"
#include "messages/MessageHelper.h"

namespace Messages
{
    GetMessageResponse::GetMessageResponse(const std::string& get_result)
    : get_result{get_result}
    {

    }

    std::string GetMessageResponse::getResult() const
    {
        return get_result;
    }

    std::size_t GetMessageResponse::CalculateGetResultSizeOffset(const GetMessageResponse& message)
    {
        return Constants::MESSAGE_DATA_OFFSET;
    }

    std::size_t GetMessageResponse::CalculateGetResultDataOffset(const GetMessageResponse& message)
    {
        return Constants::MESSAGE_DATA_OFFSET + GET_RESULT_SIZE_IN_BYTES;
    }

    void GetMessageResponse::PlaceGetResultSizeInBuffer(Common::Types::ByteVector& buffer, const GetMessageResponse& message)
    {
        // TODO: Check buffer sizes and whatnot
        auto offset = CalculateGetResultSizeOffset(message);
        MessageHelper::place32BitValueInByteBuffer(buffer, offset, message.getResult().size());
    }

    void GetMessageResponse::PlaceGetResultDataInBuffer(Common::Types::ByteVector& buffer, const GetMessageResponse& message)
    {
        auto offset = CalculateGetResultDataOffset(message);
        MessageHelper::placeStringInByteBuffer(buffer, offset, message.getResult());
    }

    std::size_t GetMessageResponse::CalculateTotalMessageSize(const GetMessageResponse& message)
    {
        return Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES +
               GET_RESULT_SIZE_IN_BYTES + message.getResult().size();
    }

    std::uint32_t GetMessageResponse::ExtractGetResultSizeFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_DATA_OFFSET;
        return MessageHelper::Extract32BitValueFromByteBuffer(buffer, offset);
    }

    std::string GetMessageResponse::ExtractGetResultDataFromBuffer(const Common::Types::ByteVector& buffer)
    {
        auto offset = Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES +
                      GET_RESULT_SIZE_IN_BYTES;
        auto string_size = ExtractGetResultSizeFromBuffer(buffer);

        return MessageHelper::ExtractStringFromByteBuffer(buffer, offset, string_size);
    }

    Common::Types::ByteVector GetMessageResponse::Serialize(const GetMessageResponse& message)
    {
        auto message_size = CalculateTotalMessageSize(message);
        Common::Types::ByteVector buffer(message_size);

        MessageHelper::placeMessageSizeInByteBuffer(buffer, message_size);
        MessageHelper::placeMessageTypeInByteBuffer(buffer, MessageType::GET_MESSAGE_RESPONSE);
        PlaceGetResultSizeInBuffer(buffer, message);
        PlaceGetResultDataInBuffer(buffer, message);

        return buffer;
    }

    GetMessageResponse GetMessageResponse::Deserialize(const Common::Types::ByteVector& buffer)
    {
        auto get_result = ExtractGetResultDataFromBuffer(buffer);

        return GetMessageResponse{get_result};
    }
}