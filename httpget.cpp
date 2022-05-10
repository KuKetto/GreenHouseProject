#include "httpget.h"

HTTPGet::HTTPGet(QObject *parent) : QObject(parent)
{

}

QString HTTPGet::method(const std::string &uri, const std::string &contentType, const QByteArray requestBody)
{
    QNetworkReply* reply = manager.get(QNetworkRequest(QUrl(QString::fromStdString(uri))));

    QEventLoop loop;

    connect(reply, &QNetworkReply::readyRead, this, &HTTPGet::readyRead);
    connect(reply , &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    reply->deleteLater();
    QString dataReply(data);
    qInfo() << data;
    return dataReply;
}

void HTTPGet::readyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) data = reply->readAll();
}
