#pragma once

#include <type_traits>
#include <google/protobuf/message.h>

template <typename T, typename = typename std::enable_if<std::is_base_of<google::protobuf::Message, T>::value>::type >
class MessageBuilder
{
public:
    virtual T build() const = 0;

    virtual ~MessageBuilder() = default;
};
