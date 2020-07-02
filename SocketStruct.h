#ifndef _SOCKET_STRUCT_
#define _SOCKET_STRUCT_
#include "SearchRadarDlg.h"

#pragma pack(1)

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
	unsigned char targetcode10;
	unsigned char targetDamageStatus10;
}TargetStatus;

//连指控系统给试验控制系统发连指控单帧解算完成状态
typedef struct FRAMEFINISH
{
	unsigned int messageType;
	unsigned short int framefinish;
	int computerNum;
}FrameFinish;

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

//类型转换用结构体
typedef struct TYPETRANSFER
{
	unsigned int messageType;
}TypeTransfer;

#endif
