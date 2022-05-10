#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <iostream>

class SensorData
{
public:
    const std::string &getGhId() const;
    void setGhId(const std::string &newGhId);

    const std::string &getToken() const;
    void setToken(const std::string &newToken);

    double getTemperature_act() const;
    void setTemperature_act(double newTemperature_act);

    double getHumidity_act() const;
    void setHumidity_act(double newHumidity_act);

    bool getBoiler_on() const;
    void setBoiler_on(bool newBoiler_on);

    bool getSprinkler_on() const;
    void setSprinkler_on(bool newSprinkler_on);

private:
    std::string ghId;
    std::string token;
    double temperature_act;
    double humidity_act;
    bool boiler_on;
    bool sprinkler_on;
};

#endif // SENSORDATA_H
