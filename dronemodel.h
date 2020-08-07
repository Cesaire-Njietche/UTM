#ifndef DRONEMODEL_H
#define DRONEMODEL_H

#include <QAbstractItemModel>
#include <QAbstractListModel>

#include "dronemanager.h"


class droneModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(droneManager *droneManager READ getDroneManager WRITE setDroneManager)

public:
    explicit droneModel(QObject *parent = nullptr);
    ~droneModel(){}

    enum{
      RegRole =  Qt::UserRole + 1,
      TypeRole,
      LatRole,
      LongRole,
      AltRole
    };

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    droneManager *getDroneManager() const;
    void setDroneManager(droneManager *value);

private:
    droneManager *dm;
};

#endif // DRONEMODEL_H
