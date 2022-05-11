#ifndef LOGGERINTERFACE_H
#define LOGGERINTERFACE_H

#include <iostream>

class LoggerInterface {
    virtual void log(const std::string& ghID,const std::string& token, const std::string& messageToLog) = 0;
};

#endif // LOGGERINTERFACE_H
