#ifndef HTTPPOST_H
#define HTTPPOST_H

#include <QObject>
#include "HTTPInterface.h"

class HTTPGet : public QObject, public HTTPInterface
{
    Q_OBJECT
public:
    explicit HTTPGet(QObject *parent = nullptr);
    QString method(const std::string& uri, const std::string& contentType = nullptr, const QByteArray requestBody = nullptr);
private slots:
    void readyRead();
private:
    QNetworkAccessManager manager;
    QByteArray data;

};

#endif // HTTPPOST_H
