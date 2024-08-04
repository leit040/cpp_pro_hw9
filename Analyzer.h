#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "SensorMetric.h"
#include "SensorData.h"
class Analyzer : public QObject
{
private:
    Q_OBJECT
    QMap<QString,SensorData> sensorData;

public:
    explicit Analyzer(QObject *parent = nullptr);
    void reportPrint() const;
    void reportPrint(QString name) const;
    void registerSensor(QString name);


public slots:
    void analyzeData(const SensorMetric& aSensorMetric);
};

#endif // ANALYZER_H
