

#ifndef _RADAR_STRUCT_H_
#define _RADAR_STRUCT_H_

#include "RadarDef.h"

#pragma pack(1)

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

//���ڵ���λ��ֱ������
typedef struct Gun_position
{
	char trackSource;
	
	double x;						//x������
	double y;						//y������
	double z;						//z������
}gunPosition;

//����
typedef struct SENDPARAM     
{
	double AS;       //��ؽ�������߷�λ��
	double ES;       //��ؽ�������߸ߵͽ�
	double TF;       //����ʱ�� 
	
	double agc;		//����
	double egc;		//����
	double agc1;	//����
	double egc1;	//����

	double azimuth_drawTran;//�����ⲿ����ɫ����
}SendParam;

//ͨ���ýṹ��
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

//ָ�����ݽṹ
typedef struct COMMAND
{
	unsigned int messageType;
	short int commandCode;
	int compOrTimeNum;
}Command;

//�����ļ����ݽṹ
typedef struct SENDFILENEW
{
	unsigned int messageType;
	unsigned int fileFrame;
	unsigned int frameLen;
	char buf[10240];
}SendFileNew;

//Ŀ��״̬
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

//���ϵͳ���������ϵͳ
typedef struct GUN2CONTROL
{
	unsigned int messageType;			//��Ϣ����
	int gunNum;							//��ؼ�����ڵ���
	unsigned short int framefinish;		//��֡�������״̬
 	unsigned char attackTargetNum;		//�������Ŀ���� 1
 	unsigned short int targetStatus;		//�������Ŀ����ڵ��Ѱ���С��ɱ�˰뾶�ĸ��� 1
}Gun2Control;

//�������յ���ϵͳ
typedef struct GUN2AIRDEFENSEMISSLE
{
	unsigned int messageType;				//��Ϣ����
	unsigned char targetShot;				//����Ŀ����
	long int missle_x;						//����X����
	long int missle_y;						//����Y����
	long int missle_z;						//����Z����
	long int missle_AngleOfPitch;			//����������
	long int missle_yawAngle;				//����ƫ����
}gun2AirDefMis;

//����ת���ýṹ��
typedef struct TYPETRANSFER
{
	unsigned int messageType;
}TypeTransfer;
//����ʾģ�鷢�������ýṹ��
typedef struct SENDTOSHOW
{
	unsigned int messageType;
	double at;
	double et;
	double dd;  
}SendToShow;  

#endif