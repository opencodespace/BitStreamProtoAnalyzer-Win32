// BitStreamAnalyzerView.h : interface of the CBitStreamAnalyzerView class
//

/*
 *   Author: sealights@gmx.com
 *
 *   This file is licensed under the terms of the GNU General Public License version 3.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#define IDC_UPDATE_BUTTON_ID		1010
#define IDC_UPDATE_WATCH_BUTTON_ID	1020

#define MAX_BIT_STRING_SIZE	1024*2

class CBitStreamAnalyzerView : public CFormView
{

	// Defining my controls here
	CEdit	m_EdProtocolHdr;
	CEdit	m_EdStartPos;
	CEdit	m_EdEndPos;
	CEdit	m_EdSetValue;
	CEdit	m_EdBitWatchRules;
	CEdit	m_EdBitWatchValues;

	// Label 
	CEdit	m_LStartPosDisp;
	CEdit	m_LEndPosDisp;
	CEdit	m_LValueDisp;
	CEdit	m_LBitWatchRulesLabel;
	CEdit	m_LBitWatchValuesLabel;

	
	CButton	m_BtnUpdate;
	CButton	m_BtnUpdateWatch;

protected: // create from serialization only
	CBitStreamAnalyzerView();
	DECLARE_DYNCREATE(CBitStreamAnalyzerView)

public:
	enum{ IDD = IDD_BITSTREAMANALYZER_FORM };

// Attributes
public:
	CBitStreamAnalyzerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CBitStreamAnalyzerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	void OnUpdateButtonClick();

	void OnWatchUpdateButtonClick();
};

#ifndef _DEBUG  // debug version in BitStreamAnalyzerView.cpp
inline CBitStreamAnalyzerDoc* CBitStreamAnalyzerView::GetDocument() const
   { return reinterpret_cast<CBitStreamAnalyzerDoc*>(m_pDocument); }
#endif

