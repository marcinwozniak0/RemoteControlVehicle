#pragma once

template <typename T>
class MessageBuilder
{
public:
    virtual T build() const = 0;

    virtual ~MessageBuilder() = default;
};
