#pragma once

#include "Engine.hpp"

class DcEngine : public Engine
{
public:
    DcEngine(const uint8_t, const uint8_t, const uint8_t);

    void setPinsConfiguration(const PinsConfiguration&) override;
    const PinsConfiguration& getPinsConfiguration() const override;

private:
    PinsConfiguration _pinsConfiguration;
};
