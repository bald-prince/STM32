
// HelloStar.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHelloStarApp:
// See HelloStar.cpp for the implementation of this class
//

class CHelloStarApp : public CWinApp
{
public:
	CHelloStarApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHelloStarApp theApp;
