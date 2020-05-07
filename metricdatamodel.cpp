#include "metricdatamodel.h"
#include <QString>

MetricDataModel::MetricDataModel(QObject *parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this,&MetricDataModel::updateSMCData);

}

void MetricDataModel::startDataFetch()
{
    this->addMetric(new Metric(QString("CPU Temperature"), QString("CPU Temperature"), QString("-")));
    int fanCount = m_smcProxy.readFanCount();
    for(int i=0;i<fanCount;i++){
        this->addMetric(new Metric(QString("Fan-"+QString::number(i)+" Speed"),
                                   QString("Fan-"+QString::number(i)+" Speed"), QString("-")));
    }

    this->addMetric(new Metric(QString("Battery Level"), QString("Battery Level"), QString("-")));
    this->addMetric(new Metric(QString("Battery Health"), QString("Battery Health"), QString("-")));
    this->addMetric(new Metric(QString("Cycle Count / Max Cycles"), QString("Cycle Count / Max Cycles"), QString("-")));
    this->addMetric(new Metric(QString("Current Charge / Max Charge"), QString("Current Charge / Max Charge"), QString("-")));

    m_timer->start(500);
}

void MetricDataModel::addMetric(Metric *metric)
{
    m_data.append(metric);
}

int MetricDataModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant MetricDataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
            return QVariant();

        const Metric *metric = m_data[index.row()];
        if (role == NameRole)
            return metric->name();
        else if (role == DisplayNameRole)
            return metric->displayName();
        else if (role == ValueRole)
            return metric->value();
        return QVariant();
}

void MetricDataModel::updateSMCData()
{
    int index = 0;
    double temperature = m_smcProxy.readCPUTemperature();
    this->m_data[index++]->setValue(QString::number(temperature)+QString("°C"));

    QVector<int> fanSpeeds = m_smcProxy.readFanSpeeds();
    for(int i=0;i<fanSpeeds.size();i++){
        this->m_data[index++]->setValue(QString::number(fanSpeeds.at(i))+QString(" RPM"));
    }

    int batteryChargeLevel = m_smcProxy.readBatteryChargeLevel();
    this->m_data[index++]->setValue(QString::number(batteryChargeLevel)+QString("%"));
    QString batteryHealth = m_smcProxy.readBatteryHealth();
    this->m_data[index++]->setValue(batteryHealth);
    QVector<int> cycleCountData = m_smcProxy.readBatteryCycleCountInfo();
    this->m_data[index++]->setValue(QString::number(cycleCountData.at(0))+"/"+QString::number(cycleCountData.at(1)));
    QVector<int> chargeLevels = m_smcProxy.readBatteryChargeLevels();
    this->m_data[index++]->setValue(QString::number(chargeLevels.at(0))+"/"+QString::number(chargeLevels.at(1)));


    emit dataChanged(this->index(0),this->index(m_data.size()-1));
}

QHash<int, QByteArray> MetricDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[DisplayNameRole] = "displayName";
        roles[ValueRole] = "value";
        return roles;
}


