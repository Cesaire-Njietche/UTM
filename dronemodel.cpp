#include "dronemodel.h"

droneModel::droneModel(QObject *parent)
    : QAbstractListModel(parent),
      dm(nullptr)
{
}

int droneModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()|| !dm)
        return 0;

    return dm->pull().size();
}

QVariant droneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() or !dm)
        return QVariant();

    const Drone drone = dm->pull().at(index.row());
    Type typ = drone.type();

    QString type = typ == Type::Parrot?"Parrot":"DJI";
    switch (role) {
    case RegRole:
        return QVariant(drone.ID());
    case TypeRole:
        return QVariant(type);
    case LatRole:
        return QVariant(drone.gps().lat);
    case LongRole:
        return QVariant(drone.gps().lon);
    case AltRole:
        return QVariant(drone.Alt());

    }
    return QVariant();
}

QHash<int, QByteArray> droneModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names[RegRole] = "Registration";
    names[TypeRole] = "Type";
    names[LatRole] = "Latitude";
    names[LongRole] = "Longitude";
    names[AltRole] = "Altitude";

    return names;
}

droneManager *droneModel::getDroneManager() const
{
    return dm;
}

void droneModel::setDroneManager(droneManager *value)
{

    if(dm)
        dm->disconnect(this);
    dm = value;
    if(dm){
        connect(dm, &droneManager::preDroneAdded, this, [=](){
            beginResetModel();
        });
        connect(dm, &droneManager::postDroneAdded, this, [=](){
            endResetModel();
        });
    }
}
