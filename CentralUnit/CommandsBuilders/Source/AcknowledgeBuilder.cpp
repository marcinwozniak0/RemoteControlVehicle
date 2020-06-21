#include "AcknowledgeBuilder.hpp"

Commands::Acknowledge AcknowledgeBuilder::build() const
{
    return _acknowledge;
}

AcknowledgeBuilder AcknowledgeBuilder::status(const Commands::Status status)
{
    _acknowledge.set_status(status);
    return *this;
}

AcknowledgeBuilder AcknowledgeBuilder::additionalInformation(const std::string& additionalInfo)
{
    _acknowledge.set_additional_info(additionalInfo);
    return *this;
}
