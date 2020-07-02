
// openglViewDlg.cpp : ʵ���ļ�
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

//��Ŀ��Ҷ�
extern double dotColor;
//�����Ҷ�
extern double bgColor;
//������Ƶ�ʱ�ʶ
bool inf_mark = true; //ÿ��10��
float k;             //�������ص�ϵ��������/K�õ����ص�������������K
//ģʽ�л���������
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
// CopenglViewDlg �Ի���
//���
extern int Sumtarget;
//�ӳ�->Ŀ���С
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
	SOCKET sock;//�Ѵ������׽���
	HWND hwnd;//�Ի�����
	CopenglViewDlg *pThis;
}RecvParam;

double **fire_ami = NULL;						//���ڻ�ؽ��㷽λ������
double **fire_ele = NULL;						//���ڻ�ؽ���ߵͽ�����
double **fire_dis = NULL;						//���ڻ�ؽ����������

char CopenglViewDlg::consoleData[1024];				//����̨buffer	
HANDLE CopenglViewDlg::hdlWrite;						//����̨���ھ��
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
	
	////////////////////////������///////////////////////////////
	hostport = 6000;				//���ؽ��ն˿�
	commandPort = 6000;				//ָ�ӳ��˿ں�
	showPort = 6000;				//��ʾģ��˿ں�
	misslePort = 0;					//�����˿ں�
	t_num = 0;						//�������
#ifdef ENTIRETYSIM
	//���޸�
	hostname = "172.25.17.79";		//���ͻ���IP
	ServerIP = "172.25.17.79";		//�ܿ�IP
	commandIP = "172.25.17.79";	//ָ�ӳ�IP
	missleIP = "";					//����IP
	genConPort = 7002;				//�ܿض˿ں�
#else
	//���޸�
	hostname = "172.25.17.79";		//���ͻ���IP
	ServerIP = "172.25.17.79";		//�ܿ�IP
	commandIP = "172.25.17.79";	//ָ�ӳ�IP
	showIP = "172.25.17.98";
	missleIP = "";					//����IP
	genConPort = 6001;				//�ܿض˿ں�
#endif
	count = 0;
	period = -1;						//���������õ���ģ������	
	second = 0;
	index_readXML = 0;
	
	memset(consoleData, 0, sizeof(consoleData));

	gp = (gunPosition*)malloc(DLGRADARNUM_GUN * sizeof(gunPosition));
	guntdp = NULL;
	guntdpFire = NULL;
	guntdpFire1 = NULL;
	data_period = NULL;
	////////////////////////opengl��ر���//////////////////////////
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


// CopenglViewDlg ��Ϣ�������
BOOL CopenglViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

#ifdef INSIDESIM
	//��DOS����
	AllocConsole();
	hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE);
#endif	

	///////////////////////Socket��ʼ��//////////////////////////
	if (InitSocketSend() && InitSocketRecv())
	{

	}
	else
	{
		MessageBox(_T("socket��ʼ��ʧ�ܣ�"));
		//exit(EXIT_FAILURE);
	}

//#ifdef INSIDESIM
//	//��DOS����
//	AllocConsole();
//	hdlWrite = GetStdHandle(STD_OUTPUT_HANDLE);
//#endif

	///////////////////////���������߳�//////////////////////////
	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socketRecv;
	pRecvParam->hwnd = m_hWnd;
	pRecvParam->pThis = this;

	//���������߳�
	HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	CloseHandle(hThread);
	//InitSocketRecv();
	//InitSocketSend();



	//
//	CBitmapButton_1.LoadBitmaps(IDB_BITMAP1);   //������Ƭ  
//	CBitmapButton_1.SizeToContent();  //ʹ��ť��ӦͼƬ��С 
//	CBitmapButton_2.LoadBitmaps(IDB_BITMAP2);   //������Ƭ  
//	CBitmapButton_2.SizeToContent();  //ʹ��ť��ӦͼƬ��С 
	CBitmapButton_3.LoadBitmaps(IDB_BITMAP4);   //������Ƭ  
	CBitmapButton_3.SizeToContent();  //ʹ��ť��ӦͼƬ��С 
	//Ĭ��������ʾ
	//SetDlgItemText(IDC_EDIT1, "2.4��7.8");
	SetDlgItemText(IDC_EDIT2, "����");
	SetDlgItemText(IDC_EDIT3, "5.6*4.2IR");
	SetDlgItemText(IDC_EDIT4, "�Աȶȸ���");
	SetDlgItemText(IDC_EDIT5, "�̶���ɻ�");
	SetDlgItemText(IDC_EDIT16, "0");
	SetDlgItemText(IDC_EDIT17, "0");
	SetDlgItemText(IDC_EDIT18, "0");
	//̽�ⷽʽ cb1
	m_cb1.AddString("--Ŀ��̽�ⷽʽѡ��--");
	m_cb1.AddString("------����------");
	m_cb1.AddString("------TV------");
//	m_cb1.AddString("------�״�------");
	m_cb1.SetCurSel(0);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������		
	//�Ŵ��� cb2
	//m_cb2.AddString("-----�Ŵ���ѡ��-----");
	//m_cb2.AddString("����");
	//m_cb2.AddString("�ı�");
	//m_cb2.AddString("�˱�");
	//m_cb2.AddString("��ԭ");
	//m_cb2.SetCurSel(0);
	//Ŀ��
	m_cb3.AddString("-----Ŀ������ѡ��-----");
	m_cb3.AddString("----�̶���ɻ�----");
	m_cb3.AddString("-----Ѳ������-----");
	m_cb3.AddString("-----��Ŀ��-----");
	m_cb3.SetCurSel(0);
	//����ģʽѡ��
	m_cb4.AddString("-----����ģʽѡ��-----");
	m_cb4.AddString("-----��Ե����-----");
	m_cb4.AddString("----�Աȶȸ���----");
	m_cb4.AddString("-----ȡ�����-----");
	m_cb4.SetCurSel(0);
	////���������
	//m_cb5.AddString("--�������������--");
	//m_cb5.SetCurSel(0);
	//���ٲ�������
	m_cb6.AddString("-----�����ӳ�����-----");
		//m_cb6.AddString("----5.6*4.2IR----");
		//m_cb6.AddString("----7.8*5.85IR----");
		//m_cb6.AddString("----2.4*1.8TV----");
		//m_cb6.AddString("----5.6*4.2TV----");
	m_cb6.SetCurSel(0);
	////����ϵͳ����
	//m_cb7.AddString("--����ϵͳ��������--");
	//m_cb7.AddString("��λ");
	//m_cb7.AddString("�ߵ�");
	//m_cb7.SetCurSel(0);
	//��Ƶ��ȡ
	m_cb8.AddString("-----��Ƶ������-----");
	m_cb8.AddString("-----¼����Ƶ-----");
	m_cb8.AddString("-----��ȡ��Ƶ-----");
	m_cb8.SetCurSel(0);
	//BGCOLOR
	m_cb9.AddString("-----������ɫѡ��-----");
	m_cb9.AddString("-----Ĭ�ϱ���-----");
	m_cb9.AddString("-----��ɫ����-----");
	m_cb9.AddString("-----��ɫ����-----");
	m_cb9.SetCurSel(0);

	//MFC��ֲ
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_OPENGL_VIEW);	
	pWnd->GetWindowRect(&rc);
	pWnd->MoveWindow(rc.left,rc.top,792, 588);	
	pWnd->GetClientRect(&rc);
	pWnd->ShowWindow(FALSE);
		
	m_sceneWnd = pWnd->m_hWnd;	
	SceneInit(m_sceneWnd,&frame_image);
	SetTimer(101,10,NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CopenglViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CopenglViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopenglViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	SceneProc(m_sceneWnd,WM_TIMER,0,0);
	SceneProc(m_sceneWnd,WM_PAINT,0,0);

	CDialogEx::OnTimer(nIDEvent);
	DrawFrame(IDC_SCENE,frame_image);
	cvReleaseImage(&frame_image);
}

//����ͼ�����
CRect CopenglViewDlg::CalcDrawRect(CRect rect,IplImage *image)
{
	CRect drawRect;

	int width  = image->width;
	int height = image->height;	
	int x,y,w,h;		
	double scale = 1;
	if(width > rect.Width() || height > rect.Height()) //СͼƬ��������
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

//��ͼƬ
void CopenglViewDlg::DrawFrame(int id,IplImage *image)
{	
	CBrush gray_brush(RGB(240,240,240));	
	CBrush *pOldBrush = NULL;

	CRect rect;//���������	
	CWnd *pWnd = GetDlgItem(id); //���pictrue�ؼ����ڵľ��   
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
	// ̽�ⷽʽ

	//���ָ����ŵ��ı��������GetCurSel()����û���ǰѡ���������
//	int nIndex = m_cb1.GetCurSel();
//	m_cb1.GetLBText(nIndex, str);
	m_cb1.GetLBText(m_cb1.GetCurSel(), str1);
//	MessageBox(str);
	if (str1 == "------����------"){
		// ����ģʽ

		Rader = false;      //�ر��״�ģʽ
		reverse_color = false;   //�ر���ɫ��ת
		tv = false;        //�ر�TVģʽ
		fire = true;        //β����ʾ
		Inf = true;         //����ģʽ����
		m_TraceSort.SetWindowTextA("����");
		m_cb6.ResetContent();
		m_cb6.AddString("-----�����ӳ�����-----");
		m_cb6.AddString("----5.6*4.2IR----");
		m_cb6.AddString("----7.8*5.85IR----");
		m_cb6.SetCurSel(0);
	}

	//if (str1 == "------�״�------"){
	//	// TODO:  rader

	//	Rader = true;
	//	reverse_color = true;
	//	fire = false;
	//	Inf = false;
	//	tv = false;
	//	m_TraceSort.SetWindowTextA("�״�");
	//}

	if (str1 == "------TV------"){
		// TV
		tv = true;          //����TVģʽ
		reverse_color = true;      //��ɫ��ת
		fire = false;        //�ر�β��
		Inf = false;         //�رպ���ģʽ
		Rader = false;
		m_TraceSort.SetWindowTextA("TV");
		m_cb6.ResetContent();
		m_cb6.AddString("-----�����ӳ�����-----");
		m_cb6.AddString("----2.4*1.8TV----");
		m_cb6.AddString("----5.6*4.2TV----");
		m_cb6.SetCurSel(0);
	}

}


void CopenglViewDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// ��ͷ�Ŵ�2x
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
		Rader = false;      //�ر��״�ģʽ
		reverse_color = false;   //�ر���ɫ��ת
		tv = false;        //�ر�TVģʽ
		fire = true;        //β����ʾ
		Inf = true;         //����ģʽ����
		m_TraceSort.SetWindowTextA("����");
		m_cb6.ResetContent();
		m_cb6.AddString("-----�����ӳ�����-----");
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
		tv = true;          //����TVģʽ
		reverse_color = true;      //��ɫ��ת
		fire = false;        //�ر�β��
		Inf = false;         //�رպ���ģʽ
		Rader = false;
		m_TraceSort.SetWindowTextA("TV");
		m_cb6.ResetContent();
		m_cb6.AddString("-----�����ӳ�����-----");
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
	// Ŀ��ѡ��


	m_cb3.GetLBText(m_cb3.GetCurSel(), str3);
	if (str3 == "----�̶���ɻ�----"){

		missile = false;
		f22 = true;
		ball = false;
		Tgt1.SetWindowText(_T("�̶���ɻ�"));
	}
	if (str3 == "-----Ѳ������-----"){

		missile = true;
		ball = false;
		f22 = false;
		Tgt1.SetWindowText(_T("Ѳ������"));
	}
	if (str3 == "-----��Ŀ��-----"){
		ball = true;
		missile = false;
		f22 = false;
		Tgt1.SetWindowText(_T("��Ŀ��"));
	}

}



void CopenglViewDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	m_cb3.GetLBText(m_cb3.GetCurSel(), str3);
	if (str3 == "-----��Ŀ��-----"){
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
	// ����ģʽѡ��
	
	m_cb4.GetLBText(m_cb4.GetCurSel(), str4);
	if (str4 == "-----��Ե����-----"){
		UpdateData(TRUE);
		edge = true;
		contrast = false;
		minusing = false;
		sum = Sumtarget;
		model.SetWindowTextA("��Ե����");      //�·�������ʾ
		UpdateData(FALSE);
	}
	if (str4 == "----�Աȶȸ���----"){
		contrast = true;
		edge = false;
		minusing = false;
		model.SetWindowTextA("�Աȶȸ���");
	}
	if (str4 == "-----ȡ�����-----"){
		minusing = true;
		edge = false;
		contrast = false;

		model.SetWindowTextA("ȡ�����");
	}
	
}



CString str6;
void CopenglViewDlg::OnCbnSelchangeCombo6()
{
	// �����ӳ�
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
		scalea = 2.14;   //sum=1364; pixel=165 ������3/7�Ĺ�ϵ
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
	if (str8 == "-----¼����Ƶ-----"){
		vdo = true;
	
	}
	//Ĭ��¼��
	if (str8 == "-----��ȡ��Ƶ-----"){
		vdo = false;  //��ȡʱ���ټ�������Ƶ
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





//��ȡ̬���ļ�
void CopenglViewDlg::OnBnClickedXml()
{
	//UpdateData(TRUE);
	//CString tmp4,tmp5,tmp6;
	//GetDlgItemText (IDC_EDIT1,tmp);
	//tmp = tmp+"\r\n"+"��ȡ̬���ļ�";
	//SetDlgItemText (IDC_EDIT1,tmp);
	//
	//string filenameXML = "̬��.xml";
	//ReadXmlFile(filenameXML);
	//ָ�ӳ���Ϣ
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


//��ʼ��Socket
BOOL CopenglViewDlg::InitSocketRecv()
{
	m_socketRecv = socket(AF_INET, SOCK_DGRAM, 0);

	if (INVALID_SOCKET == m_socketRecv)
	{
		MessageBox("���ն��׽��ִ���ʧ�ܣ�");
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
		MessageBox("��ʧ�ܣ�");
		return FALSE;
	}

	return TRUE;
}
BOOL CopenglViewDlg::InitSocketSend()
{
	//��ʼ���ܿ�socket
	m_socketSend_cont = socket(AF_INET, SOCK_DGRAM, 0);//����UDP socket
	if (m_socketSend_cont == 0)
	{
		MessageBox("���ܿ�ͨ���׽��ִ���ʧ�ܣ�");
		return FALSE;//�������socketʧ�ܣ�����FALSE
	}

	memset(&addr_cont, 0, sizeof(addr_cont));
	addr_cont.sin_family = AF_INET;
	addr_cont.sin_port = htons(genConPort);		   //ָ��portΪҪ���ӵĶ˿ں�
	addr_cont.sin_addr.s_addr = inet_addr(ServerIP);//ָ��hostnameΪҪ���ӵ�IP��ַ


	//��ʼ��ָ�ӳ�socket
	m_socketSend_comm = socket(AF_INET, SOCK_DGRAM, 0);//����UDP socket
	if (m_socketSend_comm == 0)
	{
		MessageBox("��ָ�ӳ�ͨ���׽��ִ���ʧ�ܣ�");
		return FALSE;//�������socketʧ�ܣ�����FALSE
	}

	memset(&addr_comm, 0, sizeof(addr_comm));
	addr_comm.sin_family = AF_INET;
	addr_comm.sin_port = htons(commandPort);		   //ָ��portΪҪ���ӵĶ˿ں�
	addr_comm.sin_addr.s_addr = inet_addr(commandIP);//ָ��hostnameΪҪ���ӵ�IP��ַ

	//��ʼ������socket
	m_socketSend_miss = socket(AF_INET, SOCK_DGRAM, 0);//����UDP socket
	if (m_socketSend_miss == 0)
	{
		MessageBox("�뵼��ͨ���׽��ִ���ʧ�ܣ�");
		return FALSE;//�������socketʧ�ܣ�����FALSE
	}

	memset(&addr_miss, 0, sizeof(addr_miss));
	addr_miss.sin_family = AF_INET;
	addr_miss.sin_port = htons(misslePort);		   //ָ��portΪҪ���ӵĶ˿ں�
	addr_miss.sin_addr.s_addr = inet_addr(missleIP);//ָ��hostnameΪҪ���ӵ�IP��ַ

	//��ʼ����ʾsocket
	m_socketSend_show = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_socketSend_show == 0)
	{
		MessageBox("����ʾģ��ͨ���׽��ִ���ʧ�ܣ�");
		return FALSE;//�������socketʧ�ܣ�����FALSE
	}

	memset(&addr_show, 0, sizeof(addr_show));
	addr_show.sin_family = AF_INET;
	addr_show.sin_port = htons(showPort);		   //ָ��portΪҪ���ӵĶ˿ں�
	addr_show.sin_addr.s_addr = inet_addr(showIP);//ָ��hostnameΪҪ���ӵ�IP��ַ

	return TRUE;
}

DWORD CALLBACK CopenglViewDlg::RecvProc(LPVOID lpParameter)
{
	//���ղ���
	SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	CopenglViewDlg *pThis = ((RECVPARAM*)lpParameter)->pThis;

	/////////////////////////////�ֲ�����/////////////////////////////////////	
	gun2AirDefMis g2AD;
	SOCKADDR_IN addrSock2;					//����������Ĺ㲥��ַ�Ͻ�������
	int len = sizeof(SOCKADDR);
	char recvBuf[BUFSIZE];					//�������ڽ������ݵ�buffer
	memset(recvBuf, 0, sizeof(recvBuf));

	Message *recvDataFromCom;				//������մ�ָ�ӳ����͹����Ķ�����	
	Command *recvCommand;					//�����ܿ�ָ��		
	Command feedBackCommand;				//����ָ��
	int TypeTransferLen = sizeof(TypeTransfer);
	TypeTransfer *recvData = NULL;				//ͨ�Ž���buffer

	int time_Temp = 0;
	TargetStatus *ts;

	Gun2Control g2c;
	g2c.messageType = GUN2CONTROLMESSAGE;
	g2c.gunNum = GUNVEHICLE_1;
	g2c.framefinish = ANS_FRAMEFINISH;
	/////////////////////////////////////////////////////////////////////////////////

	pThis->SetTimer(1, 20, NULL);    //����20ms

	while (TRUE)
	{
		memset(recvBuf, 0, sizeof(recvBuf));
		int retval = recvfrom(sock, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrSock2, &len);
		recvData = (TypeTransfer *)recvBuf;

		//�����ܿ�ָ��
		if (recvData->messageType == TESTCONTROLCOM)
		{
			recvCommand = (Command*)recvBuf;
			//ϵͳ�Լ�
			if (recvCommand->commandCode == COM_SELFCHECK)
			{
#ifdef INSIDESIM
				sprintf(consoleData, "ϵͳ�Լ�...\n");
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
				sprintf(consoleData, "�Լ���ϣ�\n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
			}
			//����̬���ļ�ָ��
			if (recvCommand->commandCode == COM_SENDFILESIT)
			{
				char *filename = "̬��.xml";
				pThis->RecvXMLFileUDP(filename);//����
				string filenameXML = filename;
				pThis->ReadXmlFile(filenameXML);//��ȡ
			}
			//ʱ���ƽ�ָ��
			if (recvCommand->commandCode == COM_TESTSTART)
			{
				//(����Ŀ��λ��)

				//ʱ���ƽ���ÿ20ms����һ��
				pThis->TimeAdvance();
				//sendto(m_socketSend_cont, (char*)&feedBackCommand, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));

			}
			//ʵ�����
			if (recvCommand->commandCode == COM_TESTSTOP)
			{
				if (startOrNot == TRUE)
					startOrNot = FALSE;
#ifdef INSIDESIM
				sprintf(consoleData, "�������..  \n");
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
LP:	assert(strcmp(filename, "̬��.xml") == 0);

	char *recvBuf = (char*)malloc(sizeof(SendFileNew));			//��������buffer
	memset(recvBuf, 0, sizeof(recvBuf));
	SendFileNew *fileRecv;

	FILE *fd = NULL;
	int len = sizeof(SOCKADDR);

	fd = fopen(filename, "wb");//��ֻд��ʽ���ļ����߽���һ���ļ�	
	if (fd == NULL)
	{
#ifdef INSIDESIM
		sprintf(consoleData, "���ļ���������  \n");
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#else
		MessageBox("RecvXMLFileUDP �� ̬��.xml �ļ�����");
#endif
		return FALSE;
	}
	else
	{
#ifdef INSIDESIM
		sprintf(consoleData, "��ʼ�����ļ�...  \n");
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
		while (1)
		{
			memset(recvBuf, 0, sizeof(SendFileNew));
			int retval = recvfrom(m_socketRecv, recvBuf, sizeof(SendFileNew), 0, (SOCKADDR*)&addrSock_broad, &len);

			//ת���ɱ��ؽṹ������
			fileRecv = (SendFileNew *)recvBuf;

			//���һ��
			if (fileRecv->fileFrame == -1)
			{
				int buf_len = strlen(fileRecv->buf);
				fwrite(fileRecv->buf, 1, buf_len + 1, fd);//����client���յ�������д���ļ�

#ifdef INSIDESIM
				sprintf(consoleData, "�ļ�������ϣ�����  \n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif
				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITSUS;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//���ܿط��ؽ����ļ��ɹ���Ϣ
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));
				break;
			}
			if (retval <= 0) //���client���ӶϿ��������ļ�������ɣ��������������ж�,ѭ��break
			{
#ifdef INSIDESIM
				sprintf(consoleData, "�����ļ���������  \n");
				WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#endif				
				if (fd)
					fclose(fd);//�رմ򿪵��ļ�

				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITFAIL;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//���ܿط��ؽ����ļ�������Ϣ
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));

				//���غ�����ͷ
				goto LP;
			}
			else
			{
				fwrite(fileRecv->buf, 1, sizeof(fileRecv->buf), fd);//����client���յ�������д���ļ�

				Command commandSend;
				commandSend.messageType = TESTCONTROLCOM;
				commandSend.commandCode = ANS_RECVFILESITSUS;
				commandSend.compOrTimeNum = GUNVEHICLE_1;

				//���ܿط��ؽ����ļ��ɹ���Ϣ
				sendto(m_socketSend_cont, (char*)&commandSend, sizeof(Command), 0, (SOCKADDR*)&addr_cont, sizeof(SOCKADDR));
			}
		}

		if (fd)
			fclose(fd);//�رմ򿪵��ļ�
	}

	free(recvBuf);
	return TRUE;
}

void CopenglViewDlg::UTF8ToGBK(char *&szOut)
{
	unsigned short *wszGBK;
	char *szGBK;
	//����
	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGBK, len);

	//����
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//szOut = szGBK; //�����õ���szOut����ȷ����Ϊ�˾������ǽ�szGBK���׵�ַ����szOut����delete []szGBKִ�к�szGBK����

	//��ռ佫���ͷţ���ʱ���ò���szOut������

	memset(szOut, '/0', strlen(szGBK) + 1); //�Ľ�szGBK�����ݸ���szOut ��������ʹszGBK���ͷ�Ҳ�ܵõ���ȷ��ֵ
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
	//��ȡXml�ļ���������
	try
	{
		//���ļ�·������һ��XML���ĵ�����
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		if (!myDocument->LoadFile())
		{
#ifdef INSIDESIM
			sprintf(consoleData, "����̬���ļ�����\n");
			WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
#else
			MyMessageBox("����̬���ļ�����");
#endif
			return FALSE;
		}

		int index = 0;

		TiXmlElement *RootElement = myDocument->RootElement();				//��ø�Ԫ�أ���Persons��		
		TiXmlElement *FirstPerson = RootElement->FirstChildElement();		//��õ�һ��Person�ڵ㡣
		TiXmlElement *nextPerson = FirstPerson;

		while (1)
		{
			char *str = const_cast<char*>(nextPerson->Value());
			UTF8ToGBK(str);
			memset(consoleData, 0, sizeof(consoleData));

			if (strncmp(str, "�췽", 4) == 0)
			{
				nextPerson = nextPerson->FirstChildElement();				//��ú췽�º��ӽڵ�
				char* nextPersonValue = const_cast<char*>(nextPerson->Value());
				UTF8ToGBK(nextPersonValue);
				while (1)
				{
					if (strncmp(nextPersonValue, "���ڽ������", 4) == 0)
					{
						nextPerson = nextPerson->FirstChildElement();
						nextPersonValue = const_cast<char*>(nextPerson->Value());
						UTF8ToGBK(nextPersonValue);

						while (1)
						{
							TiXmlAttribute *gunAttribute = nextPerson->FirstAttribute();		//��ȡID

							if (strncmp(gunAttribute->Value(), GUNID1, 2) == 0)					//���޸�
							{
								TiXmlElement *gunPerson = nextPerson->FirstChildElement();

								gunAttribute = gunAttribute->Next();							//����
								// 								nextPersonValue = const_cast<char*>(gunAttribute->Value());
								// 								UTF8ToGBK(nextPersonValue);
								// 								sprintf(consoleData,"%s\n",nextPersonValue);
								// 								WriteConsole(hdlWrite, consoleData, strlen(consoleData)+1, NULL, NULL);

								gunAttribute = gunAttribute->Next();							//����
								// 								nextPersonValue = const_cast<char*>(gunAttribute->Value());
								// 								UTF8ToGBK(nextPersonValue);
								// 								sprintf(consoleData,"%s\n",nextPersonValue);
								// 								WriteConsole(hdlWrite, consoleData, strlen(consoleData)+1, NULL, NULL);

								//��ȡ�ڳ��ڵ��µĵ�һ���ӽڵ������,������Χ
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
								//gunAttribute = gunPerson->FirstAttribute();						//1 �����ҡ��
								//angleOfRoll = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//2 ������ҡ��
								//gunAttribute = gunPerson->FirstAttribute();
								//angleOfPitching = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//3 ���庽���
								//gunAttribute = gunPerson->FirstAttribute();
								//courseAngle = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//4 �������Ⱥ�ҡ��
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_angleOfRoll = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//5 ����������ҡ��
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_angleOfPitching = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//6 �������Ⱥ����
								//gunAttribute = gunPerson->FirstAttribute();
								//surAcc_courseAngle = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//7 ����ز�����
								//gunAttribute = gunPerson->FirstAttribute();
								//laserPeriod = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//8 �����״�������Χ
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_dis = atof(gunAttribute->Value()) * 1000;
								//detectionRange = searchRadar_dis;
								//gunPerson = gunPerson->NextSiblingElement();					//9 �����״�ɨ������
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_per = atof(gunAttribute->Value());
								//dxx = 2 * PI / (searchRadar_per * 1000 / 20);
								//gunPerson = gunPerson->NextSiblingElement();					//10 �����״�ɨ�辫��
								//gunAttribute = gunPerson->FirstAttribute();
								////								searchRadar_acc = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//11 �����״�Ŀ������
								//gunAttribute = gunPerson->FirstAttribute();
								//searchRadar_cap = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//12 ��ظ����״�������Χ
								//gunAttribute = gunPerson->FirstAttribute();
								//trackRadar_distance = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//13 ��ظ����״���پ���
								//gunAttribute = gunPerson->FirstAttribute();
								//trackRadar_accuracy = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//14 �����ٵ��Ӹ����ӳ�
								//gunAttribute = gunPerson->FirstAttribute();
								//pe_TVTrackInspect = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//15 �����ٺ�������ӳ�
								//gunAttribute = gunPerson->FirstAttribute();
								//pe_INTrackInspect = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//16 �������������Χ 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireDis = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//17 ���������Ƶ 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireFre = atof(gunAttribute->Value());
								//gunPerson = gunPerson->NextSiblingElement();					//18 ����������� 
								//gunAttribute = gunPerson->FirstAttribute();
								//gunFireRate = atof(gunAttribute->Value());
								index_readXML = 1;
								//��ȡ�����еı���֮�󷵻�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_cb9.GetLBText(m_cb9.GetCurSel(), str9);
	if (str9 == "-----Ĭ�ϱ���-----"){
		bgcolor_default = true;
		bgcolor_gray = false;
		bgcolor_black = false;
	}
	if (str9 == "-----��ɫ����-----"){
		bgcolor_gray = true;
		bgcolor_default = false;
		bgcolor_black = false;
	}
	if (str9 == "-----��ɫ����-----"){
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
		//show.dd = pSend->egc;    ////����dd_out
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
		double AT = fire_ami[t_num - 1][dotCountNow];//��ǰ���λ����Ϣ
		double ET = fire_ele[t_num - 1][dotCountNow];
		double DD = fire_dis[t_num - 1][dotCountNow];
		//���͸�����
		sprintf(consoleData, "AT: %.2f ET: %.2f DD: %.2f dotCountNow : %d\n", AT, ET, DD, dotCountNow);
		WriteConsole(hdlWrite, consoleData, strlen(consoleData) + 1, NULL, NULL);
	}

	if (dotCountNow < file_dotNum - 1)
	{
		dotCountNow++;
	}
	//��¼20ms���ڴ���
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