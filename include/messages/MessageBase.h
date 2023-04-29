#ifndef MESSAGE_TEMPLATE_H
#define MESSAGE_TEMPLATE_H

#include "common/Types.h"
#include "MessageHelper.h"

namespace Messages
{
    /**
     * The first goal was to apply a constraint to the class template argument. An example might be
     * we have a constraint like `concept HasSerializable` which would represent a constraint
     * that return true if a template argument has a serializable function. It could be used like
     * 
     * template <HasSerializable MessageType>
     * class MessageBase ...
     * 
     * However this causes issues for derived classed if we use CRTP. If we do the following
     * 
     * class ExampleMessage : public MessageBase<ExampleMessage>
     * 
     * this causes an error because right when the compiler sees `MessageBase<ExampleMessage>`
     * it will begin checking the constraint. This means that it checks the constarint even before
     * ExampleMessage is fully defined. So even if ExampleMessage has a serialize function this
     * fails. 
     * 
     * Thus we push the template constraint onto the functions because they will not be
     * checked until they are called.
     */
    template <typename MessageType>
    class MessageBase
    {
    public:
        // Delay template inspection until the function is called.
        template <MessageHelper::HasSerialize T = MessageType>
        static Common::Types::ByteVector Serialize(const T& message)
        {
            return T::Serialize(message);
        }

        template <MessageHelper::HasDeserialize T = MessageType>
        static T Deserialize(const Common::Types::ByteVector& byte_buffer)
        {
            return T::Deserialize(byte_buffer);
        }
    };
}

#endif