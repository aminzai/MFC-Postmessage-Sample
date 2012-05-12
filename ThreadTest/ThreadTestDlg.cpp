// ThreadTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ThreadTest.h"
#include "ThreadTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CThreadTestDlg dialog




CThreadTestDlg::CThreadTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThreadTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_RUN, &CThreadTestDlg::OnBnClickedBtnRun)
    ON_MESSAGE( WM_POSTMESSAGE , &CThreadTestDlg::OnGetPostMessage)
END_MESSAGE_MAP()


// CThreadTestDlg message handlers

BOOL CThreadTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

    pBTN_Run    = (CButton *)GetDlgItem( IDC_BTN_RUN );
    pED_Run_1   = (CEdit *)GetDlgItem( IDC_ED_RUN_1 );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThreadTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CThreadTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT mthreadRunner( LPVOID lpvoid ){
    HWND tmpHWND = *( HWND *) lpvoid;

    CString tmpStr;

    for ( int i = 0 ; i < 100 ; i++ ){
        tmpStr.Format( _T("%d") , i );
        ::PostMessage( tmpHWND , WM_POSTMESSAGE , (WPARAM)&tmpStr, 0 );
        Sleep( 100 );
    }
    return 0;
}

void CThreadTestDlg::OnBnClickedBtnRun()
{
    CWinThread *pCWinThread;
    pED_Run_1->SetWindowText( _T("Hello") );
    
    HWND tmpHWND = this->m_hWnd;
    pCWinThread = AfxBeginThread( mthreadRunner, (LPVOID) &tmpHWND );
    
}

LRESULT CThreadTestDlg::OnGetPostMessage( WPARAM wparam , LPARAM lparam )
{
    UpdateData();
    CString tmpStr = *(CString *) wparam;
    pED_Run_1->SetWindowTextW( tmpStr );
    UpdateData();
    return 0;
}