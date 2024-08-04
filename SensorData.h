#ifndef SENSORDATA_H
#define SENSORDATA_H
#include "SensorMetric.h"
#include <QMap>
#include <QDateTime>
#include <QTextStream>
class SensorData
{
public:
    SensorData(const unsigned int max_elements, const QString& name);
    void insert(const SensorMetric& sm);
    QString getname();
    float max() const;
    float min()const;
    float average()const;
    float median()const;
    void print() const;


private:
    QMap<QDateTime, SensorMetric> sensorData;
    QString name;
    unsigned int max_elements;
    void clear();

};

#endif // SENSORDATA_H
