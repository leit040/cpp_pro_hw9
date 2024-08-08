#include <QCoreApplication>
#include <QRandomGenerator>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include "Analyzer.h"
#include "Logger.h"
#include "Sensor.h"

void run( QCoreApplication &app, Config &config){
    Analyzer analyzer(&app,&config);
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
    for (int i = 0; i < config.getNumIterations(); ++i) {
        float x = static_cast<float>(randomGenerator->bounded(config.getRandomBound()));
        float y = static_cast<float>(randomGenerator->bounded(config.getRandomBound()));
        float z = static_cast<float>(randomGenerator->bounded(config.getRandomBound()));
        sensor1.newData(x);
        sensor2.newData(y);
        sensor3.newData(z);
    }
}

void parseFlags(QCoreApplication& app, Config &config){
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt learning task");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption fileOption(QStringList() << "f" << "file",
                                  "Config file",
                                  "filename");
    QCommandLineOption maxElementsOption(QStringList() << "m" << "max-elements",
                                         "<Max Elements>",
                                         "maxElements");
    QCommandLineOption numIterationsOption(QStringList() << "n" << "num-iterations",
                                           "<Num Iterations>",
                                           "numIterations");
    QCommandLineOption randomBoundOption(QStringList() << "r" << "random-bound",
                                         "<Random Bound>",
                                         "randomBound");
    parser.addOption(fileOption);
    parser.addOption(maxElementsOption);
    parser.addOption(numIterationsOption);
    parser.addOption(randomBoundOption);
    parser.process(app);
    QString filename = parser.value(fileOption);
    if (filename != ""){
        config.setFilePath(filename);
        qDebug() <<"From parseFlags >> filename is :" <<filename;
    }
    int maxElements = parser.value(maxElementsOption).toInt();
    if (maxElements){
        config.setMaxElements(maxElements);
        qDebug() <<"From parseFlags >> maxElements is :" <<maxElements;
    }
    int numIterations = parser.value(numIterationsOption).toInt();
    if (numIterations){
        config.setNumIterations(numIterations);
        qDebug() <<"From parseFlags >> numIterations is :" <<numIterations;
    }
    int randomBound = parser.value(randomBoundOption).toInt();
    if (randomBound){
        config.setRandomBound(randomBound);
        qDebug() <<"From parseFlags >> randomBound is :" <<randomBound;
    }
}

void parseJson(Config &config) {
    QString configFileName;
    qDebug() <<"From parseJson >> FilePath is :" <<config.getFilePath();
    if (config.getFilePath() != ""){
        configFileName =config.getFilePath();
    } else{
        configFileName = ":resources/config.json";
    }
    QFile configFile(configFileName);
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Error: couldn't open " << configFileName;
       return;
    }
    QByteArray fileData = configFile.readAll();
    configFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qCritical() << "Error: couldn't parse json";
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    int maxElementsOption = jsonObj["maxElements"].toInt();
    if (maxElementsOption && !config.getMaxElements()){
        config.setMaxElements(maxElementsOption);
        qDebug() <<"From parseJson >> maxElements is :" <<maxElementsOption;
    }
    int numIterationsOption = jsonObj["numIterations"].toInt();
    if (numIterationsOption && !config.getNumIterations()){
        config.setNumIterations(numIterationsOption);
        qDebug() <<"From parseJson >> numIterations is :" <<numIterationsOption;
    }
   int randomBoundOption = jsonObj["randomBound"].toInt();
    if (randomBoundOption && !config.getRandomBound()){
        config.setRandomBound(randomBoundOption);
        qDebug() <<"From parseJson >> RandomBound is :" <<randomBoundOption;
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Config config;
    parseFlags(app,config);
    if (!config.getMaxElements() || !config.getNumIterations() ||!config.getRandomBound()){
        parseJson(config);
    }
    qDebug() << "From Main >> RandomBound is : " << config.getRandomBound();
    qDebug() << "From Main >> RandomBound is : " << config.getNumIterations();
    qDebug() << "From Main >> RandomBound is : " << config.getMaxElements();
    QThread::sleep(15);
    run(app,config);
    return app.exec();
}
