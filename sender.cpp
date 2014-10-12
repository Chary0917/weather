#include "sender.h"

Sender::Sender(QString cityId,QObject *parent) :
    QObject(parent),CityId(cityId)
{
    num = 0;
    realweather_str = "http://www.weather.com.cn/data/cityinfo/";
    realweather2_str = "http://www.weather.com.cn/data/sk/";
    moreweather_str = "http://www.weather.com.cn/data/zs/";
    Manager = new QNetworkAccessManager;
    connect(Manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(receiveData(QNetworkReply*)));
    connect(this,SIGNAL(receiveFinish(int)),this,SLOT(continueSend(int)));
}

void Sender::Send()
{
    QString str_1 = realweather_str + CityId +".html";
    Manager->get(QNetworkRequest(QUrl(str_1)));
}

void Sender::receiveData(QNetworkReply *reply)
{
    messageArray.append(reply->readAll());
    emit receiveFinish(++num);
}

void Sender::continueSend(int n)
{

    if(n == 1){
        QString str_2 =realweather2_str + CityId +".html";
        Manager->get(QNetworkRequest(QUrl(str_2)));
    } else if(n == 2) {
        QString str_more = moreweather_str + CityId + ".html";
        Manager->get(QNetworkRequest(QUrl(str_more)));
    } else
        emit sendData(messageArray);
}




