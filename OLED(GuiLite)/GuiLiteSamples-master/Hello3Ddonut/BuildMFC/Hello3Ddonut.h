
// Hello3Ddonut.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHello3DdonutApp:
// See Hello3Ddonut.cpp for the implementation of this class
//

class CHello3DdonutApp : public CWinApp
{
public:
	CHello3DdonutApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHello3DdonutApp theApp;
