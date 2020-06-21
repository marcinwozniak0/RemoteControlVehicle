#include <google/protobuf/any.pb.h>

#include "ControlerCommandToRunMessageBuilder.hpp"

ControlerCommandToRunMessageBuilder ControlerCommandToRunMessageBuilder::pinsConfiguration(const PinsConfiguration& configuration)
{
    auto& pinsConfiguration = *_controlerCommandToStart.mutable_pins_configuration();

    for(const auto& [pinNumber, pinValue] : configuration)
    {
        pinsConfiguration.insert({pinNumber, pinValue});
    }

    return *this;
}

ControlerCommandToRunMessageBuilder ControlerCommandToRunMessageBuilder::vehicleId(const int vehicleId)
{
    _controlerCommandToStart.set_vehicle_id(vehicleId);
    return *this;
}

google::protobuf::Any ControlerCommandToRunMessageBuilder::build() const
{
    google::protobuf::Any topLevelMessage;
    topLevelMessage.PackFrom(_controlerCommandToStart);

    return topLevelMessage;
}
