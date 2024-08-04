#include "Analyzer.h"
#include <QDebug>
#include "Config.hpp"

Analyzer::Analyzer(QObject *parent)
    : QObject{parent}{
}

void Analyzer::reportPrint() const{
    for (auto it = sensorData.cbegin(); it != sensorData.cend(); ++it) {
        QString key = it.key();
        SensorData value = it.value();
        value.print();
    }
}
void Analyzer::reportPrint(QString name) const{
    const auto it = sensorData.find(name);
    if (it != sensorData.end()) {
        const SensorData& value = it.value();
        value.print();
    } else {
        qWarning() << "Sensor data not found for key:" << name;
    }
    }

void Analyzer::registerSensor(QString name){
    sensorData.insert(name,SensorData(MAX_ELEMENTS,name));
}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric){
    if(!sensorData.contains(aSensorMetric.name))
    {
        registerSensor(aSensorMetric.name);
    }
    auto it = sensorData.find(aSensorMetric.name);
    SensorData& value = it.value();
    value.insert(aSensorMetric);
    value.print();
}
