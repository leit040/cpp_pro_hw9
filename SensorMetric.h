#ifndef SENSORMETRIC_H
#define SENSORMETRIC_H
#include <QString>
#include <QMetaType>
#include <QDateTime>

struct SensorMetric {
    QString name;
    QDateTime timestamp;
    int m_value;
    SensorMetric() : m_value(0) {}
    SensorMetric(const QString& name, int value) : name(name), timestamp(QDateTime::currentDateTime().addMSecs(value)), m_value(value) {}
};

Q_DECLARE_METATYPE(SensorMetric);
#endif // SENSORMETRIC_H
