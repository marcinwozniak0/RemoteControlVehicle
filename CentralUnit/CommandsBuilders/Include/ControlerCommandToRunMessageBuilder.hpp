#pragma once

#include <google/protobuf/any.pb.h>
#include <ControlerCommandToRun.pb.h>

#include "MessageBuilder.hpp"
#include "VehicleTypes.hpp"

namespace google::protobuf
{
class Any;
}

class ControlerCommandToRunMessageBuilder : public MessageBuilder<google::protobuf::Any>
{
public:
    google::protobuf::Any build() const override;
    ControlerCommandToRunMessageBuilder pinsConfiguration(const PinsConfiguration&);
    ControlerCommandToRunMessageBuilder vehicleId(const int);

private:
    Commands::ControlerCommandToRun _controlerCommandToStart;
};
