#ifndef IDRIVER_H
#define IDRIVER_H

#include <iostream>
#include "greenhouse.h"

class IDriver {
public:
    virtual int sendCommand(const Greenhouse& gh, const std::string& token, const double& boilerValue, const double& sprinklerValue) = 0;
};

#endif // IDRIVER_H
