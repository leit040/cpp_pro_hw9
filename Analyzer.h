#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QMap>
#include <QString>
#include "SensorMetric.h"
#include "SensorData.h"
#include "Config.hpp"
class Analyzer : public QObject
{
private:
    Q_OBJECT
    QMap<QString,SensorData> sensorData;
    Config* config;

public:
    explicit Analyzer(QObject *parent = nullptr, Config* _config = nullptr);
    void reportPrint() const;
    void reportPrint(QString name) const;
    void registerSensor(QString name);


public slots:
    void analyzeData(const SensorMetric& aSensorMetric);
};

#endif // ANALYZER_H
