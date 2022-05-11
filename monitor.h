#ifndef MONITOR_H
#define MONITOR_H

#include "IMonitor.h"
#include "httpget.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

class Monitor
{
public:
    SensorData getSensorData(const std::string& ghId);
private:
    rapidjson::Document getGreenHouseJson(const std::string& stringifiedJson);
    class parseErrorException : private std::exception {
        private:
            std::string errorMsg;
        public:
            parseErrorException(const std::string& errorMsg) : errorMsg(errorMsg) {};
            virtual const char* what() const throw() {
                return errorMsg.c_str();
            }
    };
};

#endif // MONITOR_H
