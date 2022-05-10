#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData
{
private:
    std::string ghId;
    std::string token;
    double temperature_act;
    double humidity_act;
    bool boiler_on;
    bool sprinkler_on;
};

#endif // SENSORDATA_H
