
#ifndef _RADARDEF_H_
#define _RADARDEF_H_

//��乲�����
extern double detectionRange;
extern int gunTargetStatus;
extern int misTargetStatus;

//#define DEBUGPROGRAM	//���������Ϣ
#define RELEASEVERSIONS	//�����汾
//#define ENTIRETYSIM		//�����ڳ��������
#define INSIDESIM		//�ڲ�����
#define SCREENSIZE

#define BIGFRONT 30		//�����С
#define SMALLFRONT 15		//С�����С

#define circle1 0.8
#define circle2 0.5
#define circle3 0.2

#define GUNNUM 1
#define BUFSIZE 256
#define MAX_CHAR       128
#define SINGLURVALUE 9999999		//����ֵ
#define PI 3.14
#define BUF_SIZE 1024
// #define PERIOD_SET 1
// #define PERIOD_COM 3
#define TrackNum 10
#define DOTNUM 50					//�������൱��50��20msΪ1s
#define DLGRADARNUM_GUN 6

//�Ƿ�ݻٱ�־
#define DAMAGE 00
#define NORMAL 01
//Ŀ����
#define TARGET01 1	
#define TARGET02 2
#define TARGET03 3
#define TARGET04 4
#define TARGET05 5
#define TARGET06 6
#define TARGET07 7
#define TARGET08 8
#define TARGET09 9
#define TARGET10 10		

//��Ϣ����
#define RELEASEFILE 0x5502			//�ļ��·���Ϣ����
#define TESTCONTROLCOM 0x5501		//�������ָ����Ϣ����
#define RELEASETARSTATUS 0x55A0		//����Ŀ��״̬
#define FEEDBACKCOM 0x55A1			//��ָ�ظ��������ϵͳ����
#define GUN2CONTROLMESSAGE 0x55A2	//�ڳ����ܿ�
#define SENDALLOTRETTOGUN 0x55A5	//��ָ�ظ���ط���Ŀ�������
#define RECVFUSIONDATA 0x55A6		//�����ں�����
#define GUN2MISSLE 0x55A4			//�ڳ�������

//������
//�������ָ��
#define COM_SELFCHECK 0x0011		//ϵͳ�Լ�ָ��
#define COM_SENDFILESIT 0x0022		//̬���ļ��ļ��·�ָ��
#define COM_SENDFILETAR 0x0033		//Ŀ���ļ��·�ָ��
#define COM_TESTSTART 0x0055		//ʵ�鿪ʼָ��
#define COM_TIMEADVANCE 0X0088		//ʱ���ƽ�ָ��
#define COM_TESTSTOP 0x0066			//ʵ�����ָ��
#define COM_FILESAVE 0x0077			//ʵ������ת��

//����ָ��
#define ANS_SELFCHECKSUS 0x1100		//ϵͳ�Լ�ɹ�
#define ANS_SELFCHECKFAIL 0x11FF	//ϵͳ�Լ�ʧ��
#define ANS_RECVFILESITSUS 0x2200	//����̬���ļ��ɹ�
#define ANS_RECVFILESITFAIL 0x22FF	//����̬���ļ�ʧ��
#define ANS_RECVFILETARSUS 0x3300	//����Ŀ���ļ��ɹ�
#define ANS_RECVFILETARFAIL 0x33FF	//����Ŀ���ļ�ʧ��
#define ANS_FRAMEFINISH	0x2010		//��֡�������

//������
#define EXITSIMULATION -1			//�˳�����
#define STARTSIMULATION 1			//��ʼ����
#define TESTSIMULATION 2			//��������
#define RECVFILE 3					//�����ļ�
#define DEFAULT -2					//Ĭ�ϵ���Ч�ź�
#define TARGETDAMAGE 5				//Ŀ�걻�����ź�

#define ALLNUMRES 10				//����Ŀ���������
#define NOALLOT 11					//������Ŀ����� 
#define SENDTRACKDATA 12			//��ָ�ӳ����ͺ�������

#define COMINFORM 110				//ָ�ӳ�֪ͨ�ź�

// #define COMMANDVEHICLE 201
#define GUNVEHICLE_1 301
// #define GUNVEHICLE_2 302
// #define GUNVEHICLE_3 303
// #define GUNVEHICLE_4 304
// #define GUNVEHICLE_5 305
// #define GUNVEHICLE_6 306


#define SLEEPTIME_1 20
//#define SLEEPTIME_2 40
//#define SLEEPTIME_3 60
//#define SLEEPTIME_4 80
//#define SLEEPTIME_5 100
//#define SLEEPTIME_6 120

#define GUNID1 "12"
//#define GUNID2 "13"
//#define GUNID3 "14"
//#define GUNID4 "15"
//#define GUNID5 "16"
//#define GUNID6 "17"

//���͸���ʾģ�����Ϣ����
#define SHOWTYPE 0x6601

#endif