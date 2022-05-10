#include "httppost.h"

HTTPPost::HTTPPost(QObject *parent) : QObject(parent)
{

}

QString HTTPPost::method(const std::string &uri, const std::string &contentType, const QByteArray requestBody)
{
    QNetworkRequest request = QNetworkRequest(QUrl(QString::fromStdString(uri)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString::fromStdString(contentType));
    QNetworkReply* reply = manager.post(request, requestBody);

    QEventLoop loop;

    connect(reply, &QNetworkReply::readyRead, this, &HTTPPost::readyRead);
    connect(reply , &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();
    reply->deleteLater();
    QString dataReply(data);
    return dataReply;
}

void HTTPPost::readyRead()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply) data = reply->readAll();
}
