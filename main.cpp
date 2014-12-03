#include "widget.h"
#include <QApplication>

#include<QStringList>
#include<QString>
#include<QVariant>

#include"data.h"
//#include"mtreemodel.h"
#include<iostream>
using namespace std;

//typedef QList<double> Record;
typedef QList<QVariant> RecordR;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
//    w.hide ();
//while(i--)
//{
//    RecordR r;
//    r<<"wang"<<3<<5<<9;

//    int i=0;
//    foreach (QVariant d, r) {
//        if(i++==0)cout<<d.toString ().toStdString ();
//        else cout<<d.toDouble ()<<endl;
//    }
//    cout<<endl;
////    cout<<r.count ()<<endl<<
////          r.size ()<<endl<<
////          r[2]<<endl;
//}
    return a.exec();
//    Data *dt=Data::GetDataObject ();
//    cout<<"dt"<<endl;
//    QStringList st(dt->Get_M_Head ());
//    for(int i=0;i<st.count ();i++)
//        cout<<st[i].toStdString ()<<endl;
//    MTreeModel *tm=new MTreeModel(dt->Get_Data ());
//    delete tm;
}
