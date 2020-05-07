#include "smcproxy.h"
#include "external/smc.h"

#include <QProcess>

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
    int cycleCount = queryActualBatteryCycleCount();
    SMCClose();
    QVector<int> res;
    res.append(cycleCount);
    res.append(designCycleCount);

    return res;
}

QVector<int> SMCProxy::readBatteryCapacityInfo()
{
    SMCOpen();
    int currentCapacity = SMCGetBatteryCurrentChargeCapacity();
    SMCClose();
    SMCOpen();
    int maxCapacity = SMCGetBatteryMaxChargeCapacity();
    SMCClose();
    QVector<int> res;
    res.append(currentCapacity);
    res.append(maxCapacity);
    return res;
}

QVector<int> SMCProxy::readBatteryChargeLevels()
{
    int currentLevel = queryCurrentBatteryChargeLevel();
    int maxLevel = queryMaxBatteryChargeLevel();
    QVector<int> res;
    res.append(currentLevel);
    res.append(maxLevel);
    return res;
}

int SMCProxy::queryActualBatteryCycleCount()
{
    QProcess systemProfilerProcess;
    systemProfilerProcess.start("bash",QStringList() << "-c" << "system_profiler SPPowerDataType | grep \"Cycle Count\" | awk '{print $3}'");
    systemProfilerProcess.waitForFinished();
    QString output(systemProfilerProcess.readAllStandardOutput());
    return output.toInt();
}

int SMCProxy::queryCurrentBatteryChargeLevel()
{
    QProcess systemProfilerProcess;
    systemProfilerProcess.start("bash",QStringList() << "-c"
                                << "ioreg -rn AppleSmartBattery | grep \"\\\"CurrentCapacity\\\" =\" | awk '{print $3}'");
    systemProfilerProcess.waitForFinished();
    QString output(systemProfilerProcess.readAllStandardOutput());
    return output.toInt();
}

int SMCProxy::queryMaxBatteryChargeLevel()
{
    QProcess systemProfilerProcess;
    systemProfilerProcess.start("bash",QStringList() << "-c"
                                << "ioreg -rn AppleSmartBattery | grep \"\\\"MaxCapacity\\\" =\" | awk '{print $3}'");
    systemProfilerProcess.waitForFinished();
    QString output(systemProfilerProcess.readAllStandardOutput());
    return output.toInt();
}


