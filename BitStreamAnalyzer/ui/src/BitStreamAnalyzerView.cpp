// BitStreamAnalyzerView.cpp : implementation of the CBitStreamAnalyzerView class
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
#include "stdafx.h"
#include "BitStreamAnalyzer.h"

#include "BitStreamAnalyzerDoc.h"
#include "BitStreamAnalyzerView.h"
#include "bitstreamparser.h"
#include "bytetobitconversions.h"
#include "parserintf.h"
#include "hextodecimal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitStreamAnalyzerView

IMPLEMENT_DYNCREATE(CBitStreamAnalyzerView, CFormView)

BEGIN_MESSAGE_MAP(CBitStreamAnalyzerView, CFormView)

	ON_BN_CLICKED(IDC_UPDATE_BUTTON_ID, OnUpdateButtonClick)
	ON_BN_CLICKED(IDC_UPDATE_WATCH_BUTTON_ID, OnWatchUpdateButtonClick)

END_MESSAGE_MAP()

// CBitStreamAnalyzerView construction/destruction

CBitStreamAnalyzerView::CBitStreamAnalyzerView()
	: CFormView(CBitStreamAnalyzerView::IDD)
{
	// TODO: add construction code here

}

CBitStreamAnalyzerView::~CBitStreamAnalyzerView()
{
}

void CBitStreamAnalyzerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CBitStreamAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CBitStreamAnalyzerView::OnInitialUpdate()
{
	m_EdProtocolHdr.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(50, 100, 250, 180), this, 1001);

	//Start and end position edit boxes
	m_EdStartPos.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(350, 100, 370, 120), this, 1001);

	m_EdEndPos.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(400, 100, 420, 120), this, 1001);

	//Label
	m_LStartPosDisp.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED, CRect(350, 80, 370 + 20, 100), this, 1001);
	m_LStartPosDisp.SetWindowTextW(L"Start");

	m_LEndPosDisp.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED, CRect(400, 80, 420 + 20, 100), this, 1001);
	m_LEndPosDisp.SetWindowTextW(L"End");

	
	m_LValueDisp.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED, CRect(350, 150, 450, 170), this, 1001);
	m_LValueDisp.SetWindowTextW(L"Value in HEX");

	// Value
	m_EdSetValue.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(350, 170, 420, 190), this, 1001);

	// Button
	m_BtnUpdate.Create(L"Update", WS_CHILD | WS_VISIBLE,CRect(350, 200, 420, 220), this, IDC_UPDATE_BUTTON_ID);

	// Watch rules
	m_LBitWatchRulesLabel.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED, CRect(50, 220, 170, 240), this, 1001);
	m_LBitWatchRulesLabel.SetWindowTextW(L"Watch Rules");

	m_EdBitWatchRules.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(50, 250, 300, 270), this, 1001);

	// Watch values
	m_LBitWatchValuesLabel.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_DISABLED, CRect(50, 280, 170, 300), this, 1001);
	m_LBitWatchValuesLabel.SetWindowTextW(L"Values");

	m_EdBitWatchValues.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(50, 310, 300, 330), this, 1001);

	// Button
	m_BtnUpdateWatch.Create(L"Refresh", WS_CHILD | WS_VISIBLE,CRect(150, 340, 220, 360), this, IDC_UPDATE_WATCH_BUTTON_ID);

	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CBitStreamAnalyzerView::OnUpdateButtonClick()
{
	int nProtoHdrLen;
	int nLen;
	int nStartPos;
	int nEndPos;
	int nValue;

	char* pszBitCode			= NULL;
	char* pszUpdatedValInByte	= NULL;
	char szTemp[MAX_BIT_STRING_SIZE];
	TCHAR szWideTemp[MAX_BIT_STRING_SIZE];
	TCHAR szBitString[MAX_BIT_STRING_SIZE];

	memset(szBitString, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));
    //MessageBox( L"You clicked on me ");

	nProtoHdrLen = m_EdProtocolHdr.GetWindowTextLengthW();

	m_EdProtocolHdr.GetWindowTextW(szBitString, nProtoHdrLen + 1);

	USES_CONVERSION;

	pszBitCode = convertByteRepToBitRep(T2A(szBitString), nProtoHdrLen);

	// Get Start pos value

	memset(szWideTemp, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));

	nLen = m_EdStartPos.GetWindowTextLengthW();

	m_EdStartPos.GetWindowTextW(szWideTemp, nLen + 1);

	nStartPos =  atoi(T2A(szWideTemp));

	// Get End pos value

	memset(szWideTemp, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));

	nLen = m_EdEndPos.GetWindowTextLengthW();

	m_EdEndPos.GetWindowTextW(szWideTemp, nLen + 1);

	nEndPos =  atoi(T2A(szWideTemp));

	// Get value to be updated
	memset(szWideTemp, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));

	nLen = m_EdSetValue.GetWindowTextLengthW();

	m_EdSetValue.GetWindowTextW(szWideTemp, nLen + 1);

	nValue =  convertHexStringToDecimalValue(T2A(szWideTemp));

	strcpy_s(szTemp, T2A(szBitString));

	SetValue(pszBitCode, nStartPos, nEndPos, nValue);

	pszUpdatedValInByte = convertBitRepToByteRep(pszBitCode, nProtoHdrLen);

	m_EdProtocolHdr.SetWindowTextW(A2T(pszUpdatedValInByte));

	//MessageBox(szBitString);
}

void CBitStreamAnalyzerView::OnWatchUpdateButtonClick()
{
	int nRuleStringLen = 0;
	int nBitStreamLen = 0;
	TCHAR szBitString[MAX_BIT_STRING_SIZE];
	int* pPositon = NULL;
	int nNumOfPairs = -1;
	char* pszRuleStr = NULL;
	char* pszBitStream = NULL;
	char* pszHexValueStr = NULL;

	memset(szBitString, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));

	nRuleStringLen = m_EdBitWatchRules.GetWindowTextLengthW();
	m_EdBitWatchRules.GetWindowTextW(szBitString, nRuleStringLen + 1);

	USES_CONVERSION;
	
	pszRuleStr = T2A(szBitString);

	if(getPositionValues(pszRuleStr, nRuleStringLen, &pPositon, &nNumOfPairs) != 0)
	{
		MessageBox(L"Wrong rule format");

		return;
	}

	memset(szBitString, 0, MAX_BIT_STRING_SIZE*sizeof(TCHAR));

	nBitStreamLen = m_EdProtocolHdr.GetWindowTextLengthW();
	m_EdProtocolHdr.GetWindowTextW(szBitString, nBitStreamLen + 1);

	pszBitStream = T2A(szBitString);

	getHexValueStringFromBitStream(pszBitStream, 
									nBitStreamLen, 
									pPositon,
									nNumOfPairs,
									&pszHexValueStr);

	m_EdBitWatchValues.SetWindowTextW(A2T(pszHexValueStr));
}

// CBitStreamAnalyzerView diagnostics

#ifdef _DEBUG
void CBitStreamAnalyzerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBitStreamAnalyzerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CBitStreamAnalyzerDoc* CBitStreamAnalyzerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitStreamAnalyzerDoc)));
	return (CBitStreamAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitStreamAnalyzerView message handlers
