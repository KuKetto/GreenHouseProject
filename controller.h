#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loader.h"
#include "driver.h"
#include "monitor.h"
#include "logger.h"
#include <map>
#include <algorithm>
#include <cmath>

class Controller
{
public:
    Controller();

    struct resultStruct {
      int HTTPResponse;
      std::string description;
      std::string greenHouseID;
      std::string token;
      double temperatureIncrease;
      double sprinklerIncrease;
    };

    std::vector<resultStruct> execute();
private:
    //variables
    std::map<int, double> temperatureHumidityTable;
    std::pair<int, int> temperatureHumidityTableRange;


    //classes
    Loader greenHouseListInitailizer;
    Monitor greenHouseCurrentState;
    Driver greenHouseCommandSystem;
    Logger logger;


    //controller ptivate functions
    resultStruct makeResultStruct(int HTTPResponse, std::string description, std::string greenHouseID,
                              std::string token, double temperatureIncrease, double sprinklerIncrease);
    GreenHouseList greenHouseList;
    std::pair<std::string, std::pair<double, double>> defineGreenHouseJob(const Greenhouse& gh);
    void initalizeTemperatureHumidityTable();
    void checkForDeviceError(const Greenhouse& gh, const SensorData& sD);


    //exception handling
    class NoHumidityForTemperature : private std::exception {
        private:
            bool temp_toLow;
        public:
            NoHumidityForTemperature(const bool& temp_toLow) : temp_toLow(temp_toLow) {};
            virtual const char* what() const throw() {
                return temp_toLow ? "Az adott hőmérséklet túl alacsony, nincs hozzá páratartalmi adat"
                                  : "Az adott hőmérséklet túl magas, nincs hozzá páratartalmi adat";
            }
    };
};

#endif // CONTROLLER_H
