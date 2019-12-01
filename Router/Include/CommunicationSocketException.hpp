#pragma once

#include <exception>

class CommunicationSocketException : public std::exception
{
public:
    CommunicationSocketException(std::string_view what)
        : _what(what)
    {}

    const char* what() const noexcept override
    {
        return _what.c_str();
    }

private:
    const std::string _what;
};
