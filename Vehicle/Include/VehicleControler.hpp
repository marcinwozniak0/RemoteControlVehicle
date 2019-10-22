#pragma once

#include <memory>
#include <queue>
#include <optional>

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
    void executeMessage(const std::string&);

    CommunicationSocket& _communicationSocket;
    Vehicle& _vehicle;

    bool _isControlerActive = false;
};
