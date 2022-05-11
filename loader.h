#ifndef LOADER_H
#define LOADER_H

#include "ILoader.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include "httpget.h"

class Loader : public ILoader
{
public:
    GreenHouseList loadGreenHouses();
private:
    rapidjson::Document getGreenHouseListJson(const QString& stringifiedJson);
    Greenhouse fetchGreenhouseFromJson(rapidjson::Value& greenHouseJsonObject);
    //parse exception
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

#endif // LOADER_H
