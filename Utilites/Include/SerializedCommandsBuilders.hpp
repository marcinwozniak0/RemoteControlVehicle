#pragma once

#include <string>

namespace UTHelpers
{
const std::string createSerializedDeactivateMessage();
const std::string createSerializedUserCommandToStart();
const std::string createSerializedUserCommandToStop();
const std::string createSerializedUserCommandToRun(const int32_t, const int32_t);
}//UTHelpers
