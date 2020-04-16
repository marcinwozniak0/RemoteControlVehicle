#pragma once

#include "ControlerCommandToRun.pb.h"

#include "MessageBuilder.hpp"
#include "VehicleTypes.hpp"

class ControlerCommandToRunMessageBuilder : public MessageBuilder
{
public:
    google::protobuf::Any build() const override;
    ControlerCommandToRunMessageBuilder pinsConfiguration(const PinsConfiguration&);
    ControlerCommandToRunMessageBuilder vehicleId(const int);

private:
    Commands::ControlerCommandToRun _controlerCommandToStart;
};
