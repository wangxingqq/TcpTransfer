
// openglViewDlg.h : 头文件
//
#if !defined(AFX_OPENGLVIEWDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_)
#define AFX_OPENGLVIEWDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Scene.h"
#include "opencv\cv.h"
#include "afxwin.h"
#include "afxext.h"
#include <math.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "RadarStruct.h"
#include "RadarDef.h"
#include "targetdata.h"
using namespace std;
// CopenglViewDlg 对话框

class CopenglViewDlg : public CDialogEx
{
// 构造
public:
	CopenglViewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPENGLVIEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	//添加多线程
	static DWORD CALLBACK RecvProc(LPVOID lpParameter);
	static char consoleData[1024];			//控制台buffer	
	static HANDLE hdlWrite;					//控制台窗口句柄

	static struct sockaddr_in addr_cont;			//给总控发送端地址
	static struct sockaddr_in addr_comm;			//给指挥车发送端地址
	static struct sockaddr_in addr_miss;			//给导弹发送端地址
	static struct sockaddr_in addr_show;			//显示模块发送端地址

	static SOCKET m_socketSend_cont;			//给总控发数据socket
	static SOCKET m_socketSend_comm;			//给指挥车发数据socket
	static SOCKET m_socketSend_miss;			//给导弹发数据socket
	static SOCKET m_socketSend_show;			//给显示模块发送数据socket

	static BOOL startOrNot;
public:
	int TransferCoor(float Rx, float Ry);
	//double com_RangeChange;
	//double gun_RangeChange;
	double com_x;
	double com_y;
	double com_z;

public:
	//////////////////////////////网络编程/////////////////////////////////////
	BOOL InitSocketRecv();
	BOOL InitSocketSend();
	SOCKET socket_create();
	SOCKET socket_accept(SOCKET listen_st);
	//void SendData2Com(int periodCom);
	void RecvTargetStatus(TargetStatus *);		//接收目标状态
	float TransferPixel(float angle);           //弧度->像素点
	BOOL RecvXMLFileUDP(char *filename);		//接收态势文件UDP协议

	int hostport;					//接收端口号
	int genConPort;					//总控端口号
	int commandPort;				//指挥车端口号
	int misslePort;					//导弹端口
	int showPort;					//显示模块端口号

	const char* hostname;			//本机IP
	const char* ServerIP;			//总控IP
	const char* missleIP;			//导弹IP
	const char* commandIP;			//指挥车IP
	const char* showIP;				//显示模块IP
	SOCKADDR_IN addrSock_broad;		//用来从网络的广播地址上接收数据

	int tcpPort;					//TCP文件发送
	SOCKET m_socketRecv;			//接收端口
	void TimeAdvance();					//时间推进
	int t_num;						//存储接收到的目标编号
	int dotCountNow;					//当前进行到的航迹点数
	SendToShow show;
	////程序中用到的时间控制相关变量
	int periodSum;										//模拟总周期数
	int period;											//仿真周期模拟
	int count;											//记录仿真时间
	int second;											//记录20ms周期次数
	//目标分配
	double x_allot1;				//当前点
	double y_allot1;
	double x_allot2;				//前一点
	double y_allot2;
	int index_targetDamage[TrackNum];
	int index_readXML;				//是否解析了XML文件标识
//	BOOL AnalysisFile(char *filename);
//	BOOL RecvFileTCP(char *filename);
	BOOL RecvFileUDP(char *filename);
	bool ReadXmlFile(string& szFileName);	//读取xml格式文件
	void UTF8ToGBK(char *&szOut);			//字符编码格式转换函数

	//从InitData中读取到的变量
	int file_trackNum;
	int file_dotNum;
	//从XML文件读取到的各种参数
	double angleOfRoll;					//横摇角
	double angleOfPitching;				//纵摇角
	double courseAngle;					//航向角
	double surAcc_angleOfRoll;			//测量精度横摇角
	double surAcc_angleOfPitching;		//测量精度纵摇角
	double surAcc_courseAngle;			//测量精度航向角
	double laserPeriod;					//激光回波周期
	double searchRadar_dis;				//搜索雷达威力范围
	double searchRadar_per;				//搜索雷达扫描周期 
	double searchRadar_acc;				//搜索雷达扫描精度
	double searchRadar_cap;				//搜索雷达目标容量
	double trackRadar_distance;			//火控跟踪雷达威力范围
	double trackRadar_accuracy;			//火控跟踪雷达跟踪精度
	double pe_TVTrackInspect;			//光电跟踪电视跟踪视场
	double pe_INTrackInspect;			//光电跟踪红外跟踪视场
	double gunFireDis;					//火炮射击火力范围
	double gunFireFre;					//火炮射击射频
	double gunFireRate;					//火炮射击射速
	//火控
	SendParam *pSend;					//火控用结构体变量
	TargetData objectFire;				//定义火控类对象
public:
	//火炮坐标操作
	trackDataPolar* GunCoordinate(int numSum, gunPosition *gp, trackdata *InitData, trackDataPolar 	**guntdpFire, trackDataPolar **guntdpFire1);		//火炮坐标操作
	int PolarToRec_Gun(trackDataPolar *tdpr);		//极坐标转直角坐标
	void GenerateData();						//航迹数据生成
	trackDataPolar *guntdpFire1;				//航迹数据结构体数组
	trackDataPolar **data_period;				//按照周期存储航迹数据结构体数组
	trackDataPolar *guntdp;					//航迹数据结构体数组
	trackDataPolar *guntdpFire;					//航迹数据结构体数组
	gunPosition *gp;							//火炮地理位置结构体数组

private:
	//从配置文件中读取到的变量值
	double com_searchDistance;			//连指挥车雷达威力范围
	double com_searchPeriod;			//连指挥车扫描周期值
	double com_searchAccuracy;			//连指挥车扫描精度
	double com_TargetCapacity;			//连指挥车目标容量

	double gun_searchDistance;			//炮车搜索雷达威力
	double gun_searchPeriod;			//炮车搜索雷达周期

	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg void OnXML();//读取态势文件
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CRect CalcDrawRect(CRect rect,IplImage *image);
	void DrawFrame(int id,IplImage *image);

	IplImage *frame_image;
	HWND m_sceneWnd;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	CComboBox m_cb1;
	//CComboBox m_cb2;
	//afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_cb3;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox m_cb4;
	afx_msg void OnCbnSelchangeCombo4();
//	CComboBox m_cb5;
//	afx_msg void OnCbnSelchangeCombo5();
	CComboBox m_cb6;
	afx_msg void OnCbnSelchangeCombo6();
//	CComboBox m_cb7;
	//afx_msg void OnCbnSelchangeCombo7();
	CComboBox m_cb8;
	afx_msg void OnCbnSelchangeCombo8();
//	CBitmapButton CBitmapButton_1;
//	CButton CBitmapButton_2;
	CBitmapButton CBitmapButton_2;
	CBitmapButton CBitmapButton_3;
//	CEdit sum;
	afx_msg void OnEnChangeEdit8();
	int sum;
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit16();
	afx_msg void OnEnChangeEdit17();
	afx_msg void OnEnChangeEdit18();
	CString TargetSort;
	CEdit Tgt1;
	CEdit model;
	CEdit m_TraceSort;
	CEdit m_view;
	afx_msg void OnBnClickedXml();  //读取态势文件
	CEdit m_position_x;
	CEdit m_position_y;
	CEdit m_position_z;

	double m_IRorTV;
	afx_msg void OnCbnSelchangeCombo9();
	CComboBox m_cb9;
	double m_dotRadius;
	double m_dotColor;
	double m_bgColor;
};
#endif