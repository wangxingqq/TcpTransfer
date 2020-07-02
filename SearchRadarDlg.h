
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
	//���ھ�̬����������
public:
	//��Ӷ��߳�
	static DWORD CALLBACK RecvProc(LPVOID lpParameter);
	static BOOL startOrNot;

public:
	/////////////////////////OpenGl��ͼ�ú����ͱ���/////////////////////////////////////	
	BOOL SetWindowPixelFormat(HDC hDC);   //�趨���ظ�ʽ 
	BOOL CreateViewGLContext(HDC hDC);    //View GL Context 
	void RenderScene();                   //���Ƴ��� 
	void CSearchRadarDlg::TransferCoor( float Rx,float Ry, int A[2][3]);
	void drawString(const char* str);
	void selectFont(int size, int charset, const char* face);
	void drawCNString(const char* str);
	void RandomNumber1();					//���ڲ���һ���������
	void RandomNumber2();					//���ڲ��������������
	void DrawRandomNoise();					//���ڲ���һ���������
	void DrawSingleRandomNoise();			//���ڲ��������������
	HDC hrenderDC;							//DC 
	HGLRC hrenderRC;						//RC 
	CBrush brush;	
	int PixelFormat; 
	double dxx;								//���ڸ��ݲ�ͬ���ڼ���ɨ��ÿ���ԼӲ�ͬ�ĽǶ�
	double dx;								//ɨ��ת���Ļ���,��֤�����ʼ����ʱ���������в�ȵ���ֵ
	int noiseIndex;							//���������	
	double x[TrackNum];						//������ʾ��ת����
	double y[TrackNum];
	double z[TrackNum];
	double showDamageTarX[TrackNum];		//���ڵ�Ŀ�걻���ٺ󣬺�����־����ʾ
	double showDamageTarY[TrackNum];
	double com_RangeChange;
	double gun_RangeChange;
	double com_x;
	double com_y;
	double com_z;

public:
	//�йضԻ���
	CRect m_rect;

public:
	//////////////////////////////������/////////////////////////////////////
	//UDP
	SOCKADDR_IN addrSockBroadcast;						//����������Ĺ㲥��ַ�Ͻ�������
	SOCKET m_socketSend_gun;							//���ڳ���������socket
	SOCKET m_socketSend_cont;							//���ܿط�������socket
	SOCKET m_recvsocket;								//����socket	
	int tcpPort;										//TCP�˿ں�	
	int udpPort_gun;									//���ڳ�������UDP�˿ں�
	int udpPort_cont;									//���ܿط�����UDP�˿ں�
	int udpPort_recv;									//���ն˿�
	char serverIP[15];								//�ܿ�IP
	char hostIP[15];								//����IP
	char gun1_IP[15];								//�ڳ�IP��ַ
	char gun2_IP[15];
	char gun3_IP[15];
	char gun4_IP[15];
	char gun5_IP[15];
	char gun6_IP[15];
	//���ڳ���ַ
	struct sockaddr_in addrGunInform1;					//�����ڳ���ַ
	struct sockaddr_in addrGunInform2;
	struct sockaddr_in addrGunInform3;
	struct sockaddr_in addrGunInform4;
	struct sockaddr_in addrGunInform5;
	struct sockaddr_in addrGunInform6;
	//�ܿص�ַ
	struct sockaddr_in addrGeneralCon;					//���Ͷ˵�ַ

	BOOL InitSocketRecv();
	BOOL InitSocketSend();	
	BOOL LoadConfFile();
	BOOL SendData(int sendIndex,char *data,int dataLen);	//�������ݺ���	
	SOCKET socket_create();									//TCP�ļ�����
	SOCKET socket_accept(SOCKET listen_st);
	BOOL RecvFileTCP(char *filename);							//����Ŀ���ļ�TCPЭ��
	BOOL RecvFileUDP(char *filename);							//����Ŀ���ļ�UDPЭ��
	BOOL RecvXMLFileUDP(char *filename);						//����̬���ļ�UDPЭ��
	void RecvTargetStatus(TargetStatus *);					//����Ŀ��״̬
	void SendAllotNum(int gp_num,int *index_send,const char *gun_IP);				//����Ŀ���������
	void RecvGunSendFusionData(MESSAGE *);					//�����ڳ����͹������ں�����
	void SetaddrGunInform();								//���ø����ͻ��˵�ַ
	BOOL ReadXmlFile(string& szFileName);					//��ȡxml��ʽ�ļ�
	void UTF8ToGBK(char *&szOut);							//�ַ������ʽת������

public:
	//////////////////////////////////���ݽ���/////////////////////////////////
	int PreFusionData(trackdata* InitData,int period_set);						//���濪ʼǰ�������
	trackDataPolar* ComCoordinate(int numSum,trackdata* InitData,int period_set);					//ָ�ӳ��������
	trackDataPolar* GunCoordinate(int numSum,gunPosition *gp,trackdata* InitData);	//�����������
	BOOL AnalysisFIle(char *filename);							//�ļ�����	
	void JudgeThreatDegree();									//������ָ�ӳ�Ϊ����Ŀ����в���ж�
	int ThreatCal();											//Ŀ������ڻ�����в�ȼ���
	int targetAllot();											//Ŀ�����
	int UpdateAllotTarget(int gp_num,const char *gun_IP);		//Ŀ�걻���ٺ����·���Ŀ��	
	void TimeAdvance();											//ʱ���ƽ�

public:	
	//�������õ���ʱ�������ر���
	int periodSum;				//ģ����������
	int second;					//��¼20ms���ڴ���
	int times;					//��¼1s���ڴ�����-1Ϊ������dx > 2PIʱ��ʾ��ȷ�ĺ�������
	int period_set;				//ָ�ӳ�����
	int period;					//���������õ���ģ������
	int countMessageLoop;		//��������ʱ��������
	//Ŀ��������
	int t_num[dlgRadarNum_gun];					//Ŀ������Ŵ洢
	int index_send[dlgRadarNum_gun];			//��¼�Ƿ�����Ŀ�������
	BOOL index_updateTarget[dlgRadarNum_gun];	//�Ƿ�����Ŀ�����
	int index_targetDamage[TrackNum];			//Ŀ���ǹ����ݻ�����
	double ThreatDegree[dlgRadarNum_gun+1][TrackNum];	//�����������в��ֵ�����飬���һ����Ŀ����
	int allotNum[dlgRadarNum_gun+1][TrackNum];			//Ŀ����
	int threatIndex[TrackNum];							//�����в��������Ŀ����
	//�����ں�
	Fusion *fs;							//���������ں������
	trackDataPolar *comtdp;				//���ڽ���ָ�ӳ�����󺽼�����
	gunPosition *gp;					//������ڵ���λ������ṹ�����鲢��ʼ��
	trackDataPolarRec **data_period;	//��̬���ٰ����ڴ洢��������,һά��������
	//���ջ����������		
	int n_recvTrackData;			//�����ڳ��������ݱ�־	
	int t;							//���ƽ��յĻ���Ŀ�����ݵĸ���		
	//����̨
	char consoleData[1024];			//����̨buffer
	HANDLE hdlWrite;				//����̨���ھ��	
	int analyTarFileIndex;			//�Ƿ������Ŀ���ļ��ļ�������־
	int analyXMLFileIndex;			//�Ƿ������xml�ļ�������־
	int index_readXML;

private:
	//�������ļ��ж�ȡ���ı���ֵ
	double com_searchDistance;			//��ָ�ӳ��״�������Χ
	double com_searchPeriod;			//��ָ�ӳ�ɨ������ֵ
	double com_searchAccuracy;			//��ָ�ӳ�ɨ�辫��
	double com_TargetCapacity;			//��ָ�ӳ�Ŀ������

	double gun_searchDistance;			//�ڳ������״�����
	double gun_searchPeriod;			//�ڳ������״�����

	//��Ŀ���ļ��ж���������
	int file_trackNum;
	int file_trackNum1;
	int file_dotNum;
	/////////////��������ֵ��λ///////////////
	float R1x,R1y;
	float R2x,R2y;
	float R3x,R3y;
	float R4x,R4y;
	float R5x,R5y;
	float R6x,R6y;
	
	////////////�״ﷶΧԲ��ر���////////////
	float Range;
	float RangeSearch;
	
	float RangeScale1X,RangeScale1Y;
	float RangeScale2X,RangeScale2Y;
	float RangeScale3X,RangeScale3Y;
	float RangeScale4X,RangeScale4Y;
	float RangeScale5X,RangeScale5Y;
	float RangeScale6X,RangeScale6Y;

	//////////////���ڳ�λ��//////////////
	float RadarX[6],RadarY[6];

	float mNumberX;
	float mNumberY;
	float singleNumberX;
	float singleNumberY;
	float m1;								//���ڼ�¼��������
	float m2;								//���ڼ�¼��������

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
	afx_msg void OnTEST();//ϵͳ�Լ�
	afx_msg void OnXML();//��ȡ̬���ļ�
	afx_msg void OnDATA();//��ȡ�����ļ�
	afx_msg void OnSTART();//��ʼ
	afx_msg void OnWAIT();//��ͣ
	afx_msg void OnOUT();//�˳�
	afx_msg void OnPeriodSet();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnTargetNum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHRADARDLG_H__DB3CE701_558B_4A82_B30E_1BFF84C680DF__INCLUDED_)
