
#ifndef _RADAR_H_
#define _RADAR_H_

#include "RadarDef.h"

//航迹原始数据结构体
typedef struct Track_Data_Orig
{
	int iTime;						//时间	
	double x;						//x轴坐标
	double y;						//y轴坐标
	double z;						//z轴坐标

	char trackSource;
}trackdata;

//航迹极坐标结构体
typedef struct Track_Data_Polar
{
	int  time;						//时间
	double  azimuth;				//目标方位角
	double  elevation;				//目标高低角
	double  distance;				//目标距离

	char trackSource;
}trackDataPolar;

//航迹极坐标直角坐标转化结构体
typedef struct Track_Data_Polar_Rec
{
	int  time;						//时间
	double  azimuth_x;				//目标方位角
	double  elevation_y;			//目标高低角
	double  distance_z;				//目标距离

	double speedX;
	double speedY;
	double speedZ;

	char trackSource;				//标志
}trackDataPolarRec;

//存放融合后航迹结构体
typedef struct Track_Data_Fusion
{
	int time;

	double x;
	double y;
	double z;

	int trackLabel;
}trackDataFusion;

//火炮地理位置直角坐标
typedef struct Gun_position
{
	char trackSource;

	double x;						//x轴坐标
	double y;						//y轴坐标
	double z;						//z轴坐标
}gunPosition;

#endif