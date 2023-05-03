#ifndef PUT_MESSAGE_H
#define PUT_MESSAGE_H

#include "MessageBase.h"
#include <string>

namespace Messages
{
    /**
     * Represents a put message request. The data should be packed as so
     * 
     * Message Size    | Message Type    | Key Size    | Key Data      | Value Size    | Value Data
     * -----------------------------------------------------------------------------------------------
     * 4 Bytes         | 4 Bytes         | 4 Bytes     | ??? Bytes     | 4 Bytes       | ??? Bytes
     * 
     * - Key Data: relies on Key Size
     * - Value Data: relies on Value Size
     * 
     */
    class PutMessageRequest : public MessageBase<PutMessageRequest>
    {
    public:
        static constexpr std::size_t KEY_SIZE_IN_BYTES = 4;
        static constexpr std::size_t VALUE_SIZE_IN_BYTES = 4;

        static Common::Types::ByteVector Serialize(const PutMessageRequest& message);
        static PutMessageRequest Deserialize(const Common::Types::ByteVector& buffer);

        PutMessageRequest() = delete;
        PutMessageRequest(const std::string& key, const std::string& value);
        std::string getKey() const;
        std::string getValue() const;

    private:
        std::string key;
        std::string value;

        static std::size_t CalculateKeySizeOffset(const PutMessageRequest& message);
        static std::size_t CalculateKeyDataOffset(const PutMessageRequest& message);
        static std::size_t CalculateValueSizeOffset(const PutMessageRequest& message);
        static std::size_t CalculateValueDataOffset(const PutMessageRequest& message);
        static std::size_t CalculateTotalMessageSize(const PutMessageRequest& message);
        static void PlaceKeySizeInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message);
        static void PlaceKeyDataInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message);
        static void PlaceValueSizeInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message);
        static void PlaceValueDataInBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& message);
        static std::uint32_t ExtractKeySizeFromBuffer(const Common::Types::ByteVector& buffer);
        static std::string ExtractKeyDataFromBuffer(const Common::Types::ByteVector& buffer);
        static std::uint32_t ExtractValueSizeFromBuffer(const Common::Types::ByteVector& buffer);
        static std::string ExtractValueDataFromBuffer(const Common::Types::ByteVector& buffer);
    };
}

#endif