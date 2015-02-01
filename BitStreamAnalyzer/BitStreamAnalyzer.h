// BitStreamAnalyzer.h : main header file for the BitStreamAnalyzer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBitStreamAnalyzerApp:
// See BitStreamAnalyzer.cpp for the implementation of this class
//

class CBitStreamAnalyzerApp : public CWinApp
{
public:
	CBitStreamAnalyzerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBitStreamAnalyzerApp theApp;