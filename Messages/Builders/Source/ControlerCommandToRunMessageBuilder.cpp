#include "ControlerCommandToRun.pb.h"

#include "ControlerCommandToRunMessageBuilder.hpp"

ControlerCommandToRunMessageBuilder ControlerCommandToRunMessageBuilder::pinsConfiguration(const PinsConfiguration& configuration)
{
    _pinsConfiguration = configuration;
    return *this;
}

google::protobuf::Any ControlerCommandToRunMessageBuilder::build() const
{
    Messages::ControlerCommandToRun controlerCommandToStart;
    auto& pinsConfiguration = *controlerCommandToStart.mutable_pins_configuration();

    for(const auto& [pinNumber, pinValue] : _pinsConfiguration)
    {
        pinsConfiguration.insert({pinNumber, pinValue});
    }

    google::protobuf::Any topLevelMessage;
    topLevelMessage.PackFrom(controlerCommandToStart);

    return topLevelMessage;
}
