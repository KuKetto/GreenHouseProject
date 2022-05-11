#ifndef HTTPPOST_H
#define HTTPPOST_H

#include <QObject>
#include "HTTPInterface.h"

class HTTPPost : public QObject, public HTTPInterface
{
    Q_OBJECT
public:
    explicit HTTPPost(QObject *parent = nullptr);
    QString method(const std::string& uri, const std::string& contentType = std::string(), const QByteArray requestBody = QByteArray());
private slots:
    void readyRead();
private:
    QNetworkAccessManager manager;
    QByteArray data;

};

#endif // HTTPPOST_H
