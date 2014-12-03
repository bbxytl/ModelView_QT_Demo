#include "data.h"

//Data::Data()
//{
//    ReadData ();
//    Update();
//}

//Data *Data::GetDataObject()
//{
//    if(dt_global==NULL)
//    {
//        dt_global=new Data();
//    }
//    return dt_global;
//}

void Data::ReadData()
{
    int Ii_Count=4;
    int Ii_M=5;
    int Iij_i=6;
    int Iij_j=7;

    for(int k=0;k<Ii_Count;k++){
        PDataT dt=new DataT();

        dt->I_idi="I_"+QString::number(k);
        dt->N2=0;
        dt->N3=0;
        dt->N4=0;
        dt->N5=0;

        for(int i=0;i<Ii_M;i++){//I1的M行数记录
            Record n6;
            n6<<3<<5<<9;
            dt->N6_I.append (n6);
        }
        for(int i=0;i<Iij_i;i++){
            IJRecord Iij;
            PN7Data lrd=new N7Data();
            for(int j=0;j<Iij_j;j++)
            {
                Record r;
                r<<8.3<<2.3<<5<<4.5;
                Iij.append (r);
            }
            lrd->L_Rcd.append (Iij);
            lrd->I_ij="I_"+QString::number(k)+QString::number(i);
            dt->N7_Iij.append (lrd);
        }
        m_dt.append (dt);
    }
}

void Data::SetRecord(const double data,int nparent,int row, int col,bool n6,int n7id)
{
 if(n6)
 {
     m_dt[nparent]->N6_I[row].replace (col,data);
 }else{
     m_dt[nparent]->N7_Iij[n7id]->L_Rcd[row].replace(col,data);
 }
}


void Data::Update()
{
    for(int d=0;d<m_dt.count ();d++)
    {
        m_dt[d]->N2=m_dt[d]->N6_I.count ();
        double s=0;
        for(int i=0;i<m_dt[d]->N6_I.count ();i++)
        {
            s+=((m_dt[d]->N6_I[i][0]+m_dt[d]->N6_I[i][1])/2+m_dt[d]->N6_I[i][2]);
        }
        m_dt[d]->N4=s;
        s=0;
        double s5=0;
        for(int j=0;j<m_dt[d]->N7_Iij.count ();j++)
        {
            double s1=0;
            for(int r=0;r<m_dt[d]->N7_Iij[j]->L_Rcd.count ();r++)
            {
                s+=((m_dt[d]->N7_Iij[j]->L_Rcd[r][0]+m_dt[d]->N7_Iij[j]->L_Rcd[r][1])*m_dt[d]->N7_Iij[j]->L_Rcd[r][2]+m_dt[d]->N7_Iij[j]->L_Rcd[r][3])  ;
                s1+=((m_dt[d]->N7_Iij[j]->L_Rcd[r][0]+m_dt[d]->N7_Iij[j]->L_Rcd[r][1])+m_dt[d]->N7_Iij[j]->L_Rcd[r][2]+m_dt[d]->N7_Iij[j]->L_Rcd[r][3])  ;
            }
            m_dt[d]->N7_Iij[j]->N5_ij=s1;
            s5+=s1;
        }
        m_dt[d]->N3=s;
        m_dt[d]->N5=s5;
    }
}

QStringList Data::Get_N_Head()
{
    return QStringList()<<"N1"<<"N2"<<"N3"<<"N4"<<"N5";
}

QStringList Data::Get_M_Head()
{
    return QStringList()<<"M1"<<"M2"<<"M3";
}

QStringList Data::Get_L_Head()
{
    return QStringList()<<"L1"<<"L2"<<"L3"<<"L4";
}

DataAll *Data::Get_Data()
{

    return &m_dt;
}
