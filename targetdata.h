// TargetData.h: interface for the TargetData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_)
#define AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once   
#endif // _MSC_VER > 1000  

#include "RadarStruct.h"


//���� radian ��         �� degree ��           ��λ  mil
#define DEGRAD 3.1415926/180.0 //��������ת��
#define MILDEG 180.0/3000.0    //��λ����ת��
#define RADMIL 3000.0/3.1415926//������λת��
#define MILRAD 3.1415926/3000.0//��λ����ת��
#define RADDEG 180.0/3.1415926//���ȶ���ת��
#define DEGMIL 3000.0/180.0   //������λת��

struct  DATA   //�ṹ������
{
	long double A[2000];
	long double E[2000];
};

class TargetData
{

public:
	static double Ac, Ec;
	//static double pua_agc, pua_agc0;//���� 
	static double ya1[5], ya2[5], ye1[5], ye2[5], ua2[5], ue[5], pue[5], pua[5];
	//��ȫ�ֱ�������Ŀ����2010
	TargetData();
	virtual ~TargetData();
	SendParam* MainWin(double**, double**, double**, int, int);//MainWin()�ķ���ֵ����Ϊ�ṹ��SendParam

	void TV(double, double, double, double&, double&);

	void track(double, double, double, double&, double&);


	void echo(double, double, double, double, double, int&);

	void laser(double, double&);

public:

	double fir_a_gc, fir_e_gc, fir_agc1, fir_egc1;   //MC

	int fire_tnum;
	double AT, ET, DD;  //�����״���Ŀ��Ƕȣ��������ݣ�
	int k, ndn, ninit, nfj, nagc, nflag, nflag0, flagTV; //������ʶ��
	int yr, yr1, yr3;              //�ز���ʶ��
	double ATV, ETV, a, e, ua, m_D;
	double t;   //������
	double xx0, yy0;        //���Ӹ���ϵͳ��ȡ��ֵ�������ߺ��״���Ŀ��Ƕ�֮���λ��mil 
	double ndea[4];        //ndea[1]-d[0],ndea[2],ndea[3]-elevation,azimuth after integrater���ֺ�ĸߵͽ� ��λ��
	double agc, egc, agc1, egc1, dq1, a_gc, e_gc, dq2, zq; //����δ����ʱ�õ��ı���
	double a_gc1, e_gc1;//fircont!!!
	double m_TF;
	double xc[5], xd[5], zc[5], zd[5];    // �����ŷ�����  
	double agc2, agc3, egc2, egc3;//fircont1
	int nfj1;//�޸�nfj��
	double DD_out;
	int nd, nd1, nd2, nd3;//������ʾ��
	double rx, ry, rz, ATR, ETR, DTR;//radar
	//	double xq, yq, zq1;//pinghua���
	double at, et, i;
	//double rc, rd, rj1, rj2;//�����״�
	//double fc, fd, fj1, fj2;//���
	//int zt;//������̬ģ�������ʶ��
	//double fhy, fzy;
	//double se_hp, se_dd;//���ڡ�����ѡ���ʶ
	//double sc, sd, sj1, sj2;//����ѡ��ģ��
	//double tc, td, tj1, tj2;//�Ѱ���ģ������
	//double t1, t2, t3, t4, t5, t6, t7;//�Ѱ���ģ�����
	double dd1;//fircontδ�������
	int ind;
	//int tbljz, tbljh;
	//int jz;			//���д���
	//int	jh;			//�Ƿ���ٱ�־
	//int bullet, missile, i_m;
	//int pd;//�ж�����й����ģʽ

	////���ڿ��ƹ��������
	//int index;
	//int index1;

	////rand
	double rand_num0, rand_num1, rand_num2;

	//int GZ_mode;
	//int pre_GZ_mode;   // ֮ǰ�ĸ���ģʽ 

	double pre_AT, pre_ET;//��һʱ�̵�AT��ET 

	//��ԭ��
	double fc1, fd1;
	int g0;
	int indexg0;
};

#endif // !defined(AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_)



