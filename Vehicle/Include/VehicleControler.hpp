#pragma once

#include <google/protobuf/any.pb.h>

#include "TcpCommunicationSocket.hpp"
#include "Vehicle.hpp"

class PinValueSetter;

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

    CommunicationSocket& _communicationSocket;
    Vehicle& _vehicle;

    bool _isControlerActive = false;
};
