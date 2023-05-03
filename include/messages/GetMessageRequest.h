#ifndef GET_MESSAGE_H
#define GET_MESSAGE_H

#include "MessageBase.h"
#include <string>

namespace Messages
{
    /**
     * Represents a get message request. The data should be packed as so.
     * 
     * Message Size    | Message Type   | Key Size    | Key Data
     * ------------------------------------------------------------
     * 4 Bytes         | 4 Bytes        | 4 Bytes     | ??? Bytes   
     * 
     * The number of bytes for key data are given by key size.
     */
    class GetMessageRequest : public MessageBase<GetMessageRequest>
    {
    public:
        static constexpr std::size_t KEY_SIZE_IN_BYTES = 4;

        static Common::Types::ByteVector Serialize(const GetMessageRequest& message);
        static GetMessageRequest Deserialize(const Common::Types::ByteVector& buffer);

        GetMessageRequest() = delete;
        GetMessageRequest(const std::string& key);
        std::string getKey() const;


    private:
        std::string key;

        static std::size_t CalculateKeySizeOffset(const GetMessageRequest& message);
        static std::size_t CalculateKeyDataOffset(const GetMessageRequest& message);
        static void PlaceKeySizeInBuffer(Common::Types::ByteVector& buffer, const GetMessageRequest& message);
        static void PlaceKeyDataInBuffer(Common::Types::ByteVector& buffer, const GetMessageRequest& message);
        static std::size_t CalculateTotalMessageSize(const GetMessageRequest& message);
        static std::uint32_t ExtractKeySizeFromBuffer(const Common::Types::ByteVector& buffer);
        static std::string ExtractKeyDataFromBuffer(const Common::Types::ByteVector& buffer);
    };

}

#endif