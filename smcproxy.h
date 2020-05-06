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
private:
    int m_fanCount;
};

#endif // SMCPROXY_H
