#include "loader.h"

GreenHouseList Loader::loadGreenHouses()
{
    std::vector<Greenhouse> greenHouseList;

    HTTPGet get;
    std::string stringifiedJson = get.method("http://193.6.19.58:8181/greenhouse").toStdString();
    rapidjson::Document parsedJson = getGreenHouseListJson(stringifiedJson);

    for (unsigned int i = 0; i < parsedJson["greenhouseList"].Size(); i++) {
        greenHouseList.push_back(
            fetchGreenhouseFromJson(parsedJson["greenhouseList"][i])
        );
    }

    GreenHouseList GHL;
    GHL.setGreenhouseList(greenHouseList);
    return GHL;
}

rapidjson::Document Loader::getGreenHouseListJson(const std::string& stringifiedJson)
{
    using namespace rapidjson;

    Document doc;
    ParseResult parseResult = doc.Parse(stringifiedJson.c_str());

    if (!parseResult) { //check parse errors
      throw parseErrorException(GetParseError_En(parseResult.Code()));
    }

    return doc;
}

Greenhouse Loader::fetchGreenhouseFromJson(rapidjson::Value &greenHouseJsonObject)
{
    Greenhouse gh;
    gh.setGhId(greenHouseJsonObject["ghId"].GetString());
    gh.setDescription(greenHouseJsonObject["description"].GetString());
    gh.setTemperature_min(greenHouseJsonObject["temperature_min"].GetInt());
    gh.setTemperature_opt(greenHouseJsonObject["temperature_opt"].GetInt());
    gh.setHumidity_min(greenHouseJsonObject["humidity_min"].GetInt());
    gh.setVolume(greenHouseJsonObject["volume"].GetInt());
    return gh;
}
