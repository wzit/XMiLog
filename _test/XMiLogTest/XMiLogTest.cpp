#include "stdafx.h"
#include "XMiLogTest.h"
#include "XMiLogTestDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXMiLogTestApp theApp;


BEGIN_MESSAGE_MAP(CXMiLogTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CXMiLogTestApp::CXMiLogTestApp()
{
}


BOOL CXMiLogTestApp::InitInstance()
{
	InitCommonControls();
	CWinApp::InitInstance();
	CXMiLogTestDlg dlg;
	dlg.DoModal();
	return FALSE;
}
