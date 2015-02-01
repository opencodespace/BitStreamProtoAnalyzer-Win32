// BitStreamAnalyzerDoc.cpp : implementation of the CBitStreamAnalyzerDoc class
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitStreamAnalyzerDoc

IMPLEMENT_DYNCREATE(CBitStreamAnalyzerDoc, CDocument)

BEGIN_MESSAGE_MAP(CBitStreamAnalyzerDoc, CDocument)
END_MESSAGE_MAP()


// CBitStreamAnalyzerDoc construction/destruction

CBitStreamAnalyzerDoc::CBitStreamAnalyzerDoc()
{
	// TODO: add one-time construction code here

}

CBitStreamAnalyzerDoc::~CBitStreamAnalyzerDoc()
{
}

BOOL CBitStreamAnalyzerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CBitStreamAnalyzerDoc serialization

void CBitStreamAnalyzerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CBitStreamAnalyzerDoc diagnostics

#ifdef _DEBUG
void CBitStreamAnalyzerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBitStreamAnalyzerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBitStreamAnalyzerDoc commands
