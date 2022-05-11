#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerInterface.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <chrono>
#include <ctime>

class Logger : public LoggerInterface
{
public:
    void log(const std::string& ghID,const std::string& token, const std::string& messageToLog);
private:
    void appendToFile(const rapidjson::Document& value);
};

#endif // LOGGER_H
