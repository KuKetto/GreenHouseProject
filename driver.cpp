#include "driver.h"

int Driver::sendCommand(const Greenhouse &gh, const std::string &token, const double &boilerValue, const double &sprinklerValue)
{
    std::string jsonRequestString = boilerValue == 0 && sprinklerValue == 0 ?
    stringifyJSON(mapData(
       gh.getGhId(),
       "",
       ""
    )) : stringifyJSON(mapData(
       gh.getGhId(),
       "bup" + std::to_string((int)round(boilerValue)) + "c",
       "son" + std::to_string((int)round(sprinklerValue)) + "l"
    ));

    HTTPPost post;
    return post.method("http://193.6.19.58:8181/greenhouse/" + token, "text/plain", QByteArray::fromStdString(jsonRequestString)).toInt();
}

rapidjson::Document Driver::mapData(const std::string& ghId, const std::string& boilerCommand, const std::string& sprinklerCommand)
{
    using namespace rapidjson;

    Document doc;
    doc.SetObject();

    Value json_ghId(ghId.c_str(), ghId.length());
    Value json_boilerCommand(boilerCommand.c_str(), boilerCommand.length());
    Value json_sprinklerCommand(sprinklerCommand.c_str(), sprinklerCommand.length());

    doc.AddMember("ghId", json_ghId, doc.GetAllocator());
    doc.AddMember("boilerCommand", json_boilerCommand, doc.GetAllocator());
    doc.AddMember("sprinklerCommand", json_sprinklerCommand, doc.GetAllocator());

    return doc;
}

std::string Driver::stringifyJSON(const rapidjson::Document &doc)
{
    using namespace rapidjson;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    return buffer.GetString();
}
