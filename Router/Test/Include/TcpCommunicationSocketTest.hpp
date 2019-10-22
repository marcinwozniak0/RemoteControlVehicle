#pragma once

#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "TcpCommunicationSocket.hpp"

namespace
{
const std::string home = getenv("HOME");
const std::string portDesignation = home + "/TcpCommunicationSocketTest.txt";
}

class TcpCommunicationSocketTest : public ::testing::Test
{
public:
    TcpCommunicationSocketTest()
        : _sut(portDesignation)
    {
        _portStub.open(portDesignation);
    }

    ~TcpCommunicationSocketTest()
    {
        std::remove(portDesignation.c_str());
    }

    void addMessageToPort(const std::string& message)
    {
        _portStub << message << std::endl;
    }

    TcpCommunicationSocket _sut;
    std::ofstream _portStub;
};
