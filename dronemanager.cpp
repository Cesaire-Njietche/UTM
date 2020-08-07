#include "dronemanager.h"

#include <iostream>


droneManager::droneManager(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &droneManager::refresh);
    timer->start(1000); //Update the drone list every 1 seconds
}

QVector<Drone> droneManager::pull(){

    return _vec;
}

void droneManager::pushback(Drone d){

    _vec.append(d);
}

void droneManager::fetchDB(){

       QFile file(DB);
       if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

       _vec.clear();

       QTextStream in(&file);
       float alt;
       double lat, lon;
       QString type, id;
       while(!in.atEnd()){
           QString line = in.readLine();
           auto s_list = line.split(':');
           if(s_list.at(0).compare("Alt") == 1)
               alt = s_list.at(1).toFloat();
           else if (s_list.at(0).compare("Lat") == 1)
               lat = s_list.at(1).toDouble();
           else if (s_list.at(0).compare("Lon") == 1)
               lon = s_list.at(1).toDouble();
           else if (s_list.at(0).compare("Type") == 1)
               type = s_list.at(1);
           else
               id = s_list.at(1);
       }

       // For this particular case, a one pass through is necessary to get all the data

       file.close();

       Drone drone(id, type, type.compare("Parrot")==0?Type::Parrot:Type::DJI);
       GPS gps(lat, lon);
       drone.gps(gps);

       drone.Alt(alt);

       /*qDebug() << "ID :" + id;
       qDebug() << "Type :" + type;
       qDebug() << lat;
       qDebug() << lon;*/
       qDebug() << alt;


       emit preDroneAdded();
       pushback(drone);
       emit postDroneAdded();

}

void droneManager::refresh(){
    fetchDB();
}
