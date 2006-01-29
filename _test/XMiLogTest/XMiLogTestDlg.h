#pragma once


#include "XMiLog.h"


class CXMiLogTestDlg : public CDialog
{
public:
	enum { IDD = IDD_XMILOGTEST_DIALOG };
	CXMiLogTestDlg(CWnd* pParent = 00);
private:
   XMiLog log_;

   /// MFC stuff
private:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
   afx_msg void OnBnClickedEcho();
   afx_msg void OnBnClickedWarn();
   afx_msg void OnBnClickedFatal();
   afx_msg void OnBnClickedShowtext();
public:
   afx_msg void OnBnClickedResetlog();
   afx_msg void OnBnClickedShowhtml();
};
