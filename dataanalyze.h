//此类进行数据分析

#ifndef DATAANALYZE_H
#define DATAANALYZE_H

#include <QObject>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>


#ifdef __cplusplus
    #include <iostream>
#endif


class DataAnalyze : public QObject
{
    Q_OBJECT
public:
    explicit DataAnalyze(QList<QByteArray> byteArray,bool moreMessage,QObject *parent = 0);
    void Analyse();
signals:
    void finish();
public slots:

private:
    void analyseMessage_1(QByteArray array); //解析信息1
    void analyseMessage_2(QByteArray array); //解析信息2
    void analyseMore(QByteArray array);
//    void printfMessage(QString name,QString message);

    QList<QByteArray> byteArray;
    bool moreMessage;
};

#endif // DATAANALYZE_H
