#ifndef DRONE_H
#define DRONE_H
#include<QGeoCoordinate>
#include "vehicle.h"
enum class State { OnGround, Hover, Cruising };

enum class Status { Connected, Disconnected };

enum class Type { DJI, Parrot, SkyDio, Yuneec };

class Drone : public Vehicle {
  float _alt;
  Type _type;
  Status _status;
  State _state;

public:
  // Constructor
  Drone(QString id, QString m, Type tp) : Vehicle(id, m) {
    _type = tp;
    _status = Status::Disconnected;
    _state = State::OnGround;
  }

  Drone() {}
  QGeoCoordinate toQGeoCoordinate(){return QGeoCoordinate(gps().lat, gps().lon);}

  // Setters
  void Alt(float a) { _alt = a; }
  void status(Status s) { _status = s; }
  void state(State s) { _state = s; }

  // Getters
  float Alt() const{ return _alt; }
  Type type() const { return _type; }
  State state() const{ return _state; }
  Status status() const{ return _status; }
};
#endif // DRONE_H
