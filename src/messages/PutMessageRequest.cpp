#include "messages/PutMessageRequest.h"
#include "messages/Constants.h"
#include "messages/MessageHelper.h"

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

    std::size_t PutMessageRequest::GetKeySizeOffset(const PutMessageRequest& request)
    {
        return Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES;
    }

    std::size_t PutMessageRequest::GetKeyDataOffset(const PutMessageRequest& request)
    {
        return PutMessageRequest::KEY_SIZE_BYTES + PutMessageRequest::GetKeySizeOffset(request);
    }

    std::size_t PutMessageRequest::GetValueSizeOffset(const PutMessageRequest& request)
    {
        return request.getKey().size() + PutMessageRequest::GetKeyDataOffset(request);
    }

    std::size_t PutMessageRequest::GetValueDataOffset(const PutMessageRequest& request)
    {
        return PutMessageRequest::VALUE_SIZE_BYTES + PutMessageRequest::GetValueSizeOffset(request);
    }

    void PutMessageRequest::PlaceKeySizeInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request)
    {
        auto offset = PutMessageRequest::GetKeySizeOffset(request);
        MessageHelper::place32BitValueInByteBuffer(buffer, offset, request.getKey().size());
    }

    void PutMessageRequest::PlaceKeyDataInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request)
    {
        auto offset = PutMessageRequest::GetKeyDataOffset(request);
        MessageHelper::placeStringInByteBuffer(buffer, offset, request.getKey());
    }

    void PutMessageRequest::PlaceValueSizeInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request)
    {
        auto offset = PutMessageRequest::GetValueSizeOffset(request);
        MessageHelper::place32BitValueInByteBuffer(buffer, offset, request.getValue().size());
    }

    void PutMessageRequest::PlaceValueDataInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request)
    {
        auto offset = PutMessageRequest::GetValueDataOffset(request);
        MessageHelper::placeStringInByteBuffer(buffer, offset, request.getValue());
    }

    /**
     * Expected format should be:
     * | message size | message type | key size | key data | value size | value data |
     * |   4 bytes    |    4 bytes   | 4 bytes  | x bytes  |   4 bytes  |  x bytes   |
     * 
     * Places the data in the byte buffer in network byte order.
     */
    Common::Types::ByteVector PutMessageRequest::Serialize(const PutMessageRequest& request)
    {
        std::size_t message_size_in_bytes = Constants::MESSAGE_SIZE_BYTES + Constants::MESSAGE_TYPE_BYTES +
            PutMessageRequest::KEY_SIZE_BYTES + request.getKey().size() +
            PutMessageRequest::VALUE_SIZE_BYTES + request.getValue().size();
        
        Common::Types::ByteVector buffer(message_size_in_bytes);
        MessageHelper::placeMessageSizeInByteBuffer(buffer, message_size_in_bytes);
        MessageHelper::placeMessageTypeInByteBuffer(buffer, MessageType::PUT_MESSAGE);
        PutMessageRequest::PlaceKeySizeInByteBuffer(buffer, request);
        PutMessageRequest::PlaceKeyDataInByteBuffer(buffer, request);
        PutMessageRequest::PlaceValueSizeInByteBuffer(buffer, request);
        PutMessageRequest::PlaceValueDataInByteBuffer(buffer, request);

        return buffer;
    }

    /**
     * Assumes that all the data in the byte buffer is in network byte order. 
     * TODO: Determine if this byte data should have the size and type in it or if it should be
     * stripped before it enters this function.
     */
    PutMessageRequest PutMessageRequest::Deserialize(const Common::Types::ByteVector& request_data)
    {
        // TODO: Implementation
        // std::uint32_t size_network_order = request_data[0] || (request_data[1] << 8) ||
        //     (request_data[2] << 16) || (request_data[3] << 24);
        // std::uint32_t size_host_order = ntohl(size_network_order);

        // std::uint32_t type_network_order = request_data[4] || (request_data[5] << 8) ||
        //     (request_data[6] << 16) || (request_data[7] << 24);
        // std::uint32_t type_host_order = ntohl(type_network_order);
    }
}