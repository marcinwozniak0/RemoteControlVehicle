#pragma once

#include "MessageBuilder.hpp"
#include "VehicleTypes.hpp"

class ControlerCommandToRunMessageBuilder : public MessageBuilder
{
public:
    google::protobuf::Any build() const override;
    ControlerCommandToRunMessageBuilder pinsConfiguration(const PinsConfiguration&);

private:
    PinsConfiguration _pinsConfiguration;
};
