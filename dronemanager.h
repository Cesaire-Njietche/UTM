#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QtMath>

#include "vehicleManager.h"
#include "drone.h"



#define DB "/home/katelynn/Desktop/Qt_Examples/UTM/data/drones.txt"

class droneManager : public QObject, public VehicleManager<Drone>
{
    Q_OBJECT
public:
    explicit droneManager(QObject *parent = nullptr);
    void pushback(Drone) override;
    QVector<Drone> pull ()override;
    void fetchDB() override;

public slots:
    void refresh();

signals:
    void preDroneAdded();
    void postDroneAdded();
private:
    QTimer *timer;

};

#endif // DRONEMANAGER_H
