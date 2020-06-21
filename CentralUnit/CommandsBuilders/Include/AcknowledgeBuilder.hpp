#pragma once

#include <Acknowledge.pb.h>

#include "MessageBuilder.hpp"

class AcknowledgeBuilder : public MessageBuilder<Commands::Acknowledge>
{
public:
    Commands::Acknowledge build() const override;
    AcknowledgeBuilder status(Commands::Status);
    AcknowledgeBuilder additionalInformation(const std::string&);

private:
    Commands::Acknowledge _acknowledge;
};
