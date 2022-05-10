#ifndef MONITOR_H
#define MONITOR_H

#include "IMonitor.h"
#include "httpget.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

class Monitor
{
public:
    SensorData getSensorData(std::string& ghId)
};

#endif // MONITOR_H
