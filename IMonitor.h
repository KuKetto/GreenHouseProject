#ifndef IMONITOR_H
#define IMONITOR_H

#include "sensordata.h"

class IMonitor {
    SensorData getSensorData(std::string& ghId);
};

#endif // IMONITOR_H
