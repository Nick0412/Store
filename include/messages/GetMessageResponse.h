#ifndef GET_MESSAGE_RESPONSE_H
#define GET_MESSAGE_RESPONSE_H

#include "MessageBase.h"
#include "common/Types.h"
#include <string>

namespace Messages
{
    /**
     * Represents a get message response. The data should be packed as so.
     * 
     * Message Size    | Message Type   | Get Result Size    | Get Result Data
     * ------------------------------------------------------------------------
     * 4 Bytes         | 4 Bytes        | 4 Bytes            | ??? Bytes   
     * 
     * The number of bytes for key data are given by key size.
     */
    class GetMessageResponse : public MessageBase<GetMessageResponse>
    {
    public:
        static constexpr std::size_t GET_RESULT_SIZE_IN_BYTES = 4;

        static Common::Types::ByteVector Serialize(const GetMessageResponse& message);
        static GetMessageResponse Deserialize(const Common::Types::ByteVector& buffer);

        GetMessageResponse() = delete;
        GetMessageResponse(const std::string& get_result);
        std::string getResult() const;

    private:
        std::string get_result;

        static std::size_t CalculateGetResultSizeOffset(const GetMessageResponse& message);
        static std::size_t CalculateGetResultDataOffset(const GetMessageResponse& message);
        static void PlaceGetResultSizeInBuffer(Common::Types::ByteVector& buffer, const GetMessageResponse& message);
        static void PlaceGetResultDataInBuffer(Common::Types::ByteVector& buffer, const GetMessageResponse& message);
        static std::size_t CalculateTotalMessageSize(const GetMessageResponse& message);
        static std::uint32_t ExtractGetResultSizeFromBuffer(const Common::Types::ByteVector& buffer);
        static std::string ExtractGetResultDataFromBuffer(const Common::Types::ByteVector& buffer);
    };
}

#endif