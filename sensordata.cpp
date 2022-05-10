#include "sensordata.h"

const std::string &SensorData::getGhId() const
{
    return ghId;
}

void SensorData::setGhId(const std::string &newGhId)
{
    ghId = newGhId;
}

const std::string &SensorData::getToken() const
{
    return token;
}

void SensorData::setToken(const std::string &newToken)
{
    token = newToken;
}

double SensorData::getTemperature_act() const
{
    return temperature_act;
}

void SensorData::setTemperature_act(double newTemperature_act)
{
    temperature_act = newTemperature_act;
}

double SensorData::getHumidity_act() const
{
    return humidity_act;
}

void SensorData::setHumidity_act(double newHumidity_act)
{
    humidity_act = newHumidity_act;
}

bool SensorData::getBoiler_on() const
{
    return boiler_on;
}

void SensorData::setBoiler_on(bool newBoiler_on)
{
    boiler_on = newBoiler_on;
}

bool SensorData::getSprinkler_on() const
{
    return sprinkler_on;
}

void SensorData::setSprinkler_on(bool newSprinkler_on)
{
    sprinkler_on = newSprinkler_on;
}
