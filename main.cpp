/*********************************************************************
 *  Name:main.cpp
 *  Description: weather [选项] [参数]
 *               -p [地点]   //显示指定地点天气
 *               -m         //详细信息
 *               -h         //显示帮助信息
 * *******************************************************************/

#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <QObject>

#ifdef __cplusplus
    #include <iostream>
#endif

#include "weather.h"


struct Arg{
    bool moreFlag;
    QString place;
    bool Empty;
};


void printHelp()
{
    std::cout  << "weather [选项] [参数]\n"
               << "-p [地点]   //显示指定地点天气\n"
               << "-m         //显示详细天气信息\n"
               << "-h         //显示帮助信息\n"
               << "[注]：默认显示ip所在地简单的天气信息\n";
}



void dealArguments(QStringList list,struct Arg *argument)
{

    argument->Empty = true;
    argument->moreFlag=false;
    argument->place="";
    if(list.count() == 1){
            return;
    } else {
        argument->Empty = false;
        for(int i=0;i<list.count();i++){
            if(list.at(i) == "-m"){
                argument->moreFlag = true;
            }
            if(list.at(i) == "-p"){
                for(int j = i+1;j < list.count();j++){
                    if(list.at(j) != "-p" && list.at(j) != "-m"
                            && list.at(j) != "-mp")
                        argument->place = list.at(j);
                }
            }
            if(list.at(i) == "-mp"){
                argument->moreFlag = true;
                for(int j = i+1;j < list.count();j++){
                    if(list.at(j) != "-p" && list.at(j) != "-m"
                            && list.at(j) != "-mp")
                        argument->place = list.at(j);
                }
            }
        }
    }
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList argumentList = QCoreApplication::arguments();

    //判断是否有-h参数
    if(argumentList.contains("-h") || argumentList.count() > 4){
         printHelp();
         a.quit();
    }

    struct Arg argument;
    dealArguments(argumentList,&argument);
//    qDebug() <<argument.moreFlag << argument.place;
    Weather *weather = new Weather(argument.moreFlag,argument.place);
    QObject::connect(weather,SIGNAL(getWeatherFinished()),&a,SLOT(quit()));
    weather->getWeather();


    return a.exec();
}
