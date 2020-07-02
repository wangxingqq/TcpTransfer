// TargetData.h: interface for the TargetData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_)
#define AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once   
#endif // _MSC_VER > 1000  

#include "RadarStruct.h"


//弧度 radian ；         度 degree ；           米位  mil
#define DEGRAD 3.1415926/180.0 //度数弧度转换
#define MILDEG 180.0/3000.0    //米位度数转换
#define RADMIL 3000.0/3.1415926//弧度米位转换
#define MILRAD 3.1415926/3000.0//米位弧度转换
#define RADDEG 180.0/3.1415926//弧度度数转换
#define DEGMIL 3000.0/180.0   //度数米位转换

struct  DATA   //结构体声明
{
	long double A[2000];
	long double E[2000];
};

class TargetData
{

public:
	static double Ac, Ec;
	//static double pua_agc, pua_agc0;//定义 
	static double ya1[5], ya2[5], ye1[5], ye2[5], ua2[5], ue[5], pue[5], pua[5];
	//由全局变量移入目标类2010
	TargetData();
	virtual ~TargetData();
	SendParam* MainWin(double**, double**, double**, int, int);//MainWin()的返回值类型为结构体SendParam

	void TV(double, double, double, double&, double&);

	void track(double, double, double, double&, double&);


	void echo(double, double, double, double, double, int&);

	void laser(double, double&);

public:

	double fir_a_gc, fir_e_gc, fir_agc1, fir_egc1;   //MC

	int fire_tnum;
	double AT, ET, DD;  //搜索雷达测的目标角度，接收数据；
	int k, ndn, ninit, nfj, nagc, nflag, nflag0, flagTV; //计数标识量
	int yr, yr1, yr3;              //回波标识量
	double ATV, ETV, a, e, ua, m_D;
	double t;   //？？？
	double xx0, yy0;        //电视跟踪系统的取差值，跟踪线和雷达测的目标角度之差，单位是mil 
	double ndea[4];        //ndea[1]-d[0],ndea[2],ndea[3]-elevation,azimuth after integrater积分后的高低角 方位角
	double agc, egc, agc1, egc1, dq1, a_gc, e_gc, dq2, zq; //解算未来点时用到的变量
	double a_gc1, e_gc1;//fircont!!!
	double m_TF;
	double xc[5], xd[5], zc[5], zd[5];    // 高炮伺服参数  
	double agc2, agc3, egc2, egc3;//fircont1
	int nfj1;//修改nfj用
	double DD_out;
	int nd, nd1, nd2, nd3;//计数标示量
	double rx, ry, rz, ATR, ETR, DTR;//radar
	//	double xq, yq, zq1;//pinghua输出
	double at, et, i;
	//double rc, rd, rj1, rj2;//跟踪雷达
	//double fc, fd, fj1, fj2;//火控
	//int zt;//车体姿态模块计数标识量
	//double fhy, fzy;
	//double se_hp, se_dd;//火炮、导弹选择标识
	//double sc, sd, sj1, sj2;//武器选择模块
	//double tc, td, tj1, tj2;//脱靶量模块过零点
	//double t1, t2, t3, t4, t5, t6, t7;//脱靶量模块测试
	double dd1;//fircont未来点距离
	int ind;
	//int tbljz, tbljh;
	//int jz;			//命中次数
	//int	jh;			//是否击毁标志
	//int bullet, missile, i_m;
	//int pd;//判定火控中过零点模式

	////用于控制过零点条件
	//int index;
	//int index1;

	////rand
	double rand_num0, rand_num1, rand_num2;

	//int GZ_mode;
	//int pre_GZ_mode;   // 之前的跟踪模式 

	double pre_AT, pre_ET;//上一时刻的AT、ET 

	//过原点
	double fc1, fd1;
	int g0;
	int indexg0;
};

#endif // !defined(AFX_TARGETDATA_H__F9260A92_9B72_4A84_8704_DB8B81FBD1A4__INCLUDED_)



