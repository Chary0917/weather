/* 构造一个类进行数据的发送及接收*/

#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>


class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QString cityId,QObject *parent = 0);

    void Send();

signals:
    void sendData(QList<QByteArray> byteArray);
    void receiveFinish(int n);
public slots:
    void receiveData(QNetworkReply *);
    void continueSend(int n);
private:
    int num;
    QString CityId;
    QNetworkAccessManager *Manager;

    QString realweather_str;
    QString realweather2_str;
    QString moreweather_str;

    QList<QByteArray> messageArray;
};

#endif // SENDER_H
