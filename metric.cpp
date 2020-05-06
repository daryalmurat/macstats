#include "metric.h"

Metric::Metric(QObject *parent) : QObject(parent)
{

}

Metric::Metric(const QString &name, const QString& displayName,
               const QString& value,QObject *parent)
: QObject(parent), m_name(name), m_displayName(displayName), m_value(value)
{

}

QString Metric::name() const
{
    return m_name;
}

void Metric::setName(const QString &name)
{
    m_name = name;
}

QString Metric::displayName() const
{
    return m_displayName;
}

void Metric::setDisplayName(const QString &displayName)
{
    m_displayName = displayName;
}

QString Metric::value() const
{
    return m_value;
}

void Metric::setValue(const QString &value)
{
    m_value = value;
    emit valueChanged(m_value);
}
