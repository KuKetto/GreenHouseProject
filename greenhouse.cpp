#include "greenhouse.h"

const std::string &Greenhouse::getGhId() const
{
    return ghId;
}

void Greenhouse::setGhId(const std::string &newGhId)
{
    ghId = newGhId;
}

const std::string &Greenhouse::getDescription() const
{
    return description;
}

void Greenhouse::setDescription(const std::string &newDescription)
{
    description = newDescription;
}

int Greenhouse::getTemperature_min() const
{
    return temperature_min;
}

void Greenhouse::setTemperature_min(int newTemperature_min)
{
    temperature_min = newTemperature_min;
}

int Greenhouse::getTemperature_opt() const
{
    return temperature_opt;
}

void Greenhouse::setTemperature_opt(int newTemperature_opt)
{
    temperature_opt = newTemperature_opt;
}

int Greenhouse::getHumidity_min() const
{
    return humidity_min;
}

void Greenhouse::setHumidity_min(int newHumidity_min)
{
    humidity_min = newHumidity_min;
}

int Greenhouse::getVolume() const
{
    return volume;
}

void Greenhouse::setVolume(int newVolume)
{
    volume = newVolume;
}
