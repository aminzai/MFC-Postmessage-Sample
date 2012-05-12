// ThreadTestDlg.h : header file
//

#pragma once


#define WM_POSTMESSAGE          WM_USER+1


// CThreadTestDlg dialog
class CThreadTestDlg : public CDialog
{
// Construction
public:
	CThreadTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_THREADTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
    CButton *pBTN_Run;
    CEdit   *pED_Run_1;
public:
    UINT    threadRunner( LPVOID lpvoid );
    afx_msg LRESULT OnGetPostMessage( WPARAM wparam , LPARAM lparam );
    afx_msg void OnBnClickedBtnRun();
};
