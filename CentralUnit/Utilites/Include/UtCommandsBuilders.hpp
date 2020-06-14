#pragma once

#include <string>

struct ThreeWheeledVehicleConfiguration;

namespace google::protobuf
{
struct Any;
}

namespace UTHelpers
{
google::protobuf::Any createDeactivateCommand();
google::protobuf::Any createUserCommandToStart(int);
google::protobuf::Any createUserCommandToStop(int);
google::protobuf::Any createUnknownCommand();
google::protobuf::Any createUserCommandToRun(int32_t, int32_t, int);
google::protobuf::Any createRegisterVehicleCommand(int);
google::protobuf::Any createRegisterUserCommand(int);
ThreeWheeledVehicleConfiguration createThreeWheeledVehicleConfiguration();
}//UTHelpers
