#pragma once

#include <google/protobuf/any.pb.h>

#include "VehicleTypes.hpp"

class CommunicationSocket;
class Vehicle;

class VehicleControler
{
public:
    VehicleControler(CommunicationSocket&, Vehicle&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    void handleMessage(const std::string&);
    void handleUserCommandToRun(const google::protobuf::Any&) const;
    template <typename Command> void sendCommand(const Command&) const;
    void clearPinsValues(PinsConfiguration&) const;

    CommunicationSocket& _communicationSocket;
    Vehicle& _vehicle;

    bool _isControlerActive = false;
};
