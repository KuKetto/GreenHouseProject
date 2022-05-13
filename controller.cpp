#include "controller.h"

Controller::Controller()
{
    greenHouseList = greenHouseListInitailizer.loadGreenHouses();
    initalizeTemperatureHumidityTable();
}

std::vector<Controller::resultStruct> Controller::execute()
{
    std::vector<resultStruct> resultVector;

    for (auto& greenHouse : greenHouseList.getGreenhouseList()) {
        try {
            std::pair<std::string, std::pair<double, double>> commands = defineGreenHouseJob(greenHouse); 
            int response =
                  greenHouseCommandSystem.sendCommand(greenHouse, commands.first, commands.second.first, commands.second.second);
            resultVector.push_back(makeResultStruct(response, greenHouse.getDescription(), greenHouse.getGhId(),
                                                    commands.first, commands.second.first, commands.second.second));
        }  catch (std::exception &ex) {
            qInfo() << ex.what();
            resultVector.push_back(makeResultStruct(0, greenHouse.getDescription(), ex.what(),
                                                    "-", 0, 0));
        }
    }

    return resultVector;
}

Controller::resultStruct Controller::makeResultStruct(int HTTPResponse, std::string description, std::string greenHouseID, std::string token, double temperatureIncrease, double sprinklerIncrease)
{
    resultStruct newResultStruct = {
        HTTPResponse,
        description,
        greenHouseID,
        token,
        temperatureIncrease,
        sprinklerIncrease
    };
    return newResultStruct;
}

std::pair<std::string, std::pair<double, double>> Controller::defineGreenHouseJob(const Greenhouse &gh)
{
    SensorData sensorData;
    sensorData = greenHouseCurrentState.getSensorData(gh.getGhId());

    //check for device error + check if current temp is defined in temperatureHumidityTable
    checkForDeviceError(gh, sensorData);
    if (sensorData.getTemperature_act() < temperatureHumidityTableRange.first) throw NoHumidityForTemperature(true);
    else if (sensorData.getTemperature_act() > temperatureHumidityTableRange.second) throw NoHumidityForTemperature(false);

    if (sensorData.getBoiler_on() || sensorData.getSprinkler_on()) {
        //previous command under execution, nothing to do
        return std::pair<std::string, std::pair<double, double>>(sensorData.getToken(), std::pair<double, double>(0,0));
    }
    if (sensorData.getTemperature_act() < gh.getTemperature_min()) {
        //temperature is under minimum, should increase it to optimal level
        int currentTemperature = round(sensorData.getTemperature_act());
        double hummidityDifferenceBetweenActualAndOptimal =
                temperatureHumidityTable[gh.getTemperature_opt()] * gh.getHumidity_min()
                - temperatureHumidityTable[currentTemperature] *  sensorData.getHumidity_act();
        if (hummidityDifferenceBetweenActualAndOptimal > 0) {
            //hummidity will not be high enough in case of temperature increase to optimal level
            double waterToSprinkle = (hummidityDifferenceBetweenActualAndOptimal * gh.getVolume())/1000;
            qInfo() << "\n" << gh.getTemperature_opt() - sensorData.getTemperature_act() << " c : " << hummidityDifferenceBetweenActualAndOptimal << " - " << waterToSprinkle << "\n";
            return std::pair<std::string, std::pair<double, double>>(sensorData.getToken(),
                        std::pair<double, double>(gh.getTemperature_opt() - sensorData.getTemperature_act(), waterToSprinkle));
        }
        //enough hummidity to maintain minimum hummidity level in case of temperature increase to optimal level
        qInfo() << "\n" << gh.getTemperature_opt() - sensorData.getTemperature_act() << " c : " << hummidityDifferenceBetweenActualAndOptimal << "\n";
        return std::pair<std::string, std::pair<double, double>>(sensorData.getToken(),
                    std::pair<double, double>(gh.getTemperature_opt() - sensorData.getTemperature_act(), 0));
    }
    //temperature level is higher than minimal
    int currentTemperature = round(sensorData.getTemperature_act());
    double hummidityDifferenceBetweenActualAndRequired =
            temperatureHumidityTable[currentTemperature] * gh.getHumidity_min()
            - temperatureHumidityTable[currentTemperature] *  sensorData.getHumidity_act();
    if (hummidityDifferenceBetweenActualAndRequired > 0) {
        //hummidity is too low in current temperature
        return std::pair<std::string, std::pair<double, double>>(sensorData.getToken(),
                    std::pair<double, double>(0, (hummidityDifferenceBetweenActualAndRequired * gh.getVolume())/1000));
    }
    //hummidity level is OK as well
    return std::pair<std::string, std::pair<double, double>>(sensorData.getToken(), std::pair<double, double>(0,0));
}

void Controller::initalizeTemperatureHumidityTable()
{
    temperatureHumidityTable = {
                {20, 17.3},
                {21, 18.5},
                {22, 19.7},
                {23, 20.9},
                {24, 22.1},
                {25, 23.3},
                {26, 24.7},
                {27, 26.1},
                {28, 27.5},
                {29, 28.9},
                {30, 30.3},
                {31, 31.9},
                {32, 33.5},
                {33, 35.1},
                {34, 36.7},
                {35, 38.3},
        };
    temperatureHumidityTableRange.first = min_element(temperatureHumidityTable.cbegin(), temperatureHumidityTable.cend(),
                                                      [](const std::pair<int,double>& kvp, const std::pair<int,double>& kvp2){
                                                      return kvp.first < kvp2.first;
                                           })->first;
    temperatureHumidityTableRange.second = max_element(temperatureHumidityTable.cbegin(), temperatureHumidityTable.cend(),
                                                       [](const std::pair<int,double>& kvp, const std::pair<int,double>& kvp2){
                                                       return kvp.first < kvp2.first;
    })->first;
}

void Controller::checkForDeviceError(const Greenhouse &gh, const SensorData &sD)
{
    std::string toLogMessage;

    //check for boiler error
    if (gh.getTemperature_min() - sD.getTemperature_act() >= 5) {
        //temperature too low
        logger.log(gh.getGhId(), sD.getToken(), "A hőmérséklet vészesen alacsony! Az elvárt "
                    + std::to_string(gh.getTemperature_min()) + " celsius fokhoz képest csak "
                    + std::to_string(round(sD.getTemperature_act())) + " celsius fok van");
    } else if (sD.getTemperature_act() - gh.getTemperature_opt() >= 5) {
        //temperature too high
        logger.log(gh.getGhId(), sD.getToken(), "A hőmérséklet vészesen magas! A hőmérséklet bőven az optimális "
                    + std::to_string(gh.getTemperature_opt()) + " celsius fok felett van, jelenleg "
                    + std::to_string(sD.getTemperature_act()) + " celsius fok");
    }

    //check for sprinkler error
    if (gh.getHumidity_min() - sD.getHumidity_act() >= 20) {
        //hummidity too low
        logger.log(gh.getGhId(), sD.getToken(), "A páratartalom vészesen alacsony! Az elvárt "
                    + std::to_string(gh.getHumidity_min()) + "% helyett mindössze csak "
                    + std::to_string((int)round(sD.getHumidity_act())) + "%-os páratartalmú a levegő");
    } else if (sD.getHumidity_act() - gh.getHumidity_min() >= 20) {
        //hummidty too high
        logger.log(gh.getGhId(), sD.getToken(), "A páratartalom vészesen magas! Az elvárt "
                    + std::to_string(gh.getHumidity_min()) + "%-ot bőven meghaladja, jelenleg "
                    + std::to_string((int)round(sD.getHumidity_act())) + "%-os páratartalmú a levegő");
    }

    //if toLogMessage not empty call log function else do nothing
}
