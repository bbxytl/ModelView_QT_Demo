#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "data.h"
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(Data &pd, int idx, int jdx, QObject *parent=0);
    ~TableModel(){pdata=NULL;prd=NULL;}
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                             int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                      int role = Qt::EditRole);

private:
    int idx;//区分一二级索引
    int jdx;
    IJRecord *prd; //指向二维表
    Data *pdata;

};

#endif // TABLEMODEL_H
