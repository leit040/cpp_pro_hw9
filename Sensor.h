#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QString>
#include "SensorMetric.h"

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QObject *parent = nullptr, QString name = "default");
    void newData(float value);
private:
    QString name;


signals:
        void dataReady(const SensorMetric& aSensorMetric);
};

#endif // SENSOR_H
