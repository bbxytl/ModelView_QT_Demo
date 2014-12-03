#include "tablemodel.h"


TableModel::TableModel(Data &pd, int idx, int jdx, QObject *parent)
{
    pdata=&(pd);
    this->idx=idx;
    this->jdx=jdx;
    if(jdx==-1){
        prd=(&(pdata->Get_Data ()->at (idx)->N6_I));
    }else{
        prd=(&(pdata->Get_Data ()->at (idx)->N7_Iij.at (jdx)->L_Rcd));//const_cast<QList<Record>* >
    }

}

int TableModel::rowCount(const QModelIndex &parent) const
{
   return prd->size ();//返回行数
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if(prd->size ()>0)
        return prd->at (0).size();
    else return 0;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

        if (index.row() >= prd->size())
            return QVariant();

        if (role == Qt::DisplayRole)
            return prd->at(index.row ()).at(index.column ());
        else
            return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

    if(jdx==-1){
        if (orientation == Qt::Horizontal)
            return pdata->Get_M_Head ().at (section);
        else
            return pdata->Get_Data ()->at (idx)->I_idi;
    }else{
        if (orientation == Qt::Horizontal)
            return pdata->Get_L_Head ().at (section);
        else
            return pdata->Get_Data ()->at (idx)->N7_Iij.at (jdx)->I_ij;
    }

}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
            return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
//        *(static_cast<double* >(index.internalPointer()))=value.toDouble ();
        //这里调取时出现问题，上下两种方法都是有问题
//        prd->at(index.row()).at(index.column ());.replace(index.column(),value.toDouble ());
        if(jdx!=-1)
            pdata->SetRecord (value.toDouble (),idx,index.row (),index.column (),false,jdx);
        else
            pdata->SetRecord (value.toDouble (),idx,index.row (),index.column (),true,jdx);

        pdata->Update();
        emit dataChanged(index, index);
            return true;
        }
    return false;
}
