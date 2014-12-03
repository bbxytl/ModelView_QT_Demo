#include "widget.h"
#include <QIODevice>
#include <QFile>
#include<QMessageBox>
#include<QHeaderView>
Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    gdlayout =new QGridLayout(this);
    splitter_1 =new QSplitter(Qt::Horizontal);
    m_ocxTreeView = new QTreeView(splitter_1);
    splitter_2 =new QSplitter(Qt::Vertical);
    m_ocxTableView_M = new QTableView(splitter_2);
    m_ocxTableView_L = new QTableView(splitter_2);

    gdlayout->addWidget (splitter_1);
    splitter_1->addWidget (m_ocxTreeView);
    splitter_1->addWidget (splitter_2);
    splitter_2->addWidget (m_ocxTableView_M);
    splitter_2->addWidget (m_ocxTableView_L);

    data=new Data();
    setTreeModel (*data);
    setTableModel(*data,0);
    setTableModel(*data,0,0);
    connect (m_ocxTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_treeView_clicked (QModelIndex)));
    (m_ocxTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(on_treeView_clicked (QModelIndex)));
    m_ocxTreeView->expandAll ();

    connect (model_L,SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,SLOT(UpdateAllModel()));
    connect (model_M,SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,SLOT(UpdateAllModel()));
}

void Widget::setTreeModel(Data &data)
{
    model = new QStandardItemModel(m_ocxTreeView);
    model->setHorizontalHeaderLabels(data.Get_N_Head ());
    DataAll *dt=data.Get_Data ();
    int count_i=dt->size();
    for(int i=0;i<count_i;i++){
        QStandardItem* item1=new QStandardItem(dt->at (i)->I_idi);
        model->appendRow(item1);
        int count_j=dt->at (i)->N7_Iij.count ();
        for(int j=0;j<count_j;j++)
        {
            QStandardItem* item2=new QStandardItem(dt->at (i)->N7_Iij.at(j)->I_ij);
            item1->appendRow(item2);
            item1->setChild (item2->index().row(),4,new QStandardItem(QString::number (dt->at (i)->N7_Iij.at(j)->N5_ij)));
        }
        //设置其他一级列
        model->setItem (model->indexFromItem (item1).row (),1,new QStandardItem(QString::number (dt->at (i)->N2)));
        model->setItem (model->indexFromItem (item1).row (),2,new QStandardItem(QString::number (dt->at (i)->N3)));
        model->setItem (model->indexFromItem (item1).row (),3,new QStandardItem(QString::number (dt->at (i)->N4)));
        model->setItem (model->indexFromItem (item1).row (),4,new QStandardItem(QString::number (dt->at (i)->N5)));
    }
    m_ocxTreeView->setModel (model);

}

void Widget::setTableModel(Data &data,int idx,int jdx)
{
    if(jdx==-1){
        model_M=new TableModel(data,idx,jdx);
        m_ocxTableView_M->setModel (model_M);
        m_ocxTableView_M->horizontalHeader()->setStretchLastSection(true);
    }else{
        model_L=new TableModel(data,idx,jdx);
        m_ocxTableView_L->setModel (model_L);
        m_ocxTableView_L->horizontalHeader()->setStretchLastSection(true);
    }
}

QModelIndex getTopParent(QModelIndex itemIndex)
{
    QModelIndex secondItem = itemIndex;
    while(itemIndex.parent().isValid())
    {
        secondItem = itemIndex.parent();
        itemIndex = secondItem;
    }
//    if(secondItem.column() != 0)
//    {
//         secondItem = secondItem.sibling(secondItem.row(),0);
//    }
    return secondItem;
}

void Widget::Update()
{
    int idx=0,jdx=0;
    QModelIndex mdx=getTopParent (index);
    if(index==mdx)
    {
        idx=index.row ();
        jdx=0;
    }else{
        idx=mdx.row ();
        jdx=index.row ();
    }

    setTableModel (*data,idx);//M表--I0
    setTableModel (*data,idx,jdx);//L表--I11

    connect (model_L,SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,SLOT(UpdateAllModel()));
    connect (model_M,SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,SLOT(UpdateAllModel()));
}

void Widget::UpdateAllModel()
{
    setTreeModel (*data);
    m_ocxTreeView->expandAll();
}

void Widget::on_treeView_clicked(const QModelIndex &index){
    this->index=index;
    Update();
}
