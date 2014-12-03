#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTableView>
#include<QTreeView>
#include<QBoxLayout>
#include<QLabel>

#include<QStandardItemModel>
#include<QSplitter>
#include"data.h"
#include"tablemodel.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget()
    {
        delete data;
        delete model;
        delete model_L;
        delete model_M;
        delete m_ocxTableView_M;
        delete m_ocxTableView_L;
        delete splitter_2;
        delete m_ocxTreeView;
        delete splitter_1;
        delete gdlayout;
    }

    void setTreeModel(Data&);
    void setTableModel(Data&,int idx=0,int jdx=-1);

    void Update();
private slots:
    void UpdateAllModel();
    void on_treeView_clicked(const QModelIndex &index);

private:
    //界面控件
    QTableView *m_ocxTableView_M;
    QTableView *m_ocxTableView_L;
    QTreeView *m_ocxTreeView;
    QGridLayout *gdlayout;
    QSplitter *splitter_1;
    QSplitter *splitter_2;

    //数据
    Data *data;
    QModelIndex index;
    TableModel *model_L;
    TableModel *model_M;
    QStandardItemModel* model;


};

#endif // WIDGET_H
