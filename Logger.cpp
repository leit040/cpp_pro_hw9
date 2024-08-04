#include "Logger.h"
#include <QDebug>
#include <QDateTime>

Logger::Logger(QObject *parent)    : QObject(parent), logFile(QDateTime::currentDateTime().toString()+"_data.log") {
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qWarning() << "Cannot open log file for writing:" << logFile.errorString();
    }
}
void Logger::writeData(const SensorMetric& aSensorMetric) {
    if (!logFile.isOpen() || !logFile.isWritable()) {
        qWarning() << "Log file is not open or not writable";
        return;
    }

    QTextStream out(&logFile);
    QString timestamp = aSensorMetric.timestamp.toString("yyyy-MM-dd HH:mm:ss");
    QString logEntry = QString("%1 | name=%2 | value=%3")
                           .arg(timestamp)
                           .arg(aSensorMetric.name)
                           .arg(aSensorMetric.m_value);

    out << logEntry << Qt::endl;
}
