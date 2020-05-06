#ifndef METRIC_H
#define METRIC_H

#include <QObject>
#include <string>

class Metric : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString displayName READ displayName WRITE setDisplayName)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Metric(QObject *parent = nullptr);
    Metric(const QString &name, const QString& displayName,
                    const QString& value,QObject *parent = nullptr);
    QString name() const;
    void setName(const QString &name);
    QString displayName() const;
    void setDisplayName(const QString &displayName);
    QString value() const;
    void setValue(const QString &value);

signals:
    void nameChanged(const QString& newName);
    void displayNameChanged(const QString& newDisplayName);
    void valueChanged(const QString& newValue);
private:
    QString m_name;
    QString m_displayName;
    QString m_value;

};

#endif // METRIC_H
