
// openglView.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CopenglViewApp:
// �йش����ʵ�֣������ openglView.cpp
//

class CopenglViewApp : public CWinApp
{
public:
	CopenglViewApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CopenglViewApp theApp;