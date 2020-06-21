#pragma once

class CommandSender 
{
public:
    virtual bool sendCommand(google::protobuf::Any&&) = 0;

    virtual ~CommandSender() = default;
};
