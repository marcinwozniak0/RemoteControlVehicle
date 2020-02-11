#pragma once

#include <boost/asio.hpp>
#include <gtest/gtest.h>

#include "TcpCommunicationSocket.hpp"

namespace
{
static constexpr auto port = 35271;
static constexpr auto ipAddress = "127.0.0.1";
}

class DISABLED_TcpCommunicationSocketTest : public ::testing::Test
{
public:
    void addMessageToPort(const std::string& message)
    {}

    std::unique_ptr<TcpCommunicationSocket> _sut;
};
