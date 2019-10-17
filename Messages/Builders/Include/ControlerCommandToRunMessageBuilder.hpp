#pragma once

#include "MessageBuilder.hpp"
#include "VehicleTypes.hpp"

class ControlerCommandToRunMessageBuilder : public MessageBuilder
{
public:
    ControlerCommandToRunMessageBuilder(const PinsConfiguration&);
    google::protobuf::Any buildMessage() const override;

private:
    const PinsConfiguration& _pinsConfigurationToSend;
};
