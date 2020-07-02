// SearchRadar.h : main header file for the SEARCHRADAR application
//

#if !defined(AFX_SEARCHRADAR_H__9BE534EF_F1DA_4009_A0EF_17DD06D23FB5__INCLUDED_)
#define AFX_SEARCHRADAR_H__9BE534EF_F1DA_4009_A0EF_17DD06D23FB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSearchRadarApp:
// See SearchRadar.cpp for the implementation of this class
//

class CSearchRadarApp : public CWinApp
{
public:
	CSearchRadarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchRadarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSearchRadarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHRADAR_H__9BE534EF_F1DA_4009_A0EF_17DD06D23FB5__INCLUDED_)
