
// openglViewDlg.h : ͷ�ļ�
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
// CopenglViewDlg �Ի���

class CopenglViewDlg : public CDialogEx
{
// ����
public:
	CopenglViewDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OPENGLVIEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	//��Ӷ��߳�
	static DWORD CALLBACK RecvProc(LPVOID lpParameter);
	static char consoleData[1024];			//����̨buffer	
	static HANDLE hdlWrite;					//����̨���ھ��

	static struct sockaddr_in addr_cont;			//���ܿط��Ͷ˵�ַ
	static struct sockaddr_in addr_comm;			//��ָ�ӳ����Ͷ˵�ַ
	static struct sockaddr_in addr_miss;			//���������Ͷ˵�ַ
	static struct sockaddr_in addr_show;			//��ʾģ�鷢�Ͷ˵�ַ

	static SOCKET m_socketSend_cont;			//���ܿط�����socket
	static SOCKET m_socketSend_comm;			//��ָ�ӳ�������socket
	static SOCKET m_socketSend_miss;			//������������socket
	static SOCKET m_socketSend_show;			//����ʾģ�鷢������socket

	static BOOL startOrNot;
public:
	int TransferCoor(float Rx, float Ry);
	//double com_RangeChange;
	//double gun_RangeChange;
	double com_x;
	double com_y;
	double com_z;

public:
	//////////////////////////////������/////////////////////////////////////
	BOOL InitSocketRecv();
	BOOL InitSocketSend();
	SOCKET socket_create();
	SOCKET socket_accept(SOCKET listen_st);
	//void SendData2Com(int periodCom);
	void RecvTargetStatus(TargetStatus *);		//����Ŀ��״̬
	float TransferPixel(float angle);           //����->���ص�
	BOOL RecvXMLFileUDP(char *filename);		//����̬���ļ�UDPЭ��

	int hostport;					//���ն˿ں�
	int genConPort;					//�ܿض˿ں�
	int commandPort;				//ָ�ӳ��˿ں�
	int misslePort;					//�����˿�
	int showPort;					//��ʾģ��˿ں�

	const char* hostname;			//����IP
	const char* ServerIP;			//�ܿ�IP
	const char* missleIP;			//����IP
	const char* commandIP;			//ָ�ӳ�IP
	const char* showIP;				//��ʾģ��IP
	SOCKADDR_IN addrSock_broad;		//����������Ĺ㲥��ַ�Ͻ�������

	int tcpPort;					//TCP�ļ�����
	SOCKET m_socketRecv;			//���ն˿�
	void TimeAdvance();					//ʱ���ƽ�
	int t_num;						//�洢���յ���Ŀ����
	int dotCountNow;					//��ǰ���е��ĺ�������
	SendToShow show;
	////�������õ���ʱ�������ر���
	int periodSum;										//ģ����������
	int period;											//��������ģ��
	int count;											//��¼����ʱ��
	int second;											//��¼20ms���ڴ���
	//Ŀ�����
	double x_allot1;				//��ǰ��
	double y_allot1;
	double x_allot2;				//ǰһ��
	double y_allot2;
	int index_targetDamage[TrackNum];
	int index_readXML;				//�Ƿ������XML�ļ���ʶ
//	BOOL AnalysisFile(char *filename);
//	BOOL RecvFileTCP(char *filename);
	BOOL RecvFileUDP(char *filename);
	bool ReadXmlFile(string& szFileName);	//��ȡxml��ʽ�ļ�
	void UTF8ToGBK(char *&szOut);			//�ַ������ʽת������

	//��InitData�ж�ȡ���ı���
	int file_trackNum;
	int file_dotNum;
	//��XML�ļ���ȡ���ĸ��ֲ���
	double angleOfRoll;					//��ҡ��
	double angleOfPitching;				//��ҡ��
	double courseAngle;					//�����
	double surAcc_angleOfRoll;			//�������Ⱥ�ҡ��
	double surAcc_angleOfPitching;		//����������ҡ��
	double surAcc_courseAngle;			//�������Ⱥ����
	double laserPeriod;					//����ز�����
	double searchRadar_dis;				//�����״�������Χ
	double searchRadar_per;				//�����״�ɨ������ 
	double searchRadar_acc;				//�����״�ɨ�辫��
	double searchRadar_cap;				//�����״�Ŀ������
	double trackRadar_distance;			//��ظ����״�������Χ
	double trackRadar_accuracy;			//��ظ����״���پ���
	double pe_TVTrackInspect;			//�����ٵ��Ӹ����ӳ�
	double pe_INTrackInspect;			//�����ٺ�������ӳ�
	double gunFireDis;					//�������������Χ
	double gunFireFre;					//���������Ƶ
	double gunFireRate;					//�����������
	//���
	SendParam *pSend;					//����ýṹ�����
	TargetData objectFire;				//�����������
public:
	//�����������
	trackDataPolar* GunCoordinate(int numSum, gunPosition *gp, trackdata *InitData, trackDataPolar 	**guntdpFire, trackDataPolar **guntdpFire1);		//�����������
	int PolarToRec_Gun(trackDataPolar *tdpr);		//������תֱ������
	void GenerateData();						//������������
	trackDataPolar *guntdpFire1;				//�������ݽṹ������
	trackDataPolar **data_period;				//�������ڴ洢�������ݽṹ������
	trackDataPolar *guntdp;					//�������ݽṹ������
	trackDataPolar *guntdpFire;					//�������ݽṹ������
	gunPosition *gp;							//���ڵ���λ�ýṹ������

private:
	//�������ļ��ж�ȡ���ı���ֵ
	double com_searchDistance;			//��ָ�ӳ��״�������Χ
	double com_searchPeriod;			//��ָ�ӳ�ɨ������ֵ
	double com_searchAccuracy;			//��ָ�ӳ�ɨ�辫��
	double com_TargetCapacity;			//��ָ�ӳ�Ŀ������

	double gun_searchDistance;			//�ڳ������״�����
	double gun_searchPeriod;			//�ڳ������״�����

	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg void OnXML();//��ȡ̬���ļ�
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
	afx_msg void OnBnClickedXml();  //��ȡ̬���ļ�
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