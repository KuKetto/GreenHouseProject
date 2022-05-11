#include "logger.h"

void Logger::log(const std::string &ghID, const std::string &token, const std::string &messageToLog)
{
    time_t currentDate = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
    std::string date = ctime(&currentDate);

    using namespace rapidjson;

    Value json_token(token.c_str(), token.length());
    Value json_errorMsg(messageToLog.c_str(), messageToLog.length());
    Value json_date(date.c_str(), date.length());

    Document logObject(kObjectType);
    logObject.AddMember("token", json_token, logObject.GetAllocator());
    logObject.AddMember("err_msg", json_errorMsg, logObject.GetAllocator());
    logObject.AddMember("date", json_date, logObject.GetAllocator());

    Document ghLog(kObjectType);
    Value json_ghID(ghID.c_str(), ghLog.GetAllocator());
    ghLog.AddMember(json_ghID, logObject, ghLog.GetAllocator());

    appendToFile(ghLog);
}

void Logger::appendToFile(const rapidjson::Document &value)
{
    using namespace rapidjson;

    // create file if it doesn't exist
    if (FILE* fp = fopen("log.json", "r"); !fp)
    {
        if (fp = fopen("log.json", "w"); !fp)
            return;
        fputs("[]", fp);
        fclose(fp);
    }

    // add the document to the file
    if (FILE* fp = fopen("log.json", "rb+"); fp)
    {
        // check if first is [
        std::fseek(fp, 0, SEEK_SET);
        if (getc(fp) != '[')
        {
            std::fclose(fp);
            return;
        }

        // is array empty?
        bool isEmpty = false;
        if (getc(fp) == ']')
            isEmpty = true;

        // check if last is ]
        std::fseek(fp, -1, SEEK_END);
        if (getc(fp) != ']')
        {
                std::fclose(fp);
                return;
        }

        // replace ] by ,
        fseek(fp, -1, SEEK_END);
        if (!isEmpty)
            fputc(',', fp);

        // append the document
        char writeBuffer[65536];
        FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        Writer<FileWriteStream> writer(os);
        value.Accept(writer);

        // close the array
        std::fputc(']', fp);
        fclose(fp);
        return;
    }
    return;
}
