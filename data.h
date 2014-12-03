#ifndef DATA_H
#define DATA_H
#include<QString>
#include<QStringList>
#include<QList>
#include<QVariant>
typedef QList<double> Record;
typedef QList<Record> IJRecord;//二维表
typedef struct N7DAtA{
    QString I_ij;
    double N5_ij;
    IJRecord L_Rcd;
}N7Data,*PN7Data;


typedef QList<PN7Data> DataN7;
typedef QList<Record> DataN6;

typedef struct DAtAT{
    QString I_idi;
    double N2;
    double N3;
    double N4;
    double N5;
    DataN6 N6_I;
    DataN7 N7_Iij;
}DataT,*PDataT;
typedef QList<PDataT> DataAll;

class Data
{

//private:
public:
    Data(){
        ReadData ();
        Update();
    }
    //static  Data *dt_global;

public:
    ~Data(){
        foreach (PDataT v, m_dt) {
            delete v;
        }
    }
//    static  Data* GetDataObject()
//    {
//        if(dt_global==NULL)
//        {
//            dt_global=new Data();
//        }
//        return dt_global;
//    }

    void ReadData();
    void SetRecord(const double data, int nparent, int row, int col, bool n6=true, int n7id=0);
    QStringList Get_N_Head();
    QStringList Get_M_Head();
    QStringList Get_L_Head();

    DataAll *Get_Data();

    void Update();
private:
    DataAll m_dt;//所有数据

};

#endif // DATA_H
