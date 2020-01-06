#pragma once

#include <google/protobuf/message_lite.h>
#include <string>

namespace CommandDebuger
{
namespace
{
template <typename Command>
std::string getCommanNameFromTopLevelCommand(const Command& command)
{
    const auto commandAsString = command.ShortDebugString();
    const auto beginOfCommandName = commandAsString.find_first_of('/') + 1;
    const auto endOfCommandName = commandAsString.find_first_of(']');

    if (std::string::npos == endOfCommandName or std::string::npos == beginOfCommandName)
    {
        return "Unknown.Command";
    }
    else
    {
        return {commandAsString.begin() + beginOfCommandName,
                commandAsString.begin() + endOfCommandName};
    }
}    
}//namespace

template <typename Command>
std::string getCommandName(const Command& command)
{
    const auto commandType = command.GetTypeName();

    if( "google.protobuf.Any" == commandType)
    {
        return getCommanNameFromTopLevelCommand(command);
    }
    else
    {
        return commandType;
    }

}
}//CommandDebuger