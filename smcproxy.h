#ifndef SMCPROXY_H
#define SMCPROXY_H
#include <QVector>

class SMCProxy
{
public:
    SMCProxy();
    int readCPUTemperature();
    QVector<int> readFanSpeeds();
    int readFanCount();
    int readBatteryChargeLevel();
    QString readBatteryHealth();
    QVector<int> readBatteryCycleCountInfo();
    QVector<int> readBatteryCapacityInfo();
    QVector<int> readBatteryChargeLevels();
private:
    int m_fanCount;
    int queryActualBatteryCycleCount();
    int queryCurrentBatteryChargeLevel();
    int queryMaxBatteryChargeLevel();
};

#endif // SMCPROXY_H
