
// openglViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "openglView.h"
#include "openglViewDlg.h"
#include "resource.h"
#include "windows.h"
#include "stdlib.h"
#include "time.h"
#include "RadarDef.h"
#include "RadarStruct.h"
#include "afxdialogex.h"
#include "Processing.h"
#include "tinyxml.h"
#include "string"
#include "vector"
#include "fstream"
#include "iostream"
#include  <winsock2.h>
#include "targetdata.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//点目标灰度
extern double dotColor;
//背景灰度
extern double bgColor;
//红外检测频率标识
bool inf_mark = true; //每秒10次
float k;             //弧度像素点系数，输入/K得到像素点个数，输出乘以K
//模式切换参数声明
extern bool Rader;
extern bool reverse_color;
extern bool fire;
extern bool Inf;
extern bool tv;
extern float Vn;
extern bool missile;
extern bool f22;
extern bool ball;
extern bool vdo;

//stop
extern bool stop;
//strat
extern bool start_test;
//tracking
extern bool edge;
extern bool contrast;
extern bool minusing;
// CopenglViewDlg 对话框
//面积
extern int Sumtarget;
//视场->目标大小
extern float scalea;
extern float scaleb;
extern float Vt;
extern bool destroy_f22;
extern bool destroy_missile;
extern bool bgcolor_default;
extern bool bgcolor_gray;
extern bool bgcolor_black;
extern CvPoint target_pos;
extern float D1;
bool LaserDis;
CString str1;
struct RECVPARAM
{
	SOCKET sock;//已创建的套接字
	HWND hwnd;//对话框句柄
	CopenglViewDlg *pThis;
}RecvParam;

double **fire_ami = NULL;						//用于火控解算方位角数组
double **fire_ele = NULL;						//用于火控解算高低角数组
double **fire_dis = NULL;						//用于火控解算距离数组

char CopenglViewDlg::consoleData[1024];				//控制台buffer	
HANDLE CopenglViewDlg::hdlWrite;						//控制台窗口句柄
SOCKET CopenglViewDlg::m_socketSend_comm;
SOCKET CopenglViewDlg::m_socketSend_cont;
SOCKET CopenglViewDlg::m_socketSend_miss;
SOCKET CopenglViewDlg::m_socketSend_show;
BOOL CopenglViewDlg::startOrNot = FALSE;
struct sockaddr_in CopenglViewDlg::addr_comm;
struct sockaddr_in CopenglViewDlg::addr_cont;
struct sockaddr_in CopenglViewDlg::addr_miss;
struct sockaddr_in CopenglViewDlg::addr_show;
double detectionRange = 0;
int gunTargetStatus = 0;
int misTargetStatus = 0;




CopenglViewDlg::CopenglViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CopenglViewDlg::IDD, pParent)
	, sum(0)
	, TargetSort(_T(""))
	, m_IRorTV(0)
	, m_dotRadius(0)
	, m_dotColor(0)
	, m_bgColor(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	frame_image = NULL;
	
	////////////////////////网络编程///////////////////////////////
	hostport = 6000;				//本地接收端口
	commandPort = 6000;				//指挥车端口号
	showPort = 6000;				//显示模块端口号
	misslePort = 0;					//导弹端口号
	t_num = 0;						//航迹编号
#ifdef ENTIRETYSIM
	//待修改
	hostname = "172.25.17.79";		//本客户端IP
	ServerIP = "172.25.17.79";		//总控IP
	commandIP = "172.25.17.79";	//指挥车IP
	missleIP = "";					//导弹IP
	genConPort = 7002;				//总控端口号
#else
	//待修改
	hostname = "172.25.17.79";		//本客户端IP
	ServerIP = "172.25.17.79";		//总控IP
	commandIP = "172.25.17.79";	//指挥车IP
	showIP = "172.25.17.98";
	missleIP = "";					//导弹IP
	genConPort = 6001;				//总控端口号
#endif
	count = 0;
	period = -1;						//本函数中用到的模拟周期	
	second = 0;
	index_readXML = 0;
	
	memset(consoleData, 0, sizeof(consoleData));

	gp = (gunPosition*)malloc(DLGRADARNUM_GUN * sizeof(gunPosition));
	guntdp = NULL;
	guntdpFire = NULL;
	guntdpFire1 = NULL;
	data_period = NULL;
	////////////////////////opengl相关变量//////////////////////////
	com_x = 0;
	com_y = 0;
	com_z = 0;

}

void CopenglViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cb1);
	//	DDX_Control(pDX, IDC_COMBO2, m_cb2);
	DDX_Control(pDX, IDC_COMBO3, m_cb3);
	DDX_Control(pDX, IDC_COMBO4, m_cb4);
	//  DDX_Control(pDX, IDC_COMBO5, m_cb5);
	DDX_Control(pDX, IDC_COMBO6, m_cb6);
	//  DDX_Control(pDX, IDC_COMBO7, m_cb7);
	DDX_Control(pDX, IDC_COMBO8, m_cb8);
	//DDX_Control(pDX, IDC_BUTTON1, CBitmapButton_1);
	//  DDX_Control(pDX, IDC_BUTTON2, CBitmapButton_2);
	//DDX_Control(pDX, IDC_BUTTON2, CBitmapButton_2);
	DDX_Control(pDX, IDC_BUTTON3, CBitmapButton_3);
	//  DDX_Control(pDX, IDC_EDIT8, sum);
	//DDX_Text(pDX, IDC_EDIT8, sum);
	//DDX_Text(pDX, IDC_EDIT5, TargetSort);
	DDX_Control(pDX, IDC_EDIT5, Tgt1);
	DDX_Control(pDX, IDC_EDIT4, model);
	DDX_Control(pDX, IDC_EDIT2, m_TraceSort);
	DDX_Control(pDX, IDC_EDIT3, m_view);
	DDX_Control(pDX, IDC_EDIT9, m_position_x);
	DDX_Control(pDX, IDC_EDIT10, m_position_y);
	DDX_Control(pDX, IDC_EDIT11, m_position_z);
	DDX_Text(pDX, IDC_EDIT1, m_IRorTV);
	DDX_Control(pDX, IDC_COMBO9, m_cb9);
	DDX_Text(pDX, IDC_EDIT16, m_dotRadius);
	DDX_Text(pDX, IDC_EDIT17, m_dotColor);
	DDX_Text(pDX, IDC_EDIT18, m_bgColor);
}

BEGIN_MESSAGE_MAP(CopenglViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CopenglViewDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CopenglViewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CopenglViewDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CopenglViewDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CopenglViewDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CopenglViewDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CopenglViewDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CopenglViewDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CopenglViewDlg::OnBnClickedButton6)
//	ON_BN_CLICKED(IDC_BUTTON8, &CopenglViewDlg::OnBnClickedButton8)
//	ON_BN_CLICKED(IDC_BUTTON9, &CopenglViewDlg::OnBnClickedButton9)
	//ON_CBN_SELCHANGE(IDC_COMBO2, &CopenglViewDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CopenglViewDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CopenglViewDlg::OnCbnSelchangeCombo4)
//	ON_CBN_SELCHANGE(IDC_COMBO5, &CopenglViewDlg::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CopenglViewDlg::OnCbnSelchangeCombo6)
	//ON_CBN_SELCHANGE(IDC_COMBO7, &CopenglViewDlg::OnCbnSelchangeCombo7)
	ON_CBN_SELCHANGE(IDC_COMBO8, &CopenglViewDlg::OnCbnSelchangeCombo8)
//	ON_EN_CHANGE(IDC_EDIT8, &CopenglViewDlg::OnEnChangeEdit8)
//	ON_EN_CHANGE(IDC_EDIT5, &CopenglViewDlg::OnEnChangeEdit5)
ON_BN_CLICKED(IDC_XML, &CopenglViewDlg::OnBnClickedXml)
ON_CBN_SELCHANGE(IDC_COMBO9, &CopenglViewDlg::OnCbnSelchangeCombo9)
END_MESSAGE_MAP()


// CopenglViewDlg 消息处理程序
BOOL CopenglViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef INSIDESIM
	//打开DOS窗口
	AllocConsole();
	hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE);
#endif	

	///////////////////////Socket初始化//////////////////////////
	if (InitSocketSend() && InitSocketRecv())
	{

	}
	else
	{
		MessageBox(_T("socket初始化失败！"));
		//exit(EXIT_FAILURE);
	}

//#ifdef INSIDESIM
//	//打开DOS窗口
//	AllocConsole();
//	hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE);
//#endif

	///////////////////////创建接收线程//////////////////////////
	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socketRecv;
	pRecvParam->hwnd = m_hWnd;
	pRecvParam->pThis = this;

	//创建接收线程
	HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	CloseHandle(hThread);
	//InitSocketRecv();
	//InitSocketSend();



	//
//	CBitmapButton_1.LoadBitmaps(IDB_BITMAP1);   //载入照片  
//	CBitmapButton_1.SizeToContent();  //使按钮适应图片大小 
//	CBitmapButton_2.LoadBitmaps(IDB_BITMAP2);   //载入照片  
//	CBitmapButton_2.SizeToContent();  //使按钮适应图片大小 
	CBitmapButton_3.LoadBitmaps(IDB_BITMAP4);   //载入照片  
	CBitmapButton_3.SizeToContent();  //使按钮适应图片大小 
	//默认设置显示
	//SetDlgItemText(IDC_EDIT1, "2.4至7.8");
	SetDlgItemText(IDC_EDIT2, "红外");
	SetDlgItemText(IDC_EDIT3, "5.6*4.2IR");
	SetDlgItemText(IDC_EDIT4, "对比度跟踪");
	SetDlgItemText(IDC_EDIT5, "固定翼飞机");
	SetDlgItemText(IDC_EDIT16, "0");
	SetDlgItemText(IDC_EDIT17, "0");
	SetDlgItemText(IDC_EDIT18, "0");
	//探测方式 cb1
	m_cb1.AddString("--目标探测方式选择--");
	m_cb1.AddString("------红外------");
	m_cb1.AddString("------TV------");
//	m_cb1.AddString("------雷达------");
	m_cb1.SetCurSel(0);
	// TODO: 在此添加额外的初始化代码		
	//放大倍数 cb2
	//m_cb2.AddString("-----放大倍数选择-----");
	//m_cb2.AddString("二倍");
	//m_cb2.AddString("四倍");
	//m_cb2.AddString("八倍");
	//m_cb2.AddString("还原");
	//m_cb2.SetCurSel(0);
	//目标
	m_cb3.AddString("-----目标类型选择-----");
	m_cb3.AddString("----固定翼飞机----");
	m_cb3.AddString("-----巡航导弹-----");
	m_cb3.AddString("-----点目标-----");
	m_cb3.SetCurSel(0);
	//跟踪模式选择
	m_cb4.AddString("-----跟踪模式选择-----");
	m_cb4.AddString("-----边缘跟踪-----");
	m_cb4.AddString("----对比度跟踪----");
	m_cb4.AddString("-----取差跟踪-----");
	m_cb4.SetCurSel(0);
	////激光测距参数
	//m_cb5.AddString("--激光测距参数设置--");
	//m_cb5.SetCurSel(0);
	//跟踪波门设置
	m_cb6.AddString("-----跟踪视场设置-----");
		//m_cb6.AddString("----5.6*4.2IR----");
		//m_cb6.AddString("----7.8*5.85IR----");
		//m_cb6.AddString("----2.4*1.8TV----");
		//m_cb6.AddString("----5.6*4.2TV----");
	m_cb6.SetCurSel(0);
	////跟踪系统参数
	//m_cb7.AddString("--跟踪系统参数设置--");
	//m_cb7.AddString("方位");
	//m_cb7.AddString("高低");
	//m_cb7.SetCurSel(0);
	//视频存取
	m_cb8.AddString("-----视频与数据-----");
	m_cb8.AddString("-----录制视频-----");
	m_cb8.AddString("-----读取视频-----");
	m_cb8.SetCurSel(0);
	//BGCOLOR
	m_cb9.AddString("-----背景颜色选择-----");
	m_cb9.AddString("-----默认背景-----");
	m_cb9.AddString("-----灰色背景-----");
	m_cb9.AddString("-----黑色背景-----");
	m_cb9.SetCurSel(0);

	//MFC移植
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_OPENGL_VIEW);	
	pWnd->GetWindowRect(&rc);
	pWnd->MoveWindow(rc.left,rc.top,792, 588);	
	pWnd->GetClientRect(&rc);
	pWnd->ShowWindow(FALSE);
		
	m_sceneWnd = pWnd->m_hWnd;	
	SceneInit(m_sceneWnd,&frame_image);
	SetTimer(101,10,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopenglViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopenglViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopenglViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	SceneProc(m_sceneWnd,WM_TIMER,0,0);
	SceneProc(m_sceneWnd,WM_PAINT,0,0);

	CDialogEx::OnTimer(nIDEvent);
	DrawFrame(IDC_SCENE,frame_image);
	cvReleaseImage(&frame_image);
}

//计算图像绘制
CRect CopenglViewDlg::CalcDrawRect(CRect rect,IplImage *image)
{
	CRect drawRect;

	int width  = image->width;
	int height = image->height;	
	int x,y,w,h;		
	double scale = 1;
	if(width > rect.Width() || height > rect.Height()) //小图片，不缩放
	{	
		float xScale=(float)rect.Width()/(float)width;
		float yScale=(float)rect.Height()/(float)height;
		scale = (xScale>=yScale? yScale:xScale);	
	}

	w = int(width * scale);
	h = int(height * scale);
	x = (rect.Width() - w)/2;
	y = (rect.Height() - h)/2;		
	w = rect.Width() - 2 * x;
	h = rect.Height() - 2 * y;

	drawRect.left = rect.left + x;
	drawRect.top  = rect.top + y;
	drawRect.right  = drawRect.left + w;
	drawRect.bottom = drawRect.top  + h;

	return drawRect;
}

//画图片
void CopenglViewDlg::DrawFrame(int id,IplImage *image)
{	
	CBrush gray_brush(RGB(240,240,240));	
	CBrush *pOldBrush = NULL;

	CRect rect;//定义矩形类	
	CWnd *pWnd = GetDlgItem(id); //获得pictrue控件窗口的句柄   
	pWnd->GetClientRect(rect);			

	cvFlip(image);
	
	CDC *pBaseDC = pWnd->GetDC();
	CMemDC *pMemDC = new CMemDC(*pBaseDC,pWnd);
	CDC *pDc = &(pMemDC->GetDC());

	pOldBrush = pDc->SelectObject(&gray_brush);	
	pDc->Rectangle(rect.left,rect.top,rect.right, rect.bottom); 	
	pDc->SelectObject(pOldBrush);

	rect.InflateRect(-1,-1);
	CRect drawRect = CalcDrawRect(rect,image);

	LPBITMAPINFO pBmi = CreateMapInfo(image,1);		
	SetStretchBltMode(pDc->m_hDC,STRETCH_HALFTONE); 
	StretchDIBits(pDc->m_hDC,
			drawRect.left,drawRect.top,drawRect.Width(),drawRect.Height(),
			0,0,image->width,image->height,
			image->imageData,pBmi,DIB_RGB_COLORS,SRCCOPY);			
	
	pWnd->ReleaseDC(pDc);
	free(pBmi);

	cvFlip(image);

	delete pMemDC;
	pWnd->ReleaseDC(pBaseDC);	
}

void CopenglViewDlg::OnCbnSelchangeCombo1()
{
	// 探测方式

	//获得指定序号的文本，序号由GetCurSel()获得用户当前选定的项序号
//	int nIndex = m_cb1.GetCurSel();
//	m_cb1.GetLBText(nIndex, str);
	m_cb1.GetLBText(m_cb1.GetCurSel(), str1);
//	MessageBox(str);
	if (str1 == "------红外------"){
		// 红外模式

		Rader = false;      //关闭雷达模式
		reverse_color = false;   //关闭颜色反转
		tv = false;        //关闭TV模式
		fire = true;        //尾焰显示
		Inf = true;         //红外模式开启
		m_TraceSort.SetWindowTextA("红外");
		m_cb6.ResetContent();
		m_cb6.AddString("-----跟踪视场设置-----");
		m_cb6.AddString("----5.6*4.2IR----");
		m_cb6.AddString("----7.8*5.85IR----");
		m_cb6.SetCurSel(0);
	}

	//if (str1 == "------雷达------"){
	//	// TODO:  rader

	//	Rader = true;
	//	reverse_color = true;
	//	fire = false;
	//	Inf = false;
	//	tv = false;
	//	m_TraceSort.SetWindowTextA("雷达");
	//}

	if (str1 == "------TV------"){
		// TV
		tv = true;          //开启TV模式
		reverse_color = true;      //颜色反转
		fire = false;        //关闭尾焰
		Inf = false;         //关闭红外模式
		Rader = false;
		m_TraceSort.SetWindowTextA("TV");
		m_cb6.ResetContent();
		m_cb6.AddString("-----跟踪视场设置-----");
		m_cb6.AddString("----2.4*1.8TV----");
		m_cb6.AddString("----5.6*4.2TV----");
		m_cb6.SetCurSel(0);
	}

}


void CopenglViewDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CopenglViewDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	stop = true;

	UpdateData(FALSE);
}


void CopenglViewDlg::OnBnClickedButton3()
{

}





void CopenglViewDlg::OnBnClickedButton4()
{
	// 镜头放大2x
	UpdateData(TRUE);
	Vn = 0;
	Vn += 2.0;
	UpdateData(FALSE);
}


void CopenglViewDlg::OnBnClickedButton5()
{
	// IR
	UpdateData(TRUE);
	if ((m_IRorTV>=2.4)&&(m_IRorTV<=10)){
		scalea = 5 * (2.4 / m_IRorTV);
		scaleb = 4 * (2.4 / m_IRorTV);
		Vt = 4;
		k = TransferPixel(m_IRorTV);
		Rader = false;      //关闭雷达模式
		reverse_color = false;   //关闭颜色反转
		tv = false;        //关闭TV模式
		fire = true;        //尾焰显示
		Inf = true;         //红外模式开启
		m_TraceSort.SetWindowTextA("红外");
		m_cb6.ResetContent();
		m_cb6.AddString("-----跟踪视场设置-----");
		m_cb6.AddString("----5.6*4.2IR----");
		m_cb6.AddString("----7.8*5.85IR----");
		m_cb6.SetCurSel(0);
	}
	UpdateData(FALSE);

}


void CopenglViewDlg::OnBnClickedButton7()
{
	// 8X
	UpdateData(TRUE);
	Vn = 0;
	Vn += 8.0;
	UpdateData(FALSE);
}


void CopenglViewDlg::OnBnClickedButton6()
{
	//TV
	UpdateData(TRUE);
	if ((m_IRorTV >= 2.4)&&(m_IRorTV <= 10)){
		scalea = 5 * (2.4 / m_IRorTV);
		scaleb = 4 * (2.4 / m_IRorTV);
		Vt = 4;
		k = TransferPixel(m_IRorTV);
		tv = true;          //开启TV模式
		reverse_color = true;      //颜色反转
		fire = false;        //关闭尾焰
		Inf = false;         //关闭红外模式
		Rader = false;
		m_TraceSort.SetWindowTextA("TV");
		m_cb6.ResetContent();
		m_cb6.AddString("-----跟踪视场设置-----");
		m_cb6.AddString("----2.4*1.8TV----");
		m_cb6.AddString("----5.6*4.2TV----");
		m_cb6.SetCurSel(0);
	}
	UpdateData(FALSE);
}


void CopenglViewDlg::OnBnClickedButton8()
{
	// missile
	UpdateData(TRUE);
	missile = true;
	f22 = false;
	UpdateData(FALSE);
}


void CopenglViewDlg::OnBnClickedButton9()
{
	// F22
	UpdateData(TRUE);
	missile = false;
	f22 = true;
	UpdateData(FALSE);
}


CString str3;
void CopenglViewDlg::OnCbnSelchangeCombo3()
{
	// 目标选择


	m_cb3.GetLBText(m_cb3.GetCurSel(), str3);
	if (str3 == "----固定翼飞机----"){

		missile = false;
		f22 = true;
		ball = false;
		Tgt1.SetWindowText(_T("固定翼飞机"));
	}
	if (str3 == "-----巡航导弹-----"){

		missile = true;
		ball = false;
		f22 = false;
		Tgt1.SetWindowText(_T("巡航导弹"));
	}
	if (str3 == "-----点目标-----"){
		ball = true;
		missile = false;
		f22 = false;
		Tgt1.SetWindowText(_T("点目标"));
	}

}



void CopenglViewDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	m_cb3.GetLBText(m_cb3.GetCurSel(), str3);
	if (str3 == "-----点目标-----"){
		Vn = m_dotRadius;
		dotColor = m_dotColor;
	}
	if (bgcolor_gray){
		bgColor = m_bgColor;
	}
	start_test = true;
	UpdateData(FALSE);
}

CString str4;
void CopenglViewDlg::OnCbnSelchangeCombo4()
{
	// 跟踪模式选择
	
	m_cb4.GetLBText(m_cb4.GetCurSel(), str4);
	if (str4 == "-----边缘跟踪-----"){
		UpdateData(TRUE);
		edge = true;
		contrast = false;
		minusing = false;
		sum = Sumtarget;
		model.SetWindowTextA("边缘跟踪");      //下方属性显示
		UpdateData(FALSE);
	}
	if (str4 == "----对比度跟踪----"){
		contrast = true;
		edge = false;
		minusing = false;
		model.SetWindowTextA("对比度跟踪");
	}
	if (str4 == "-----取差跟踪-----"){
		minusing = true;
		edge = false;
		contrast = false;

		model.SetWindowTextA("取差跟踪");
	}
	
}



CString str6;
void CopenglViewDlg::OnCbnSelchangeCombo6()
{
	// 跟踪视场
	m_cb6.GetLBText(m_cb6.GetCurSel(), str6);
	if (str6 == "----2.4*1.8TV----"){
		m_view.SetWindowTextA("2.4*1.8TV");
		scalea = 5;           //sum=4242;pixel=384
		scaleb = 4;
		Vt = 4;
		k = TransferPixel(2.4);
	}
	if (str6 == "----5.6*4.2TV----"){
		m_view.SetWindowTextA("5.6*4.2TV");
		scalea = 2.14;   //sum=1364; pixel=165 正好是3/7的关系
		scaleb = 1.71;
		Vt = 4;
		k = TransferPixel(5.6);
	}
	if (str6 == "----5.6*4.2IR----"){
		m_view.SetWindowTextA("5.6*4.2IR");
		scalea = 2.14;   //sum=1364; pixel=165 
		scaleb = 1.71;
		Vt = 4;
		k = TransferPixel(5.6);
	}
	if (str6 == "----7.8*5.85IR----"){
		m_view.SetWindowTextA("7.8*5.85IR");
		scalea = 1.53;    //5/3.25  sum=930; pixel=117 
		scaleb = 1.23;    
		Vt = 4;
		k = TransferPixel(7.8);
	}
}



CString str8;
void CopenglViewDlg::OnCbnSelchangeCombo8()
{
	//video
	m_cb8.GetLBText(m_cb8.GetCurSel(), str8);
	if (str8 == "-----录制视频-----"){
		vdo = true;
	
	}
	//默认录制
	if (str8 == "-----读取视频-----"){
		vdo = false;  //读取时不再继续存视频
			CvCapture* capture = NULL;
			IplImage* frame;
			char c;
			cvNamedWindow("Example2", CV_WINDOW_AUTOSIZE);
			capture = cvCreateFileCapture("video.avi");
			while (1) {
				frame = cvQueryFrame(capture);
				if (!frame) break;
				cvShowImage("Example2", frame);
				c = cvWaitKey(33);
				if (c == 27) break;
			
			}
	}
}





//读取态势文件
void CopenglViewDlg::OnBnClickedXml()
{
	//UpdateData(TRUE);
	//CString tmp4,tmp5,tmp6;
	//GetDlgItemText (IDC_EDIT1,tmp);
	//tmp = tmp+"\r\n"+"读取态势文件";
	//SetDlgItemText (IDC_EDIT1,tmp);
	//
	//string filenameXML = "态势.xml";
	//ReadXmlFile(filenameXML);
	//指挥车信息
	//tmp1.Format("%.3f",com_searchDistance);
	//tmp2.Format("%.3f",com_searchAccuracy);
	//tmp3.Format("%.3f",com_searchPeriod);
	//tmp4.Format("%.3f",com_x);
	//tmp5.Format("%.3f",com_y);
	//tmp6.Format("%.3f",com_z);
	//SetDlgItemText (IDC_EDIT9,tmp1);
	//SetDlgItemText (IDC_EDIT10,tmp2);
	//SetDlgItemText (IDC_EDIT11,tmp3);

	//SetDlgItemText (IDC_EDIT9,tmp4);
	//SetDlgItemText (IDC_EDIT10,tmp5);
	//SetDlgItemText (IDC_EDIT11,tmp6);

	//m_position_x.SetWindowText(tmp4);
	//m_position_y.SetWindowText(tmp5);
	//m_position_z.SetWindowText(tmp6);
	//UpdateData(FALSE);
}


//初始化Socket
BOOL CopenglViewDlg::InitSocketRecv()
{
	m_socketRecv = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == m_socketRecv)
	{
		MessageBox("接收端套接字创建失败！");
		return FALSE;
	}

	SOCKADDR_IN addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(hostport);
	addrSock.sin_addr.S_un.S_addr = inet_addr(hostname);//htonl(INADDR_ANY);

	int retval;
	retval = bind(m_socketRecv, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == retval)
	{
		closesocket(m_socketRecv);
		MessageBox("绑定失败！");
		return FALSE;
	}

	return TRUE;
}
BOOL CopenglViewDlg::InitSocketSend()
{
	//初始化总控socket
	m_socketSend_cont = socket(AF_INET, SOCK_DGRAM, 0);//建立UDP socket
	if (m_socketSend_cont == 0)
	{
		MessageBox("与总控通信套接字创建失败！");
		return FALSE;//如果建立socket失败，返回FALSE
	}

	memset(&addr_cont, 0, sizeof(addr_cont));
	addr_cont.sin_family = AF_INET;
	addr_cont.sin_port = htons(genConPort);		   //指定port为要连接的端口号
	addr_cont.sin_addr.s_addr = inet_addr(ServerIP);//指定hostname为要连接的IP地址


	//初始化指挥车socket
	m_socketSend_comm = socket(AF_INET, SOCK_DGRAM, 0);//建立UDP socket
	if (m_socketSend_comm == 0)
	{
		MessageBox("与指挥车通信套接字创建失败！");
		return FALSE;//如果建立socket失败，返回FALSE
	}

	memset(&addr_comm, 0, sizeof(addr_comm));
	addr_comm.sin_family = AF_INET;
	addr_comm.sin_port = htons(commandPort);		   //指定port为要连接的端口号
	addr_comm.sin_addr.s_addr = inet_addr(commandIP);//指定hostname为要连接的IP地址

	//初始化导弹socket
	m_socketSend_miss = socket(AF_INET, SOCK_DGRAM, 0);//建立UDP socket
	if (m_socketSend_miss == 0)
	{
		MessageBox("与导弹通信套接字创建失败！");
		return FALSE;//如果建立socket失败，返回FALSE
	}

	memset(&addr_miss, 0, sizeof(addr_miss));
	addr_miss.sin_family = AF_INET;
	addr_miss.sin_port = htons(misslePort);		   //指定port为要连接的端口号
	addr_miss.sin_addr.s_addr = inet_addr(missleIP);//指定hostname为要连接的IP地址

	//初始化显示socket
	m_socketSend_show = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socketSend_show == 0)
	{
		MessageBox("与显示模块通信套接字创建失败！");
		return FALSE;//如果建立socket失败，返回FALSE
	}

	memset(&addr_show, 0, sizeof(addr_show));
	addr_show.sin_family = AF_INET;
	addr_show.sin_port = htons(showPort);		   //指定port为要连接的端口号
	addr_show.sin_addr.s_addr = inet_addr(showIP);//指定hostname为要连接的IP地址

	return TRUE;
}

DWORD CALLBACK CopenglViewDlg::RecvProc(LPVOID lpParameter)
{
	//接收参数
	SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	CopenglViewDlg *pThis = ((RECVPARAM*)lpParameter)->pThis;

	/////////////////////////////局部变量/////////////////////////////////////	
	gun2AirDefMis g2AD;
	SOCKADDR_IN addrSock2;					//用来从网络的广播地址上接收数据
	int len = sizeof(SOCKADDR);
	char recvBuf[BUFSIZE];					//建立用于接收数据的buffer
	memset(recvBuf, 0, sizeof(recvBuf));

	Message *recvDataFromCom;				//定义接收从指挥车传送过来的而数据	
	Command *recvCommand;					//接收总控指令		
	Command feedBackCommand;				//反馈指令
	int TypeTransferLen = sizeof(TypeTransfer);
	TypeTransfer *recvData = NULL;				//通信接收buffer

	int time_Temp = 0;
	TargetStatus *ts;

	Gun2Control g2c;
	g2c.messageType = GUN2CONTROLMESSAGE;
	g2c.gunNum = GUNVEHICLE_1;
	g2c.framefinish = ANS_FRAMEFINISH;
	/////////////////////////////////////////////////////////////////////////////////

	pThis->SetTimer(1, 20, NULL);    //周期20ms

	while (TRUE)
	{
		memset(recvBuf, 0, sizeof(recvBuf));
		int retval = recvfrom(sock, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrSock2, &len);
		recvData = (TypeTransfer *)recvBuf;

		//接收总控指令
		if (recvData->messageType == TESTCONTROLCOM)
		{
			recvCommand = (Command*)recvBuf;
			//系统自检
			if (recvCommand->commandCode == COM_SELFCHECK)
			{
#ifdef INSIDESIM
				sprintf(consoleData, "系统自检...\n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif				
				feedBackCommand.compOrTimeNum = GUNVEHICLE_1;
				feedBackCommand.messageType = TESTCONTROLCOM;
				feedBackCommand.commandCode = ANS_SELFCHECKSUS;
#ifdef INSIDESIM				
				Sleep(SLEEPTIME_1);
#endif
				sendto(m_socketSend_cont, (char*)&feedBackCommand, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));
#ifdef INSIDESIM			
				sprintf(consoleData, "自检完毕！\n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
			}
			//接收态势文件指令
			if (recvCommand->commandCode == COM_SENDFILESIT)
			{
				char *filename = "态势.xml";
				pThis->RecvXMLFileUDP(filename);//接收
				string filenameXML = filename;
				pThis->ReadXmlFile(filenameXML);//读取
			}
			//时间推进指令
			if (recvCommand->commandCode == COM_TESTSTART)
			{
				//(更新目标位置)

				//时间推进中每20ms发送一次
				pThis->TimeAdvance();
				//sendto(m_socketSend_cont, (char*)&feedBackCommand, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));

			}
			//实验结束
			if (recvCommand->commandCode == COM_TESTSTOP)
			{
				if (startOrNot == TRUE)
					startOrNot = FALSE;
#ifdef INSIDESIM
				sprintf(consoleData, "仿真结束..  \n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif				
				break;
			}
		}
	}

	if (pThis->gp != NULL)
	{
		free(pThis->gp);
		pThis->gp = NULL;
	}
	if (pThis->guntdp != NULL)
	{
		free(pThis->guntdp);
		pThis->guntdp = NULL;
	}
	if (pThis->guntdpFire != NULL)
	{
		free(pThis->guntdpFire);
	}
	if (pThis->guntdpFire1 != NULL)
	{
		free(pThis->guntdpFire1);
	}

	free(pThis->data_period);
	pThis->data_period = NULL;

	closesocket(sock);
	closesocket(m_socketSend_cont);
	WSACleanup();
	exit(0);
}
BOOL CopenglViewDlg::RecvXMLFileUDP(char *filename)
{
LP:	assert(strcmp(filename, "态势.xml") == 0);

	char *recvBuf = (char*)malloc(sizeof(SendFileNew));			//接收数据buffer
	memset(recvBuf, 0, sizeof(recvBuf));
	SendFileNew *fileRecv;

	FILE *fd = NULL;
	int len = sizeof(SOCKADDR);

	fd = fopen(filename, "wb");//以只写方式打开文件或者建立一个文件	
	if (fd == NULL)
	{
#ifdef INSIDESIM
		sprintf(consoleData, "打开文件出错！！！  \n");
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#else
		MessageBox("RecvXMLFileUDP 打开 态势.xml 文件出错！");
#endif
		return FALSE;
	}
	else
	{
#ifdef INSIDESIM
		sprintf(consoleData, "开始接收文件...  \n");
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
		while (1)
		{
			memset(recvBuf, 0, sizeof(SendFileNew));
			int retval = recvfrom(m_socketRecv, recvBuf, sizeof(SendFileNew), 0, (SOCKADDR*)&addrSock_broad, &len);

			//转换成本地结构体类型
			fileRecv = (SendFileNew *)recvBuf;

			//最后一包
			if (fileRecv->fileFrame == -1)
			{
				int buf_len = strlen(fileRecv->buf);
				fwrite(fileRecv->buf, 1, buf_len + 1, fd);//将从client端收到的内容写入文件

#ifdef INSIDESIM
				sprintf(consoleData, "文件传输完毕！！！  \n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITSUS;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//给总控返回接收文件成功信息
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));
				break;
			}
			if (retval <= 0) //如果client连接断开，代表文件传递完成，或者网络意外中断,循环break
			{
#ifdef INSIDESIM
				sprintf(consoleData, "接收文件出错！！！  \n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif				
				if (fd)
					fclose(fd);//关闭打开的文件

				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITFAIL;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//给总控返回接收文件出错信息
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));

				//返回函数开头
				goto LP;
			}
			else
			{
				fwrite(fileRecv->buf, 1, sizeof(fileRecv->buf), fd);//将从client端收到的内容写入文件

				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITSUS;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//给总控返回接收文件成功信息
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));
			}
		}

		if (fd)
			fclose(fd);//关闭打开的文件
	}

	free(recvBuf);
	return TRUE;
}

void CopenglViewDlg::UTF8ToGBK(char *&szOut)
{
	unsigned short *wszGBK;
	char *szGBK;
	//长度
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

	//长度
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//szOut = szGBK; //这样得到的szOut不正确，因为此句意义是将szGBK的首地址赋给szOut，当delete []szGBK执行后szGBK的内

	//存空间将被释放，此时将得不到szOut的内容

	memset(szOut, '/0', strlen(szGBK) + 1); //改将szGBK的内容赋给szOut ，这样即使szGBK被释放也能得到正确的值
	memcpy(szOut, szGBK, strlen(szGBK));

	delete[]szGBK;
	delete[]wszGBK;
}

bool CopenglViewDlg::ReadXmlFile(string& szFileName)
{
	if (index_readXML == 1)
	{
		return TRUE;
	}
	//读取Xml文件，并遍历
	try
	{
		//用文件路径创建一个XML的文档对象。
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		if (!myDocument->LoadFile())
		{
#ifdef INSIDESIM
			sprintf(consoleData, "加载态势文件出错！\n");
			WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#else
			MyMessageBox("加载态势文件出错！");
#endif
			return FALSE;
		}

		int index = 0;

		TiXmlElement *RootElement = myDocument->RootElement();				//获得根元素，即Persons。		
		TiXmlElement *FirstPerson = RootElement->FirstChildElement();		//获得第一个Person节点。
		TiXmlElement *nextPerson = FirstPerson;

		while (1)
		{
			char *str = const_cast<char*>(nextPerson->Value());
			UTF8ToGBK(str);
			memset(consoleData, 0, sizeof(consoleData));

			if (strncmp(str, "红方", 4) == 0)
			{
				nextPerson = nextPerson->FirstChildElement();				//获得红方下孩子节点
				char* nextPersonValue = const_cast<char*>(nextPerson->Value());
				UTF8ToGBK(nextPersonValue);
				while (1)
				{
					if (strncmp(nextPersonValue, "弹炮结合武器", 4) == 0)
					{
						nextPerson = nextPerson->FirstChildElement();
						nextPersonValue = const_cast<char*>(nextPerson->Value());
						UTF8ToGBK(nextPersonValue);

						while (1)
						{
							TiXmlAttribute *gunAttribute = nextPerson->FirstAttribute();		//获取ID

							if (strncmp(gunAttribute->Value(), GUNID1, 2) == 0)					//待修改
							{
								TiXmlElement *gunPerson = nextPerson->FirstChildElement();

								gunAttribute = gunAttribute->Next();							//名称
								// 								nextPersonValue = const_cast<char*>(gunAttribute->Value());
								// 								UTF8ToGBK(nextPersonValue);
								// 								sprintf(consoleData,"%s\n",nextPersonValue);
								// 								WriteConsole(hdlWrite, consoleData, strlen(consoleData)+1, NULL, NULL);

								gunAttribute = gunAttribute->Next();							//类型
								// 								nextPersonValue = const_cast<char*>(gunAttribute->Value());
								// 								UTF8ToGBK(nextPersonValue);
								// 								sprintf(consoleData,"%s\n",nextPersonValue);
								// 								WriteConsole(hdlWrite, consoleData, strlen(consoleData)+1, NULL, NULL);

								//获取炮车节点下的第一个子节点的属性,威力范围
								gunAttribute = gunAttribute->Next();							//x
								com_x = atof(gunAttribute->Value());
								gunAttribute = gunAttribute->Next();							//y
								com_y = atof(gunAttribute->Value());
								gunAttribute = gunAttribute->Next();							//z
								com_z = atof(gunAttribute->Value());
								CString tmp1, tmp2, tmp3;
								tmp1.Format("%.3f", com_x);
								tmp2.Format("%.3f", com_y);
								tmp3.Format("%.3f", com_z);
								SetDlgItemText (IDC_EDIT9,tmp1);
								SetDlgItemText (IDC_EDIT10,tmp2);
								SetDlgItemText (IDC_EDIT11,tmp3);
								//gunAttribute = gunPerson->FirstAttribute();						//1 车体横摇角
								//angleOfRoll = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//2 车体纵摇角
								//gunAttribute = gunPerson->FirstAttribute();
								//angleOfPitching = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//3 车体航向角
								//gunAttribute = gunPerson->FirstAttribute();
								//courseAngle = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//4 测量精度横摇角
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_angleOfRoll = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//5 测量精度纵摇角
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_angleOfPitching = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//6 测量精度航向角
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_courseAngle = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//7 激光回波周期
								//gunAttribute = gunPerson->FirstAttribute();
								//laserPeriod = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//8 搜索雷达威力范围
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_dis = atof(gunAttribute->Value()) * 1000;
								//detectionRange = searchRadar_dis;
								//gunPerson = gunPerson->NextSiblingElement();					//9 搜索雷达扫描周期
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_per = atof(gunAttribute->Value());
								//dxx = 2 * PI / (searchRadar_per * 1000 / 20);
								//gunPerson = gunPerson->NextSiblingElement();					//10 搜索雷达扫描精度
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_acc = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//11 搜索雷达目标容量
								//gunAttribute = gunPerson->FirstAttribute();
								//searchRadar_cap = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//12 火控跟踪雷达威力范围
								//gunAttribute = gunPerson->FirstAttribute();
								//trackRadar_distance = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//13 火控跟踪雷达跟踪精度
								//gunAttribute = gunPerson->FirstAttribute();
								//trackRadar_accuracy = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//14 光电跟踪电视跟踪视场
								//gunAttribute = gunPerson->FirstAttribute();
								//pe_TVTrackInspect = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//15 光电跟踪红外跟踪视场
								//gunAttribute = gunPerson->FirstAttribute();
								//pe_INTrackInspect = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//16 火炮射击火力范围 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireDis = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//17 火炮射击射频 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireFre = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//18 火炮射击射速 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireRate = atof(gunAttribute->Value());
								index_readXML = 1;
								//读取完所有的变量之后返回
								free(gunPerson);
								return true;
							}

							index++;

							nextPerson = nextPerson->NextSiblingElement();
							nextPersonValue = const_cast<char*>(nextPerson->Value());
							UTF8ToGBK(nextPersonValue);
						}
					}

					nextPerson = nextPerson->NextSiblingElement();
					nextPersonValue = const_cast<char*>(nextPerson->Value());
					UTF8ToGBK(nextPersonValue);
				}
			}

			nextPerson = nextPerson->NextSiblingElement();
		}

	}
	catch (string& e)
	{
		return false;
	}

	return false;
}




CString str9;
void CopenglViewDlg::OnCbnSelchangeCombo9()
{
	// TODO:  在此添加控件通知处理程序代码
	m_cb9.GetLBText(m_cb9.GetCurSel(), str9);
	if (str9 == "-----默认背景-----"){
		bgcolor_default = true;
		bgcolor_gray = false;
		bgcolor_black = false;
	}
	if (str9 == "-----灰色背景-----"){
		bgcolor_gray = true;
		bgcolor_default = false;
		bgcolor_black = false;
	}
	if (str9 == "-----黑色背景-----"){
		bgcolor_default = false;
		bgcolor_gray = false;
		bgcolor_black = true;
	}
}

void CopenglViewDlg::TimeAdvance(){
	if (t_num != 0)
	{
		for (int i = 0; i < TrackNum; i++)
		{
			if (index_targetDamage[i] == 1)
			{
				fire_ami[i][dotCountNow] = SINGLURVALUE;
				fire_ele[i][dotCountNow] = SINGLURVALUE;
				fire_dis[i][dotCountNow] = SINGLURVALUE;
			}
		}

		show.messageType = SHOWTYPE;
		show.at = fire_ami[t_num - 1][dotCountNow];
		show.et = fire_ele[t_num - 1][dotCountNow];
		show.dd = fire_dis[t_num - 1][dotCountNow];
		pSend = objectFire.MainWin(fire_ami, fire_ele, fire_dis, t_num, dotCountNow);
		//show.dd = pSend->egc;    ////发送dd_out
		int len = sendto(m_socketSend_show, (char*)&pSend->egc, sizeof(SENDTOSHOW), 0, (SOCKADDR*)&addr_show, sizeof(SOCKADDR));
		//		int len = sendto(m_socketSend_show, (char*)&show, sizeof(SENDTOSHOW), 0, (SOCKADDR*)&addr_show, sizeof(SOCKADDR));
		sprintf(consoleData, "AT: %.4f ET: %.4f DD: %.1f\n", show.at, show.et, show.dd);
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
		memset(&show, 0, sizeof(show));

	}
	if (NULL != pSend)
	{
		// 		double AT = pSend->agc;
		// 		double ET = pSend->ES;
		// 		double DD = pSend->egc;
		double AT = fire_ami[t_num - 1][dotCountNow];//当前点的位置信息
		double ET = fire_ele[t_num - 1][dotCountNow];
		double DD = fire_dis[t_num - 1][dotCountNow];
		//发送给主控
		sprintf(consoleData, "AT: %.2f ET: %.2f DD: %.2f dotCountNow : %d\n", AT, ET, DD, dotCountNow);
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
	}

	if (dotCountNow < file_dotNum - 1)
	{
		dotCountNow++;
	}
	//记录20ms周期次数
	if (second == 0)
	{
		if (period < file_dotNum / DOTNUM)     period++;
	}
	if (second < DOTNUM)
	{
		second++;
	}
	else
	{
		second = 0;
	}
}

float CopenglViewDlg::TransferPixel(float angle){
	return (angle*(3.1415926 / 180)) / 768;

}