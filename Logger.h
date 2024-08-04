#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "SensorMetric.h"
#include"SensorMetric.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

public slots:
    void writeData(const SensorMetric& aSensorMetric);
private:
    QFile logFile;
};



#endif // LOGGER_H
