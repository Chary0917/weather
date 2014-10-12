#include <QNetworkAccessManager>
#include <QThread>
#include "weather.h"
#include "dataanalyze.h"

Weather::Weather(bool moreMessage,QString place,QObject *parent) :
    QObject(parent)
{
    this->place = place;
    this->moreMessage =moreMessage;
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(getCityInfo(QNetworkReply*)));

    if(needImportCityID()){
        fromFileToList();
        CityID = findIdByCityName(place);
        if(CityID.isEmpty()){
            qDebug() << "未找到城市，请确定是否正确输入";
            exit(1);
        }
    }

    connect(this,SIGNAL(initSender()),this,SLOT(beginSender()));


}


void Weather::ImportCityID(QString cityName,QString id)
{
    QPair<QString,QString> tempPair;
    tempPair.first = cityName;
    tempPair.second = id;

    cityList.append(tempPair);
}

//将文件导入导QList<QPair<...>>之中
void Weather::fromFileToList()
{
    QFile file(":/data/data/CityID");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Get City ID Error\n"
                 << file.errorString();
        exit(1);
    }

    QTextStream textStream(&file);
    QString line;
    QStringList list;
    do {
        line = textStream.readLine();
        list = line.split("=",QString::SkipEmptyParts);
        if(!list.isEmpty()){
            ImportCityID(list.at(0),list.at(1));
        }
    }while(!line.isNull());
    file.close();
}

//得到本地的城市ID号
void Weather::getLocalCityID()
{
   manager->get(QNetworkRequest(QUrl("http://61.4.185.48:81/g/")));
}

//通过城市名找到城市ID
QString Weather::findIdByCityName(QString cityName)
{
    QPair<QString,QString> city;
    foreach (city, cityList) {
        if(city.second == cityName){
            return city.first;
        }
    }
    return NULL;
}


//获得天气数据
void Weather::getWeather()
{
    if(CityID.isEmpty()){
        getLocalCityID();
    } else{
        beginSender();
    }

}


//得到服务器返回的本地城市ID
void Weather::getCityInfo(QNetworkReply *reply)
{
    QByteArray byteArray = reply->readAll();
    QString strScript(byteArray);
    QStringList list = strScript.split(";");
    if(list.count() > 2){
        QStringList idList = list.at(1).split("=");
        CityID = idList.at(1);
        emit initSender();
    }
}

void Weather::receiveData(QList<QByteArray> byteArray)
{
    DataAnalyze *anlyze = new DataAnalyze(byteArray,moreMessage);
    connect(anlyze,SIGNAL(finish()),this,SLOT(finish()));
    anlyze->Analyse();
}

void Weather::finish()
{
    emit getWeatherFinished();
}

void Weather::beginSender()
{
    sender = new Sender(CityID);
    connect(sender,SIGNAL(sendData(QList<QByteArray>)),
            this,SLOT(receiveData(QList<QByteArray>)));
    sender->Send();
}

//判断是否需要导入城市ID,如果是本地的话，就不需要
bool Weather::needImportCityID()
{
    if(place.isEmpty())
        return false;
    else
        return true;
}
