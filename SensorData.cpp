#include "SensorData.h"

SensorData::SensorData(const unsigned int max_elements, const QString& name):max_elements(max_elements),name(name){}
float SensorData::max()const{
    if(sensorData.isEmpty())return 0.0F;
    float result = sensorData.cbegin()->m_value;
    for(const auto& sm : sensorData){
        if(sm.m_value > result) result=sm.m_value;
    }

    return result;
}
void  SensorData::insert(const SensorMetric& sm){

    if(sensorData.size()>=max_elements){
        sensorData.clear();
    }
    sensorData.insert(sm.timestamp,sm);
}

void SensorData::print()const{
    QTextStream out(stdout);

    out << "SensorData {" << Qt::endl;
    out << "  Name: " << name << Qt::endl;
    out << "  Max Elements: " << max_elements << Qt::endl;
    out << "  Data: {" << Qt::endl;

    /* for (auto it = sensorData.cbegin(); it != sensorData.cend(); ++it) {
        out << "    Timestamp: " << it.key().toString()
            << ", SensorMetric: { Name: " << it.value().name
            << ", Value: " << it.value().m_value << " }" << Qt::endl;
    }*/

    out << "  }" << Qt::endl;
    out << "  Max: " << max() << Qt::endl;
    out << "  Min: " << min() << Qt::endl;
    out << "  Average: " << average() << Qt::endl;
    out << "  Median: " << median() << Qt::endl;
    out << "}" << Qt::endl;
}


float SensorData::min()const{
    if(sensorData.isEmpty())return 0.0F;
    float result = sensorData.cbegin()->m_value;
    for(const auto& sm : sensorData){
        if(sm.m_value < result) result=sm.m_value;
    }

    return result;
}

float SensorData::average()const{
    if(sensorData.isEmpty())return 0.0F;
    float sum = 0.0F;
    for(const auto& sm : sensorData){
        sum += sm.m_value;
    }
    return sum /sensorData.size();
}
float SensorData::median()const{
    if (sensorData.isEmpty())   if(sensorData.isEmpty())return 0.0F;
    QVector<int> values;
    for (const SensorMetric& metric : sensorData) {
        values.append(metric.m_value);
    }

    std::sort(values.begin(), values.end());

    int n = values.size();
    if (n % 2 == 0) {

        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    } else {
            return values[n / 2];
    }
}
