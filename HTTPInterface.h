#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <QString>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

class HTTPInterface {
    virtual QString method(const std::string& uri, const std::string& contentType = std::string(), const QByteArray requestBody = QByteArray()) = 0;
};

#endif // HTTPINTERFACE_H
