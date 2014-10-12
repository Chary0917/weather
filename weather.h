#ifndef WEATHER_H
#define WEATHER_H


#include <QObject>
#include <QString>
#include <QPair>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>


#include "sender.h"

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(bool moreMessage = false,
                     QString place = QString(),
                     QObject *parent = 0);

    void getWeather();
    void setPlace(QString place){ this->place = place;}
    void setMoreFlag(bool moreFlag){ this->moreMessage = moreFlag;}
signals:
    void getWeatherFinished();
    void initSender();
public slots:
    void getCityInfo(QNetworkReply *reply);
    void receiveData(QList<QByteArray> byteArray);
    void finish();
    void beginSender();
private:
    bool needImportCityID();
    void ImportCityID(QString cityName,QString id);
    void fromFileToList();
    void getLocalCityID();
    QString findIdByCityName(QString cityName);

    Sender *sender;
    QString CityID;
    QString place;
    bool moreMessage;
    QList<QPair<QString,QString> > cityList;
    QNetworkAccessManager *manager;
};

#endif // WEATHER_H
