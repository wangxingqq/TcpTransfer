

#ifndef _RADAR_STRUCT_H_
#define _RADAR_STRUCT_H_

#include "RadarDef.h"

#pragma pack(1)

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

//火炮地理位置直角坐标
typedef struct Gun_position
{
	char trackSource;
	
	double x;						//x轴坐标
	double y;						//y轴坐标
	double z;						//z轴坐标
}gunPosition;

//声明
typedef struct SENDPARAM     
{
	double AS;       //火控解算跟踪线方位角
	double ES;       //火控解算跟踪线高低角
	double TF;       //飞行时间 
	
	double agc;		//增加
	double egc;		//增加
	double agc1;	//增加
	double egc1;	//增加

	double azimuth_drawTran;//用于外部画白色三角
}SendParam;

//通信用结构体
typedef struct Message
{
	unsigned int messageType;
	int data;
	int time;
	float azimuth_x[TrackNum];
	float elevation_y[TrackNum];
	float distance_z[TrackNum];
	char trackSource;
	int t_num;
	int damageNum;
}MESSAGE;

//指令数据结构
typedef struct COMMAND
{
	unsigned int messageType;
	short int commandCode;
	int compOrTimeNum;
}Command;

//发送文件数据结构
typedef struct SENDFILENEW
{
	unsigned int messageType;
	unsigned int fileFrame;
	unsigned int frameLen;
	char buf[10240];
}SendFileNew;

//目标状态
typedef struct TARGETSTATUS
{
	unsigned int messageType;
	unsigned char targetcode1;
	unsigned char targetDamageStatus1;
	unsigned char targetcode2;
	unsigned char targetDamageStatus2;
	unsigned char targetcode3;
	unsigned char targetDamageStatus3;
	unsigned char targetcode4;
	unsigned char targetDamageStatus4;
	unsigned char targetcode5;
	unsigned char targetDamageStatus5;
	unsigned char targetcode6;
	unsigned char targetDamageStatus6;
	unsigned char targetcode7;
	unsigned char targetDamageStatus7;
	unsigned char targetcode8;
	unsigned char targetDamageStatus8;
	unsigned char targetcode9;
	unsigned char targetDamageStatus9;
	unsigned char targetcode0;
	unsigned char targetDamageStatus0;
}TargetStatus;

//火控系统与试验控制系统
typedef struct GUN2CONTROL
{
	unsigned int messageType;			//消息类型
	int gunNum;							//火控计算机节点编号
	unsigned short int framefinish;		//单帧解算完成状态
 	unsigned char attackTargetNum;		//武器打击目标编号 1
 	unsigned short int targetStatus;		//打击上述目标的炮弹脱靶量小于杀伤半径的个数 1
}Gun2Control;

//火控与防空导弹系统
typedef struct GUN2AIRDEFENSEMISSLE
{
	unsigned int messageType;				//消息类型
	unsigned char targetShot;				//攻击目标编号
	long int missle_x;						//导弹X坐标
	long int missle_y;						//导弹Y坐标
	long int missle_z;						//导弹Z坐标
	long int missle_AngleOfPitch;			//导弹俯仰角
	long int missle_yawAngle;				//导弹偏航角
}gun2AirDefMis;

//类型转换用结构体
typedef struct TYPETRANSFER
{
	unsigned int messageType;
}TypeTransfer;
//向显示模块发送数据用结构体
typedef struct SENDTOSHOW
{
	unsigned int messageType;
	double at;
	double et;
	double dd;  
}SendToShow;  

#endif