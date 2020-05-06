#include "smcproxy.h"
#include "external/smc.h"

SMCProxy::SMCProxy()
{

}

int SMCProxy::readCPUTemperature()
{
    SMCOpen();
    double temperature = SMCGetTemperature(SMC_KEY_CPU_TEMP);
    SMCClose();
    return temperature;
}

QVector<int> SMCProxy::readFanSpeeds()
{
    QVector<int> res;
    for(int i=0;i<m_fanCount;i++){
        SMCOpen();
        int fanSpeed = SMCGetFanSpeed(i);
        SMCClose();
        res.append(fanSpeed);
    }

    return res;
}

int SMCProxy::readFanCount()
{
    SMCOpen();
    m_fanCount = SMCGetFanNumber(SMC_KEY_FAN_NUM);
    SMCClose();
    return m_fanCount;
}

int SMCProxy::readBatteryChargeLevel()
{
    SMCOpen();
    int batteryChargeLevel = SMCGetBatteryCharge();
    SMCClose();
    return batteryChargeLevel;
}

QString SMCProxy::readBatteryHealth()
{
    SMCOpen();
    const char* batteryHealth = SMCGetBatteryHealth();
    SMCClose();
    return QString(batteryHealth);
}

QVector<int> SMCProxy::readBatteryCycleCountInfo()
{
    SMCOpen();
    int designCycleCount = SMCGetDesignCycleCount();
    SMCClose();
    SMCOpen();
    //int cycleCount = getCycleCount();
    int cycleCount = 1;
    SMCClose();
    QVector<int> res;
    res.append(cycleCount);
    res.append(designCycleCount);

    return res;
}
