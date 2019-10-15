#pragma once

#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "UsbSerialPortMesageReceiver.hpp"

namespace
{
const std::string home = getenv("HOME");
const std::string portDesignation = home + "/UsbSerialPortMesageReceiverTest.txt";
}

class UsbSerialPortMesageReceiverTest : public ::testing::Test
{
public:
    UsbSerialPortMesageReceiverTest()
        : _sut(portDesignation)
    {
        _portStub.open(portDesignation);
    }

    ~UsbSerialPortMesageReceiverTest()
    {
        std::remove(portDesignation.c_str());
    }

    void addMessageToPort(const std::string& message)
    {
        _portStub << message << std::endl;
    }

    UsbSerialPortMesageReceiver _sut;
    std::ofstream _portStub;
};
