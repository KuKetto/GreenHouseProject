#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <iostream>

class Greenhouse
{
public:
    //auto generated setters & getters
    const std::string &getGhId() const;
    void setGhId(const std::string &newGhId);

    const std::string &getDescription() const;
    void setDescription(const std::string &newDescription);

    int getTemperature_min() const;
    void setTemperature_min(int newTemperature_min);

    int getTemperature_opt() const;
    void setTemperature_opt(int newTemperature_opt);

    int getHumidity_min() const;
    void setHumidity_min(int newHumidity_min);

    int getVolume() const;
    void setVolume(int newVolume);

private:
    std::string ghId;
    std::string description;
    int temperature_min;
    int temperature_opt;
    int humidity_min;
    int volume;
};

#endif // GREENHOUSE_H
