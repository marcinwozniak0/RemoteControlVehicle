#pragma once

#include <string>
#include <google/protobuf/any.pb.h>

namespace UTHelpers
{
google::protobuf::Any createDeactivateCommand();
google::protobuf::Any createUserCommandToStart(int);
google::protobuf::Any createUserCommandToStop(int);
google::protobuf::Any createUnknownCommand();
google::protobuf::Any createUserCommandToRun(int32_t, int32_t, int);
google::protobuf::Any createRegisterVehicleCommand(int);
google::protobuf::Any createRegisterUserCommand(int);
}//UTHelpers
