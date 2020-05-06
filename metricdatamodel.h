#ifndef METRICDATAMODEL_H
#define METRICDATAMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <metric.h>
#include <QTimer>
#include "smcproxy.h"

class MetricDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MetricRoles {
        NameRole = Qt::UserRole + 1,
        DisplayNameRole,
        ValueRole
    };
    MetricDataModel(QObject *parent = nullptr);
    void startDataFetch();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
public slots:
    void updateSMCData();
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    void addMetric(Metric *metric);
    QList<Metric*> m_data;
    QTimer *m_timer;
    SMCProxy m_smcProxy;
};

#endif // METRICDATAMODEL_H
