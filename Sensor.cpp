#include "Sensor.h"

Sensor::Sensor(QObject *parent, QString name)
    : QObject{parent}, name(name)
{}
void Sensor::newData(float value){
    emit dataReady(SensorMetric(name, value));
}
