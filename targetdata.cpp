#include "stdafx.h"
#include "targetdata.h"
#include "math.h"

#ifdef _DEBUG      
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW     
#endif  
////��̬������ʼ��
double TargetData::ya1[5] = { 0, 0, 0, 0, 0 };
double TargetData::ya2[5] = { 0, 0, 0, 0, 0 };
double TargetData::ye2[5] = { 0, 0, 0, 0, 0 };
double TargetData::pua[5] = { 0, 0, 0, 0, 0 };
double TargetData::ua2[5] = { 0, 0, 0, 0, 0 };
double TargetData::ue[5] = { 0, 0, 0, 0, 0 };
double TargetData::ye1[5] = { 0, 0, 0, 0, 0 };
double TargetData::pue[5] = { 0, 0, 0, 0, 0 };

double TargetData::Ec = 0;
extern bool inf_mark;

double **global_ami;
double **global_ele;
double **global_dis;
int global_num;
extern float H;   //������1/100��
extern float Dj;  //���Ծ������1Kmʱ(D1 = 10)190pixel��17*11
extern float L;  //���
extern float Vt;

TargetData::TargetData()
{
	srand((unsigned)time(NULL));//�������Ϊ��ǰʱ��ֵ����λΪ��
	fire_tnum = 0;
	t = 0.02;                        //20ms
	xx0 = yy0 = 0.0000;          //���Ӹ���ϵͳ��ȡ��ֵ�������ߺ��״���Ŀ��Ƕ�֮���λ������ ,200 mil= 12 ��
	ndea[0] = 97.0;              //97 mil=5.82��    
	ndea[1] = ndea[2] = ndea[3] = 0.0; //ndea[1]-d[0]���������ֵ,ndea[2],ndea[3]-�ֱ��Ǹ���ģ������ߵͽǺͷ�λ��
	nfj = 0;                   //������ʶ�� 
	yr3 = 0;                    //�ز���ʶ��
	yr1 = 0;
	nd = 97;                 //������ʶ��
	nd1 = 97;                //nd->fircont nd1->laser
	int k, tra = 0;
	ninit = nagc = k = ndn = 0;    //������ʶ��
	a = e = m_TF = 0.0;
	ATV = ETV = 0.0000;
	DD_out = 0;
	nd2 = 3;
	nd3 = 0;
	AT = 0, ET = 0, DD = 0;
	at = 0, et = 0, i = 0;
	fc1 = 0, fd1 = 999999;//��ԭ��
	g0 = 0;
	indexg0 = 0;
}

TargetData::~TargetData()
{
}


SendParam* TargetData::MainWin(double **ami, double **ele, double **dis, int t_num, int MainWin_i)
{
	double MainWin_ami = ami[t_num - 1][MainWin_i];
	double MainWin_ele = ele[t_num - 1][MainWin_i];
	double MainWin_dis = dis[t_num - 1][MainWin_i];

	global_ami = ami;
	global_ele = ele;
	global_dis = dis;
	global_num = t_num;

	if (fire_tnum != t_num)
	{
		fire_tnum = t_num;
		t = 0.02;                        //20ms
		xx0 = yy0 = 0.0000;          //���Ӹ���ϵͳ��ȡ��ֵ�������ߺ��״���Ŀ��Ƕ�֮���λ������ ,200 mil= 12 ��
		ndea[0] = 97.0;              //97 mil=5.82��    
		ndea[1] = ndea[2] = ndea[3] = 0.0; //ndea[1]-d[0]���������ֵ,ndea[2],ndea[3]-�ֱ��Ǹ���ģ������ߵͽǺͷ�λ��
		nfj = 0;                   //������ʶ�� 
		yr3 = 0;                    //�ز���ʶ��
		yr1 = 0;
		agc = 0; egc = 0;
		agc1 = 0, agc2 = 0, agc3 = 0, egc1 = 0, egc2 = 0, egc3 = 0;//fircont1
		a_gc = 0;            //����δ����ʱ�õ��ı���
		nd = 97;                 //������ʶ��
		nd1 = 97;                //nd->fircont nd1->laser
		int k, tra = 0;
		ninit = nagc = k = ndn = 0;    //������ʶ��
		a = e = m_TF = 0.0;
		ATV = ETV = 0.0000;

		DD_out = 0;
		nd2 = 3;
		nd3 = 0;
		a_gc1 = 0;
		e_gc1 = 0;
		rx = 0, ry = 0, rz = 0, ATR = 0, ETR = 0, DTR = 0;

		AT = 0, ET = 0, DD = 0;
		at = 0, et = 0, i = 0;
	}

	SendParam *pSend = new SendParam;
	memset(pSend, 0, sizeof(SendParam));

	// nfj1=3;		//�趨nfj

	ind = MainWin_i;

	AT = MainWin_ami;
	if (AT>6.28)
	{
		AT = 6.28;    //2��
	}
	ET = MainWin_ele;
	DD = MainWin_dis;
	xx0 = AT - a; 	yy0 = ET - e;     //���Ӹ���ϵͳ��ȡ��ֵ�������ߺ��״���Ŀ��Ƕ�֮��a=e=0.0 a,e����׼�ߵĽǶȣ�AT,ET-Ŀ��Ƕ�
	if (xx0 < -PI)
	{
		xx0 = xx0 + 2 * PI;
	}
	else if (xx0 > PI)
	{
		xx0 = 2 * PI - xx0;
	}

	TV(DD, xx0, yy0, ATV, ETV);     //2���Ӹ���ϵͳ���������ATV��ETV

	rx = DD*cos(ET)*sin(AT);
	ry = DD*cos(ET)*cos(AT);
	rz = DD*sin(ET);
	nd3++;

	if (DD>4000)
	{
		at = ATR;
		et = ETR;
	}
	else
	{
		i++;
		if (i<2)
		{
			ATV = ATR;
			ETV = ETR;
		}
		at = ATV;
		et = ETV;
	}

	if (nfj == nfj1)
	{
		echo(a, e, DD, xx0, yy0, yr3);//3Ŀ��ز����� DD=sqrt(1250000+b *b )  a,e����׼�ߵĽǶ�

		nfj = 0;

		if (yr3 == 1)//yr3=1 or yr3=0		 
		{
			DD = sqrt((L - Vt * t)*(L - Vt * t) + H*H + Dj*Dj);
			nd1++; ninit++;
			laser(DD, DD_out);//4�����������ģ��

		}
		else
		{
			nd1 = 97;
		}
	}
	nfj++;//nfj 3->0->1
	track(at, et, ya1[0], a, e);           //8���ߵ�/��λ�������ŷ�ϵͳ  
	pSend->agc = MainWin_dis;
	pSend->agc1 = gunTargetStatus;
	pSend->egc = DD_out;//bullet;
	pSend->egc1 = misTargetStatus;
	pSend->azimuth_drawTran = ya1[0];
	pSend->ES = nfj1;
	return pSend;
}
//***************************���ߵ�/��λ�������ŷ�ϵͳ*********************************//
void TargetData::track(double track_ATV, double track_ETV, double track_ya1, double & track_a, double & track_e)
{
	zc[0] = 0;               zc[1] = 1.8417;         zc[2] = -1.2292;       zc[3] = 0.3867;       zc[4] = 0;        //�����ŷ�����
	zd[0] = 0;               zd[1] = 0.8545;         zd[2] = -0.8652;       zd[3] = -0.2865;      zd[4] = 0.298;    //�����ŷ�����

	for (int m = 4; m>0; m--)
	{
		ya2[m] = ya2[m - 1];	   ua2[m] = ua2[m - 1];
		ue[m] = ue[m - 1];	       ye2[m] = ye2[m - 1];
	}
	pue[0] = ue[0] = track_ETV;	            // ���ߵ͸����ŷ�ϵͳ��ֵ
	ua2[0] = track_ATV - track_ya1;  //???

	if (ua2[0] > PI)
	{
		ua2[0] = ua2[0] - 2 * PI;
	}
	else if (ua2[0] < -PI)
	{
		ua2[0] = ua2[0] + 2 * PI;
	}

	ya2[0] = ye2[0] = 0;                         // ya2[0], ye2[0]-ϵͳ���ֵ��������ָ���Ŀ��δ��������ڵ�Ĳ�ֵ

	for (int n = 0; n <= 4; n++)
	{
		ya2[0] = ya2[0] + ya2[n] * zc[n] + ua2[n] * zd[n];        //zc[m] ��zd[m]�����ŷ�����
		ye2[0] = ye2[0] + ye2[n] * zc[n] + ue[n] * zd[n];
	}
	//***************************�� �� �� ׼ ��*********************************//
	track_a = track_ya1 + ya2[0];//???
	if (track_a < 0)
	{
		track_a = track_a + 2 * PI;
	}
	else if (track_a > 2 * PI)
	{
		track_a = track_a - 2 * PI;
	}

	track_e = ye2[0];
}

//***************************���Ӹ���ģ��TV*********************************//
//TV_xx0 �� TV_yy0---������ xx0 yy0 ��        TV_AT ,TV_ET---AT,ET����ֵ;              ATV_out, ETV_out  ���������
void TargetData::TV(double TV_DD, double TV_xx0, double TV_yy0, double &ATV_out, double &ETV_out)
{
	static double yh1[3] = { 0, 0, 0 }, uh1[3] = { 0, 0, 0 }, yw1[2] = { 0, 0 }, uw1[2] = { 0, 0 },
		yh2[3] = { 0, 0, 0 }, uh2[3] = { 0, 0, 0 }, yw2[2] = { 0, 0 }, uw2[2] = { 0, 0 },
		us1[2] = { 0, 0 }, ys1[2] = { 0, 0 }, us2[2] = { 0, 0 }, ys2[2] = { 0, 0 };

	double hc[3] = { 0, -0.935, 0.035 }, hd[3] = { 0, 1.935, -1.035 },
		wc[2] = { 0, 0.99005 }, wd[2] = { 9.204, -8.21 };

	register int m;

	ys1[0] = ATV_out;
	ys2[0] = ETV_out;

	/////////////////// ���������ٶ�wa,we ///////////////////    wrong ???
	double wa, we;    	wa = 0;    we = 0;

	wa = (ATV_out - pre_AT) * 50;    we = (ETV_out - pre_ET) * 50;
	wa = (0.00025*(8000 - TV_DD))*wa;
	we = (0.00025*(8000 - TV_DD))*we;

	/////////////////////////////////////////////////////////////////////////////////////////////	
	for (m = 2; m>0; m--)
	{
		yh1[m] = yh1[m - 1];    uh1[m] = uh1[m - 1];    yh2[m] = yh2[m - 1];    uh2[m] = uh2[m - 1];
		if (m>1) continue; //��������ѭ����������һ��ѭ���������˳�����ѭ��
		yw1[m] = yw1[m - 1];    uw1[m] = uw1[m - 1];    yw2[m] = yw2[m - 1];    uw2[m] = uw2[m - 1];
		ys1[m] = ys1[m - 1];      us1[m] = us1[m - 1];      ys2[m] = ys2[m - 1];       us2[m] = us2[m - 1];
	}
	/////////////  У  ��  ��  ��////////////
	///////////  ������-�������uw1[0]=xx0�������-���ٶ�yw1[0]	/////////////
	/*  uh1[0]=TV_xx0;  uh2[0]=TV_yy0;
	yh1[0]=yh2[0]=0;
	for (m=0;m<3;m++)
	{
	yh1[0]=yh1[0]+hc[m]*yh1[m]+hd[m]*uh1[m];
	yh2[0]=yh2[0]+hc[m]*yh2[m]+hd[m]*uh2[m];
	}
	uw1[0]=yh1[0];  uw2[0]=yh2[0];   yw1[0]=yw2[0]=0;*/
	uw1[0] = TV_xx0;     uw2[0] = TV_yy0;  //xx0=AT-a; yy0=ET-e;  a,e����׼�ߵĽǶȣ�AT,ET-Ŀ��Ƕ�

	yw1[0] = yw2[0] = 0.0;

	for (m = 0; m<2; m++)
	{
		yw1[0] = yw1[0] + wc[m] * yw1[m] + wd[m] * uw1[m];
		yw2[0] = yw2[0] + wc[m] * yw2[m] + wd[m] * uw2[m];
	}

	////////////  ��  ��  ��  ��  /////////////
	////  ������-���ٶ�,us1[0]=yw1[0]�������-���ٷ�λ�͸ߵͽ�ATV,ETV /////

	us1[0] = yw1[0];  us2[0] = yw2[0];

	ys1[0] = ys2[0] = 0.0;

	ATV_out = ys1[0] = ys1[1] + 0.5*0.02*(us1[1] + us1[0]);
	/*
	if(ATV_out >= 2*PI)
	{
	ATV_out = ATV_out - 2*PI;
	}
	*/
	ETV_out = ys2[0] = ys2[1] + 0.5*0.02*(us2[1] + us2[0]);
}

//******************Ŀ��ز�����********************//
void TargetData::echo(double echo_a, double echo_e, double echo_DD, double echo_xx0, double echo_yy0, int  & echo_yr3)
{
	double st, rt, a_t, a_l, er, as, a_g, r1, r_1, r2, r_2, ndea1;
	ndea1 = echo_DD*echo_DD;
	//	st=43.2*fabs(sin(ndea[2]))+18.5*fabs(cos(ndea[2])*cos(ndea[3]))+2.0*fabs(cos(ndea[2])*sin(ndea[3]));
	st = 43.2*fabs(sin(echo_e)) + 18.5*fabs(cos(echo_e)*cos(echo_a)) + 2.0*fabs(cos(echo_e)*sin(echo_a));//����Ŀ���Ч���
	rt = sqrt(st / 3.1415926);   //����Ŀ���Ч����İ뾶

	//��������ڿռ��ϵ�ʸ������
	a_t = sqrt(echo_yy0*echo_yy0 + echo_xx0*echo_xx0*cos(echo_e)*cos(echo_e));    //MILRAD ���ƽǻ���ת��
	a_l = rt / echo_DD;		//Ŀ��뾶��Ӧ�Ľǻ���
	if (a_t >= a_l + 0.002)  { er = 0.; yr = 0; yr1 = 0; return; }
	else
	{
		if (a_t <= fabs(a_l - 0.002))
		{
			if (a_l >= 0.002)  { as = 3.1415926*(ndea1*(4.e-6)); a_g = 0; }
			else { as = st; a_g = a_t; }
		}
		else
		{
			r1 = (a_l*a_l + a_t*a_t - (4.e-6)) / (2.0*a_l*a_t);
			r_1 = acos(r1);
			r2 = (4.e-6 + a_t*a_t - a_l*a_l) / (0.004*a_t);
			r_2 = acos(r2);
			as = r_1*rt*rt*(1.0 - r1) + r_2*ndea1*(4.e-6)*(1.0 - r2);
			a_g = 0.002*r2;
		}
	}
	er = exp(-5.e5*a_g*a_g);
	er = 1.4e7 / (ndea1*ndea1)*as*er;

	if (er >= 2.0e-8) {
		yr = 1;
		yr1 = yr1 + 1;
		if (yr){
			inf_mark = true;
		}
		else{
			inf_mark = false;
		}
	}
	else { yr = 0; yr1 = 0; }
	if (yr1 >= 3 || echo_yr3 == 1)  { echo_yr3 = 1; }//��
	else { echo_yr3 = 0; }
	return;
}
//************************ �����������ģ�� ******************************/  
void TargetData::laser(double DD_in, double & DD_out)
{
	static double d1, d2, d3, td2, td3, td_0, d_1, d, p1, p2, z, px;

	px = DD_in;       // px--б��·�ݾ�

	switch (nd1)
	{
	case 98: d1 = d1 = DD_in;
		DD_out = DD_in;
		return;
	case 99: d2 = d1 = DD_in;
		DD_out = DD_in;
		return;
	case 100: d3 = d1 = DD_in;
		td2 = d2 - d1; td3 = d3 - d2;
		td_0 = (td2 + td3)*0.5;
		d = (d3 + d2 + td_0)*0.5;
		d_1 = d + td_0;
		DD_out = DD_in;
		return;
	}
	if ((nd1>100) && (nd1 <= 110))  //2��֮ǰ�Ĳ�ദ��ģ��  
	{
		p1 = 0.66 + 132. / (d + 1.0);
		p2 = 0.1;

		d1 = DD_in;
		z = d1 - d_1;

		if (fabs(z)>10.) { p1 = 0.8; p2 = 0.2; }
		if ((fabs(z) >= 5) || (fabs(z) <= 10)) { z = z*0.5; }
		d = d_1 + p1*z; td_0 = td_0 + p2*z; d_1 = d + td_0;
		DD_out = d;
		return;
	}
	p1 = 0.71 + px / (d + 1.0)*0.236666667;  //2��֮��Ĳ�ദ��ģ��
	p2 = (1.0 + px / (d + 1.0))*0.1;

	d1 = DD_in;
	z = d1 - d_1;
	if (fabs(z)>10) { p1 = 0.8; p2 = 0.2; }
	if (fabs(z)>5 || fabs(z) <= 10) { p1 = p1*0.5; p2 = p2*0.5; }

	if (yr == 0) z = 0.0;   //���޻ز�ʱȡz��0;
	d = p1*d1 + (1.0 - p1)*d_1;   td_0 = td_0 + p2*z;   d_1 = d + td_0;

	DD_out = d;
	return;
}