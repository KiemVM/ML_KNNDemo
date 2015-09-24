
// KNNMDemoProject.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KNNMDemoProject.h"
#include "KNNMDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKNNMDemoProjectApp

BEGIN_MESSAGE_MAP(CKNNMDemoProjectApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKNNMDemoProjectApp construction

CKNNMDemoProjectApp::CKNNMDemoProjectApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CKNNMDemoProjectApp object

CKNNMDemoProjectApp theApp;


// CKNNMDemoProjectApp initialization

BOOL CKNNMDemoProjectApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CKNNMDemoProjectDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
