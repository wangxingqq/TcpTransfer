
#ifndef _RADAR_H_
#define _RADAR_H_

#include "RadarDef.h"

//����ԭʼ���ݽṹ��
typedef struct Track_Data_Orig
{
	int iTime;						//ʱ��	
	double x;						//x������
	double y;						//y������
	double z;						//z������

	char trackSource;
}trackdata;

//����������ṹ��
typedef struct Track_Data_Polar
{
	int  time;						//ʱ��
	double  azimuth;				//Ŀ�귽λ��
	double  elevation;				//Ŀ��ߵͽ�
	double  distance;				//Ŀ�����

	char trackSource;
}trackDataPolar;

//����������ֱ������ת���ṹ��
typedef struct Track_Data_Polar_Rec
{
	int  time;						//ʱ��
	double  azimuth_x;				//Ŀ�귽λ��
	double  elevation_y;			//Ŀ��ߵͽ�
	double  distance_z;				//Ŀ�����

	double speedX;
	double speedY;
	double speedZ;

	char trackSource;				//��־
}trackDataPolarRec;

//����ںϺ󺽼��ṹ��
typedef struct Track_Data_Fusion
{
	int time;

	double x;
	double y;
	double z;

	int trackLabel;
}trackDataFusion;

//���ڵ���λ��ֱ������
typedef struct Gun_position
{
	char trackSource;

	double x;						//x������
	double y;						//y������
	double z;						//z������
}gunPosition;

#endif