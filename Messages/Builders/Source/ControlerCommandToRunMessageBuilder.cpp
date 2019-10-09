#include "ControlerCommandToRun.pb.h"

#include "ControlerCommandToRunMessageBuilder.hpp"

ControlerCommandToRunMessageBuilder::ControlerCommandToRunMessageBuilder(const PinsConfiguration& pinsConfigurationToSend)
    : _pinsConfigurationToSend(pinsConfigurationToSend)
{}

google::protobuf::Any ControlerCommandToRunMessageBuilder::buildMessage() const
{
    Messages::ControlerCommandToRun controlerCommandToStart;
    auto& pinsConfigurationToSend = *controlerCommandToStart.mutable_pins_configuration();

    for(const auto& [pinNumber, pinValue] : _pinsConfigurationToSend)
    {
        pinsConfigurationToSend.insert({pinNumber, pinValue});
    }

    google::protobuf::Any topLevelMessage;
    topLevelMessage.PackFrom(controlerCommandToStart);

    return topLevelMessage;
}
