#ifndef IMONITOR_H
#define IMONITOR_H

#include "sensordata.h"

class IMonitor {
    virtual SensorData getSensorData(const std::string& ghId) = 0;
};

#endif // IMONITOR_H
