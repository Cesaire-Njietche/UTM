#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

using namespace std;

// Float Attributes
struct GPS {
  double lat;
  double lon;
  GPS(double la, double lo) : lat(la), lon(lo) {}
  GPS() {}
};

class Vehicle {
public:
  // Constructor
  Vehicle(QString id, QString m) :_manufacturer(m), _id(id) {}

  Vehicle() {}

  // Setters
  void Manufacturer(QString m) { _manufacturer = m; }
  void ID(QString id) { _id = id; }
  void Timestamp(QString ts) { _timestamp = ts; }
  void gps(GPS gps) { _gps = gps; }

  // Getters
  QString Manufacturer() const { return _manufacturer; }
  QString ID() const { return _id; }
  QString Timestamp() const { return _timestamp; }
  GPS gps() const{ return _gps; }

private:
  // QString Attributes
  QString _manufacturer;
  QString _id;
  QString _timestamp;

  // GPS
  GPS _gps;
};
#endif // VEHICLE_H
