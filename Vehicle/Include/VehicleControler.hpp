#pragma once

#include <memory>
#include <queue>
#include <optional>

#include "UsbSerialPortMesageReceiver.hpp"
#include "Vehicle.hpp"

class PinValueSetter;

class VehicleControler
{
public:
    VehicleControler(CommunicationSocket&, Vehicle&, const PinValueSetter&);

    void controlVehicle();
    void vehicleEmergencyStop();  

private:
    std::optional<std::string> getMessageToExecute();
    void executeMessage(const std::string&);

    CommunicationSocket& _communicationSocket;
    Vehicle& _vehicle;
    const PinValueSetter& _pinValueSeter;

    bool _isControlerActive = false;
};
