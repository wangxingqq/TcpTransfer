
#if !defined(AFX_SEARCHRADARDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_)
#define AFX_SEARCHRADARDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSearchRadarDlg dialog

#include "Radar.h"
#include "RadarDef.h"
#include "SocketStruct.h"
#include "Fusion.h"
#include <vector>
using namespace std;

class CSearchRadarDlg : public CDialog
{
	// Construction
public:
	CSearchRadarDlg(CWnd* pParent = NULL);	// standard constructor
	~CSearchRadarDlg();
	//类内静态变量及函数
public:
	//添加多线程
	static DWORD CALLBACK RecvProc(LPVOID lpParameter);
	static BOOL startOrNot;

public:
	/////////////////////////OpenGl画图用函数和变量/////////////////////////////////////	
	BOOL SetWindowPixelFormat(HDC hDC);   //设定象素格式 
	BOOL CreateViewGLContext(HDC hDC);    //View GL Context 
	void RenderScene();                   //绘制场景 
	void CSearchRadarDlg::TransferCoor( float Rx,float Ry, int A[2][3]);
	void drawString(const char* str);
	void selectFont(int size, int charset, const char* face);
	void drawCNString(const char* str);
	void RandomNumber1();					//用于产生一批随机噪声
	void RandomNumber2();					//用于产生单个随机噪声
	void DrawRandomNoise();					//用于产生一批随机噪声
	void DrawSingleRandomNoise();			//用于产生单个随机噪声
	HDC hrenderDC;							//DC 
	HGLRC hrenderRC;						//RC 
	CBrush brush;	
	int PixelFormat; 
	double dxx;								//用于根据不同周期计算扫线每次自加不同的角度
	double dx;								//扫线转过的弧度,保证程序最开始运行时不会计算威胁度等数值
	int noiseIndex;							//随机噪声用	
	double x[TrackNum];						//航迹显示中转数组
	double y[TrackNum];
	double z[TrackNum];
	double showDamageTarX[TrackNum];		//用于当目标被击毁后，航迹标志的显示
	double showDamageTarY[TrackNum];
	double com_RangeChange;
	double gun_RangeChange;
	double com_x;
	double com_y;
	double com_z;

public:
	//有关对话框
	CRect m_rect;

public:
	//////////////////////////////网络编程/////////////////////////////////////
	//UDP
	SOCKADDR_IN addrSockBroadcast;						//用来从网络的广播地址上接收数据
	SOCKET m_socketSend_gun;							//给炮车发送数据socket
	SOCKET m_socketSend_cont;							//给总控发送数据socket
	SOCKET m_recvsocket;								//接收socket	
	int tcpPort;										//TCP端口号	
	int udpPort_gun;									//给炮车发数据UDP端口号
	int udpPort_cont;									//给总控发数据UDP端口号
	int udpPort_recv;									//接收端口
	char serverIP[15];								//总控IP
	char hostIP[15];								//本地IP
	char gun1_IP[15];								//炮车IP地址
	char gun2_IP[15];
	char gun3_IP[15];
	char gun4_IP[15];
	char gun5_IP[15];
	char gun6_IP[15];
	//各炮车地址
	struct sockaddr_in addrGunInform1;					//建立炮车地址
	struct sockaddr_in addrGunInform2;
	struct sockaddr_in addrGunInform3;
	struct sockaddr_in addrGunInform4;
	struct sockaddr_in addrGunInform5;
	struct sockaddr_in addrGunInform6;
	//总控地址
	struct sockaddr_in addrGeneralCon;					//发送端地址

	BOOL InitSocketRecv();
	BOOL InitSocketSend();	
	BOOL LoadConfFile();
	BOOL SendData(int sendIndex,char *data,int dataLen);	//发送数据函数	
	SOCKET socket_create();									//TCP文件发送
	SOCKET socket_accept(SOCKET listen_st);
	BOOL RecvFileTCP(char *filename);							//接收目标文件TCP协议
	BOOL RecvFileUDP(char *filename);							//接收目标文件UDP协议
	BOOL RecvXMLFileUDP(char *filename);						//接收态势文件UDP协议
	void RecvTargetStatus(TargetStatus *);					//接收目标状态
	void SendAllotNum(int gp_num,int *index_send,const char *gun_IP);				//发送目标分配数据
	void RecvGunSendFusionData(MESSAGE *);					//接收炮车发送过来的融合数据
	void SetaddrGunInform();								//设置各个客户端地址
	BOOL ReadXmlFile(string& szFileName);					//读取xml格式文件
	void UTF8ToGBK(char *&szOut);							//字符编码格式转换函数

public:
	//////////////////////////////////数据解算/////////////////////////////////
	int PreFusionData(trackdata* InitData,int period_set);						//仿真开始前坐标操作
	trackDataPolar* ComCoordinate(int numSum,trackdata* InitData,int period_set);					//指挥车坐标操作
	trackDataPolar* GunCoordinate(int numSum,gunPosition *gp,trackdata* InitData);	//火炮坐标操作
	BOOL AnalysisFIle(char *filename);							//文件解析	
	void JudgeThreatDegree();									//用于连指挥车为中心目标威胁度判断
	int ThreatCal();											//目标相对于火炮威胁度计算
	int targetAllot();											//目标分配
	int UpdateAllotTarget(int gp_num,const char *gun_IP);		//目标被击毁后重新分配目标	
	void TimeAdvance();											//时间推进

public:	
	//程序中用到的时间控制相关变量
	int periodSum;				//模拟总周期数
	int second;					//记录20ms周期次数
	int times;					//记录1s周期次数，-1为了能在dx > 2PI时显示正确的航迹数据
	int period_set;				//指挥车周期
	int period;					//本函数中用到的模拟周期
	int countMessageLoop;		//程序运行时间周期数
	//目标分配相关
	int t_num[dlgRadarNum_gun];					//目标分配编号存储
	int index_send[dlgRadarNum_gun];			//记录是否发送了目标分配结果
	BOOL index_updateTarget[dlgRadarNum_gun];	//是否重新目标分配
	int index_targetDamage[TrackNum];			//目标是够被摧毁数组
	double ThreatDegree[dlgRadarNum_gun+1][TrackNum];	//用于最后存放威胁度值的数组，最后一行是目标编号
	int allotNum[dlgRadarNum_gun+1][TrackNum];			//目标编号
	int threatIndex[TrackNum];							//存放威胁度排序后的目标编号
	//航迹融合
	Fusion *fs;							//创建航迹融合类对象
	trackDataPolar *comtdp;				//用于接收指挥车处理后航迹数据
	gunPosition *gp;					//定义火炮地理位置坐标结构体数组并初始化
	trackDataPolarRec **data_period;	//动态开辟按周期存储航迹数据,一维是周期数
	//接收火炮数据相关		
	int n_recvTrackData;			//接收炮车航迹数据标志	
	int t;							//控制接收的火炮目标数据的个数		
	//控制台
	char consoleData[1024];			//控制台buffer
	HANDLE hdlWrite;				//控制台窗口句柄	
	int analyTarFileIndex;			//是否进行了目标文件文件解析标志
	int analyXMLFileIndex;			//是否进行了xml文件解析标志
	int index_readXML;

private:
	//从配置文件中读取到的变量值
	double com_searchDistance;			//连指挥车雷达威力范围
	double com_searchPeriod;			//连指挥车扫描周期值
	double com_searchAccuracy;			//连指挥车扫描精度
	double com_TargetCapacity;			//连指挥车目标容量

	double gun_searchDistance;			//炮车搜索雷达威力
	double gun_searchPeriod;			//炮车搜索雷达周期

	//从目标文件中读到的数据
	int file_trackNum;
	int file_trackNum1;
	int file_dotNum;
	/////////////分离坐标值各位///////////////
	float R1x,R1y;
	float R2x,R2y;
	float R3x,R3y;
	float R4x,R4y;
	float R5x,R5y;
	float R6x,R6y;
	
	////////////雷达范围圆相关变量////////////
	float Range;
	float RangeSearch;
	
	float RangeScale1X,RangeScale1Y;
	float RangeScale2X,RangeScale2Y;
	float RangeScale3X,RangeScale3Y;
	float RangeScale4X,RangeScale4Y;
	float RangeScale5X,RangeScale5Y;
	float RangeScale6X,RangeScale6Y;

	//////////////各炮车位置//////////////
	float RadarX[6],RadarY[6];

	float mNumberX;
	float mNumberY;
	float singleNumberX;
	float singleNumberY;
	float m1;								//用于记录噪声正负
	float m2;								//用于记录噪声正负

	double randomNumber1;
	double randomNumber2;

public:
// Dialog Data
	//{{AFX_DATA(CSearchRadarDlg)
	enum { IDD = IDD_RENDER };
	CComboBox	m_combobox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchRadarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSearchRadarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelMode();
	afx_msg void OnTEST();//系统自检
	afx_msg void OnXML();//读取态势文件
	afx_msg void OnDATA();//读取数据文件
	afx_msg void OnSTART();//开始
	afx_msg void OnWAIT();//暂停
	afx_msg void OnOUT();//退出
	afx_msg void OnPeriodSet();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnTargetNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHRADARDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_)
