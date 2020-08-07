#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "drone.h"
#include <QVector>

template <class K> class VehicleManager {

protected:
  QVector<K> _vec; // Vector of Drones/Vehicles
  int length;     // Number of Drones/Vehicles

public:
  int getSize() {
    return _vec.size();
  }

  virtual void pushback(K) = 0;
  virtual QVector<K> pull() = 0;
  virtual void fetchDB() = 0;

};
#endif // VEHICLEMANAGER_H
