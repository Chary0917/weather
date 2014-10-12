#include <QDebug>
#include <QVariant>
#include "dataanalyze.h"

DataAnalyze::DataAnalyze(QList<QByteArray> byteArray,bool moreMessage,QObject *parent) :
    QObject(parent)
{
    this->byteArray = byteArray;
    this->moreMessage = moreMessage;
}


void DataAnalyze::Analyse()
{
    analyseMessage_1(byteArray.at(0));
    std::cout <<"******************************\n";
    analyseMessage_2(byteArray.at(1));
    std::cout <<"******************************\n";
    if(moreMessage){
        analyseMore(byteArray.at(2));
//        std::cout <<"******************************\n";
    }
    emit finish();
}

void DataAnalyze::analyseMessage_1(QByteArray byte_array)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);

    if(json_error.error == QJsonParseError::NoError) {
        if(parse_doucment.isObject()){
            QJsonObject obj = parse_doucment.object().take("weatherinfo").toObject();
            if(obj.contains("city"))  {
                QJsonValue name_value = obj.take("city");
                if(name_value.isString()){
                   std::cout<<"城市名："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("temp1"))  {
                QJsonValue name_value = obj.take("temp1");
                if(name_value.isString()){
                   std::cout<<"温度1："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("temp2"))  {
                QJsonValue name_value = obj.take("temp2");
                if(name_value.isString()){
                   std::cout<<"温度2："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("weather"))  {
                QJsonValue name_value = obj.take("weather");
                if(name_value.isString()){
                   std::cout<<"天气状况："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
        }
    }
}

void DataAnalyze::analyseMessage_2(QByteArray byte_array)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError) {
        if(parse_doucment.isObject()){
            QJsonObject obj = parse_doucment.object().take("weatherinfo").toObject();
            if(obj.contains("temp"))  {
                QJsonValue name_value = obj.take("temp");
                if(name_value.isString()){
                   std::cout<<"实时温度："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("WD"))  {
                QJsonValue name_value = obj.take("WD");
                if(name_value.isString()){
                   std::cout<<"风向："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("WS"))  {
                QJsonValue name_value = obj.take("WS");
                if(name_value.isString()){
                   std::cout<<"大小(风)："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("SD"))  {
                QJsonValue name_value = obj.take("SD");
                if(name_value.isString()){
                   std::cout<<"湿度："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("njd"))  {
                QJsonValue name_value = obj.take("njd");
                if(name_value.isString()){
                   std::cout<<"实况信息："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }
            if(obj.contains("SD"))  {
                QJsonValue name_value = obj.take("SD");
                if(name_value.isString()){
                   std::cout<<"湿度："<< qPrintable(name_value.toString())
                              <<std::endl;
                }
            }

        }
    }
}

void DataAnalyze::analyseMore(QByteArray byte_array)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array, &json_error);
    if(json_error.error == QJsonParseError::NoError) {
        if(parse_doucment.isObject()){
            QJsonObject obj = parse_doucment.object().take("zs").toObject();
             QJsonObject::const_iterator iterator;
             QString str;
             iterator = obj.begin();
             for(++iterator;iterator != obj.end();iterator++){
                 if(iterator.key().contains(QRegExp("._des")))
                     std::cout << "[" <<qPrintable(iterator.value().toString()) <<"]\n";
                 if(iterator.key().contains(QRegExp("._name")))
                     std::cout << qPrintable(iterator.value().toString()) << ":"
                               << qPrintable(str);
                 if(iterator.key().contains(QRegExp("._hint")))
                     str = iterator.value().toString();
             }
        }
    }
}

//void DataAnalyze::printfMessage(QJsonObject obj, QString name)
//{
//    if(obj.contains(name))  {
//        QJsonValue name_value = obj.take(name);
//        if(name_value.isString()){
//           std::cout<<"实时温度："<< qPrintable(name_value.toString())
//                      <<std::endl;
//        }
//    }
//}
