#ifndef PUT_MESSAGE_REQUEST_H
#define PUT_MESSAGE_REQUEST_H

#include "common/Types.h"
#include <string>

namespace Messages
{
    class PutMessageRequest 
    {
    private:
        std::string key;
        std::string value;

    public:
        static Common::Types::ByteVector Serialize(const PutMessageRequest& request);
        static PutMessageRequest Deserialize(const Common::Types::ByteVector& request_data);

        static constexpr std::size_t KEY_SIZE_BYTES = 4;
        static constexpr std::size_t VALUE_SIZE_BYTES = 4;

        // TODO: Should these be member functions maybe?
        static std::size_t GetKeySizeOffset(const PutMessageRequest& request);
        static std::size_t GetKeyDataOffset(const PutMessageRequest& request);
        static std::size_t GetValueSizeOffset(const PutMessageRequest& request);
        static std::size_t GetValueDataOffset(const PutMessageRequest& request);

        static void PlaceKeySizeInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request);
        static void PlaceKeyDataInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request);
        static void PlaceValueSizeInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request);
        static void PlaceValueDataInByteBuffer(Common::Types::ByteVector& buffer, const PutMessageRequest& request);

    public:
        PutMessageRequest() = delete;
        PutMessageRequest(const std::string& key, const std::string& value);

        std::string getKey() const;
        std::string getValue() const;

    };
}

#endif