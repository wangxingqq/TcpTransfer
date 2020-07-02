
#ifndef _RADARDEF_H_
#define _RADARDEF_H_

//类间共享变量
extern double detectionRange;
extern int gunTargetStatus;
extern int misTargetStatus;

//#define DEBUGPROGRAM	//输出调试信息
#define RELEASEVERSIONS	//发布版本
//#define ENTIRETYSIM		//联合炮车整体仿真
#define INSIDESIM		//内部仿真
#define SCREENSIZE

#define BIGFRONT 30		//字体大小
#define SMALLFRONT 15		//小字体大小

#define circle1 0.8
#define circle2 0.5
#define circle3 0.2

#define GUNNUM 1
#define BUFSIZE 256
#define MAX_CHAR       128
#define SINGLURVALUE 9999999		//奇异值
#define PI 3.14
#define BUF_SIZE 1024
// #define PERIOD_SET 1
// #define PERIOD_COM 3
#define TrackNum 10
#define DOTNUM 50					//点间隔，相当于50个20ms为1s
#define DLGRADARNUM_GUN 6

//是否摧毁标志
#define DAMAGE 00
#define NORMAL 01
//目标编号
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

//消息类型
#define RELEASEFILE 0x5502			//文件下发消息类型
#define TESTCONTROLCOM 0x5501		//试验控制指令消息类型
#define RELEASETARSTATUS 0x55A0		//发布目标状态
#define FEEDBACKCOM 0x55A1			//连指控给试验控制系统反馈
#define GUN2CONTROLMESSAGE 0x55A2	//炮车给总控
#define SENDALLOTRETTOGUN 0x55A5	//连指控给火控发送目标分配结果
#define RECVFUSIONDATA 0x55A6		//发送融合数据
#define GUN2MISSLE 0x55A4			//炮车给导弹

//网络编程
//试验控制指令
#define COM_SELFCHECK 0x0011		//系统自检指令
#define COM_SENDFILESIT 0x0022		//态势文件文件下发指令
#define COM_SENDFILETAR 0x0033		//目标文件下发指令
#define COM_TESTSTART 0x0055		//实验开始指令
#define COM_TIMEADVANCE 0X0088		//时间推进指令
#define COM_TESTSTOP 0x0066			//实验结束指令
#define COM_FILESAVE 0x0077			//实验数据转存

//反馈指令
#define ANS_SELFCHECKSUS 0x1100		//系统自检成功
#define ANS_SELFCHECKFAIL 0x11FF	//系统自检失败
#define ANS_RECVFILESITSUS 0x2200	//接收态势文件成功
#define ANS_RECVFILESITFAIL 0x22FF	//接收态势文件失败
#define ANS_RECVFILETARSUS 0x3300	//接收目标文件成功
#define ANS_RECVFILETARFAIL 0x33FF	//接收目标文件失败
#define ANS_FRAMEFINISH	0x2010		//单帧解算完成

//网络编程
#define EXITSIMULATION -1			//退出仿真
#define STARTSIMULATION 1			//开始仿真
#define TESTSIMULATION 2			//测试网络
#define RECVFILE 3					//发送文件
#define DEFAULT -2					//默认的无效信号
#define TARGETDAMAGE 5				//目标被击毁信号

#define ALLNUMRES 10				//接收目标分配数据
#define NOALLOT 11					//不进行目标分配 
#define SENDTRACKDATA 12			//给指挥车发送航迹数据

#define COMINFORM 110				//指挥车通知信号

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

//发送给显示模块的消息类型
#define SHOWTYPE 0x6601

#endif