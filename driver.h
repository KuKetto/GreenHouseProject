#ifndef DRIVER_H
#define DRIVER_H

#include "IDriver.h"
#include "httppost.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>

class Driver : public IDriver
{
public:
    int sendCommand(Greenhouse& gh, const std::string& token, const double& boilerValue, const double& sprinklerValue);
private:
    rapidjson::Document mapData(const std::string& ghId, const std::string& boilerCommand, const std::string& sprinklerCommand);
    std::string stringifyJSON(const rapidjson::Document& doc);
};

#endif // DRIVER_H
