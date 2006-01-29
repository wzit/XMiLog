#include "stdafx.h"
#include "XMiLogTest.h"
#include "XMiLogTestDlg.h"
#include ".\xmilogtestdlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CXMiLogTestDlg, CDialog)
   ON_BN_CLICKED(IDC_Echo, OnBnClickedEcho)
   ON_BN_CLICKED(IDC_Warn, OnBnClickedWarn)
   ON_BN_CLICKED(IDC_Fatal, OnBnClickedFatal)
   ON_BN_CLICKED(IDC_ShowText, OnBnClickedShowtext)
   ON_BN_CLICKED(IDC_ResetLog, OnBnClickedResetlog)
   ON_BN_CLICKED(IDC_ShowHTML, OnBnClickedShowhtml)
END_MESSAGE_MAP()


//************************************************************************************************
/// \brief utility function that change the focus and default control for a dialog
//************************************************************************************************
void dialogSetDefault(CDialog *window, int nID)
{
   window->SendDlgItemMessage(window->GetDefID(), BM_SETSTYLE, BS_PUSHBUTTON, (LPARAM)TRUE);   // Update the default push button's control ID.
   window->SendMessage(DM_SETDEFID, nID, 0L);   // Set the new style.
   window->SendDlgItemMessage(nID, BM_SETSTYLE, BS_DEFPUSHBUTTON, (LPARAM)TRUE);
}


//************************************************************************************************
/// \brief Constructor
//************************************************************************************************
CXMiLogTestDlg::CXMiLogTestDlg(CWnd* pParent)
	: CDialog(CXMiLogTestDlg::IDD, pParent)
{
}


//************************************************************************************************
/// \brief Dialog initialization callback
//************************************************************************************************
BOOL CXMiLogTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->CheckDlgButton(IDC_ShowType, BST_CHECKED);
	this->CheckDlgButton(IDC_ShowTime, BST_CHECKED);
   return TRUE;
}


//************************************************************************************************
/// \brief Echo button callback
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedEcho()
{
   CString s;
   this->GetDlgItemText(IDC_Edit,s);
   log_.echo(s.GetBuffer());
   this->SetDlgItemText(IDC_Edit, "");
   this->GetDlgItem(IDC_Edit)->SetFocus();
   dialogSetDefault(this, IDC_Echo);
}


//************************************************************************************************
/// \brief Warn button callback
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedWarn()
{
   CString s;
   this->GetDlgItemText(IDC_Edit,s);
   log_.warn(s.GetBuffer());
   this->SetDlgItemText(IDC_Edit, "");
   this->GetDlgItem(IDC_Edit)->SetFocus();
   dialogSetDefault(this, IDC_Warn);
}


//************************************************************************************************
/// \brief Fatal button callback
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedFatal()
{
   CString s;
   this->GetDlgItemText(IDC_Edit,s);
   log_.fatal(s.GetBuffer());
   this->SetDlgItemText(IDC_Edit, "");
   this->GetDlgItem(IDC_Edit)->SetFocus();
   dialogSetDefault(this, IDC_Fatal);
}


//************************************************************************************************
/// \brief Display the log in a message box
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedShowtext()
{
   CString s;
   this->GetDlgItemText(IDC_TitleEdit, s);
   s = s.Trim();
   AfxMessageBox(log_.getTextLog(!!this->IsDlgButtonChecked(IDC_ShowType),
                                 !!this->IsDlgButtonChecked(IDC_ShowTime),
                                 s.IsEmpty() ? 00 : s.GetBuffer()).c_str()
                , MB_OK);
}


//************************************************************************************************
/// \brief Display the log in a browser window
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedShowhtml()
{
   const char filePath[] = "log.html";
   FILE *fp;
   if (!(fp = fopen(filePath, "w")))
   {
      AfxMessageBox("Could not open HTML file for writing", MB_OK | MB_ICONERROR);
      return;
   }
   CString title;
   this->GetDlgItemText(IDC_TitleEdit, title);
   title = title.Trim();
   
   CString style;
   this->GetDlgItemText(IDC_StyleEdit, style);
   style = style.Trim();
   
   if (style.Trim().IsEmpty())
      fputs(log_.getHTMLLog(!!this->IsDlgButtonChecked(IDC_ShowType),
                           !!this->IsDlgButtonChecked(IDC_ShowTime), 
                           title.IsEmpty() ? 00 : title.GetBuffer()).c_str(), fp);
   else
      fputs(log_.getHTMLLog(style.GetBuffer(), !!this->IsDlgButtonChecked(IDC_ShowType),
                           !!this->IsDlgButtonChecked(IDC_ShowTime), 
                           title.IsEmpty() ? 00 : title.GetBuffer()).c_str(), fp);
   fclose(fp);
   if (ShellExecute(HWND(this), "open", filePath, 00, 00, SW_SHOWNORMAL) <= HINSTANCE(32))
   {
      AfxMessageBox("Unable to open HTML log document with. Your environment is probably "
                    "not configured to handle .html documents properly", MB_OK | MB_ICONERROR);
      return;
   }
}


//************************************************************************************************
/// \brief Reset the log
//************************************************************************************************
void CXMiLogTestDlg::OnBnClickedResetlog()
{
   log_.reset();
}

