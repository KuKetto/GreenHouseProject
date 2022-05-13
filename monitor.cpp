#include "monitor.h"

SensorData Monitor::getSensorData(const std::string &ghId)
{
    HTTPGet get;

    //for testing purposes only!
    //std::string stringifiedJson = get.method("https://saydo.me/" + ghId + ".json").toStdString();

    std::string stringifiedJson = get.method("http://193.6.19.58:8181/greenhouse/" + ghId).toStdString();
    rapidjson::Document parsedJson = getGreenHouseJson(stringifiedJson);

    SensorData sensorData;
    sensorData.setGhId(parsedJson["ghId"].GetString());
    sensorData.setToken(parsedJson["token"].GetString());
    sensorData.setTemperature_act(parsedJson["temperature_act"].GetDouble());
    sensorData.setHumidity_act(parsedJson["humidity_act"].GetDouble());
    sensorData.setBoiler_on(parsedJson["boiler_on"].GetBool());
    sensorData.setSprinkler_on(parsedJson["sprinkler_on"].GetBool());

    return sensorData;
}

rapidjson::Document Monitor::getGreenHouseJson(const std::string &stringifiedJson)
{
    using namespace rapidjson;

    Document doc;
    ParseResult parseResult = doc.Parse(stringifiedJson.c_str());

    if (!parseResult) { //check parse errors
      throw parseErrorException(GetParseError_En(parseResult.Code()));
    }

    return doc;
}
