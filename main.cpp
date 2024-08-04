#include <QCoreApplication>
#include <QRandomGenerator>
#include "Analyzer.h"
#include "Logger.h"
#include "Sensor.h"
#include "Config.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Analyzer analyzer;
    Logger logger;
    Sensor sensor1(nullptr,"sensor1");
    Sensor sensor2(nullptr,"sensor2");
    Sensor sensor3(nullptr,"sensor3");
    QObject::connect(&sensor1, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);
    QObject::connect(&sensor2, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);
    QObject::connect(&sensor3, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);
    QObject::connect(&sensor1, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&sensor2, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&sensor3, &Sensor::dataReady, &logger, &Logger::writeData);
    QRandomGenerator *randomGenerator;
    randomGenerator = QRandomGenerator::global();
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        float x = static_cast<float>(randomGenerator->bounded(RANDOM_BOUND));
        float y = static_cast<float>(randomGenerator->bounded(RANDOM_BOUND));
        float z = static_cast<float>(randomGenerator->bounded(RANDOM_BOUND));
        sensor1.newData(x);
        sensor2.newData(y);
        sensor3.newData(z);
    }

    return a.exec();
}
