
// KNNMDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KNNMDemoProject.h"
#include "KNNMDemoDlg.h"
#include "OSFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void WriteToFile(LPCSTR szFormat, ...);

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


// CKNNMDemoProjectDlg dialog




CKNNMDemoProjectDlg::CKNNMDemoProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKNNMDemoProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bTraining = FALSE;
	m_bTest = FALSE;
}

void CKNNMDemoProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, TRAINING_SAMPLE_IDC_EDIT1, m_cEditTraining);
	DDX_Control(pDX, TEST_SAMPLE_IDC_EDIT3, m_cEditTest);
	DDX_Control(pDX, NO_TRAINING_IDC_EDIT4, m_cEditNoSampleTraining);
	DDX_Control(pDX, NO_TEST_IDC_EDIT5, m_cEditNoSampleTest);
	DDX_Control(pDX, IDC_EDIT6, m_cEditKNN);
}

BEGIN_MESSAGE_MAP(CKNNMDemoProjectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(BROWSE_TRAINING_IDC_BUTTON1, &CKNNMDemoProjectDlg::OnBnClickedTrainingIdcButton1)
	ON_BN_CLICKED(BROWSE_TEST_IDC_BUTTON3, &CKNNMDemoProjectDlg::OnBnClickedTestIdcButton3)
	ON_BN_CLICKED(START_TRAINING_IDC_BUTTON2, &CKNNMDemoProjectDlg::OnBnClickedTrainingIdcButton2)
	ON_BN_CLICKED(START_TEST_IDC_BUTTON4, &CKNNMDemoProjectDlg::OnBnClickedTestIdcButton4)
	ON_BN_CLICKED(EXIT_ID, &CKNNMDemoProjectDlg::OnBnClickedId)
	ON_BN_CLICKED(RESET_IDC_BUTTON5, &CKNNMDemoProjectDlg::OnBnClickedIdcButton5)
END_MESSAGE_MAP()


// CKNNMDemoProjectDlg message handlers

BOOL CKNNMDemoProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	ZeroMemory(&m_strProMax, sizeof(ProstateData));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKNNMDemoProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKNNMDemoProjectDlg::OnPaint()
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
HCURSOR CKNNMDemoProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKNNMDemoProjectDlg::OnBnClickedTrainingIdcButton1()
{
	TCHAR szFilter[] = TEXT ("CSV Files (*.CSV)\0*.csv\0")  \
		TEXT ("All Files (*.*)\0*.*\0\0");
	TCHAR szDefExtention[] = TEXT("txt\0");

	COSFDialog osfDlg;

	osfDlg.FileOpenDlg(szFilter, szDefExtention,TEXT("Select file)"),  TRUE);
	m_szFileTraining = osfDlg.GetFileName();
	m_cEditTraining.SetWindowText(m_szFileTraining);
	
}

void CKNNMDemoProjectDlg::OnBnClickedTestIdcButton3()
{
	TCHAR szFilter[] = TEXT ("CSV Files (*.CSV)\0*.csv\0")  \
		TEXT ("All Files (*.*)\0*.*\0\0");
	TCHAR szDefExtention[] = TEXT("txt\0");

	COSFDialog osfDlg;

	osfDlg.FileOpenDlg(szFilter, szDefExtention,TEXT("Select file)"),  TRUE);
	m_szFileTest = osfDlg.GetFileName();
	m_cEditTest.SetWindowText(m_szFileTest);
}

void CKNNMDemoProjectDlg::OnBnClickedTrainingIdcButton2()
{
	if (m_bTraining)
	{
		MessageBox("Please wait training finish!", "Training", MB_OK);
	}
	else
	{
		m_bTraining = TRUE;
		m_cEditNoSampleTraining.GetWindowText(m_szNumberDataTraining);
		SetDlgItemText(START_TRAINING_IDC_BUTTON2, _T("Stop"));
		Training();
		MessageBox("Training done!", "Training", MB_OK);
		SetDlgItemText(START_TRAINING_IDC_BUTTON2, _T("Start"));
		m_bTraining = FALSE;
		GetDlgItem(START_TRAINING_IDC_BUTTON2)->EnableWindow(FALSE);
	}
	
}

void CKNNMDemoProjectDlg::OnBnClickedTestIdcButton4()
{
	if (m_bTest)
	{
		MessageBox("Please wait test finish!", "Test", MB_OK);
	}
	else
	{
		m_bTest = TRUE;
		m_cEditNoSampleTraining.GetWindowText(m_szNumberDataTest);
		m_cEditKNN.GetWindowText(m_szNumberKNN);
		SetDlgItemText(START_TEST_IDC_BUTTON4, _T("Stop"));
		Test();
		MessageBox("Test done!", "Test", MB_OK);
		SetDlgItemText(START_TEST_IDC_BUTTON4, _T("Start"));
		m_bTest = FALSE;
		GetDlgItem(START_TEST_IDC_BUTTON4)->EnableWindow(FALSE);
	}
}

void CKNNMDemoProjectDlg::OnBnClickedId()
{
	CDialog::OnCancel();
}

void CKNNMDemoProjectDlg::OnBnClickedIdcButton5()
{
	if (m_bTest || m_bTraining)
	{
		MessageBox("Please wait process data finsih!", "Reset", MB_OK);
		return;
	}
	m_cEditTest.SetWindowText("");
	m_cEditTraining.SetWindowText("");
	m_cEditNoSampleTest.SetWindowText("");
	m_cEditNoSampleTraining.SetWindowText("");
	m_bTest = FALSE;
	m_bTraining = TRUE;
	m_szFileTest = "";
	m_szFileTraining = "";
	m_szNumberDataTest = "";
	m_szNumberDataTraining = "";
	GetDlgItem(START_TRAINING_IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(START_TEST_IDC_BUTTON4)->EnableWindow(TRUE);
}

//Thực hiện nạp tất cả các dữ liệu vào danh sách, lưu lại các kết quả phân loại tương ứng.
BOOL CKNNMDemoProjectDlg::Training()
{
	BOOL bRet = TRUE;

	if (!ReadData(READ_TRAINING_DATA))
	{
		MessageBox("Co loi, vui long kiem tra lai du lieu", "Training", MB_OK);
	}
Exit_Training:
	return bRet;
}

// Thực hiện tính khoảng cách từ mỗi điểm cần test tới các điểm đã training.
// Lấy ra số KNN điểm có khoảng cách ngắn nhất tới điểm đang test.
// đếm số lượng điểm có khoảng 
BOOL CKNNMDemoProjectDlg::Test()
{
	BOOL bRet = TRUE;
	std::list<ProstateData>::iterator listTest;
	if (!ReadData(READ_TEST_DATA))
	{
		MessageBox("Co loi, vui long kiem tra lai du lieu", "Test", MB_OK);
	}

	WriteToFile("lcavol,lweight,age,lbph,svi,lcp,gleason,pgg45,lpsa");

	for(listTest = m_listDataTest.begin(); listTest != m_listDataTest.end(); ++listTest)
	{
		Calculator(*listTest);
	}
	
Exit_Test:
	return bRet;
}

BOOL CKNNMDemoProjectDlg::ReadData(DWORD dwOption)
{
#define INDEXLEN 20
	BOOL bRet = TRUE;
	CString szFileToRead;
	TCHAR	szIndex[INDEXLEN];
	int iNumberDataToread;
	TCHAR szLine[MAX_PATH];
	FILE *fp = NULL;
	ProstateData strData;
	char* posTemp;
	char * pos;

	if (dwOption == READ_TRAINING_DATA)
	{
		szFileToRead = m_szFileTraining;
		iNumberDataToread = atoi(m_szNumberDataTraining);
	}
	else
	{
		szFileToRead = m_szFileTest;
		iNumberDataToread = atoi(m_szNumberDataTest);
	}

	// Doc file de lay du lieu
	errno_t err = fopen_s(&fp, szFileToRead, "rt");
	if (err) 
	{
		bRet = FALSE;
		goto Exit_ReadFile;
	}

	while (!feof(fp) || !iNumberDataToread)
	{
		ZeroMemory(szLine, MAX_PATH);
		if (NULL == fgets(szLine, 512, fp))
			break;

		//Loai bo dau xuong dong
		while ( (_tcslen(szLine) > 0) &&
			((szLine[_tcslen(szLine) - 1] == 13) || 
			(szLine[_tcslen(szLine) - 1] == 10)))
			szLine[_tcslen(szLine) - 1] = 0;

		// chi doc du lieu - dong 1 ko chua du lieu
		if (_strnicmp(szLine, "lcavol", 6) == 0)
			continue; // next line

		// lcavol
		ZeroMemory(szIndex, INDEXLEN);
		pos = strchr(szLine, ',');
		strncpy(szIndex, szLine, pos - szLine);
		strData.fLcavol1 = atof(szIndex);
		if (abs(strData.fLcavol1) > m_strProMax.fLcavol1)
		{
			m_strProMax.fLcavol1 = abs(strData.fLcavol1);
		}

		// lweight
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.fLweight2 = atof(szIndex);
		if (abs(strData.fLweight2) > m_strProMax.fLweight2)
		{
			m_strProMax.fLweight2 = strData.fLweight2;
		}

		// age
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.iAge3 = atoi(szIndex);
		if (abs(strData.iAge3) > m_strProMax.iAge3)
		{
			m_strProMax.iAge3 = strData.iAge3;
		}

		// lbph
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.fLbph4 = atof(szIndex);
		if (abs(strData.fLbph4) > m_strProMax.fLbph4)
		{
			m_strProMax.fLbph4 = strData.fLbph4;
		}

		// svi
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.fLsvi5 = atof(szIndex);
		if (abs(strData.fLsvi5) > m_strProMax.fLsvi5)
		{
			m_strProMax.fLsvi5 = strData.fLsvi5;
		}

		// lcp
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.fLcp6 = atof(szIndex);
		if (abs(strData.fLcp6) > m_strProMax.fLcp6)
		{
			m_strProMax.fLcp6 = strData.fLcp6;
		}

		// gleason
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.fGleason7 = atof(szIndex);
		if (abs(strData.fGleason7) > m_strProMax.fGleason7)
		{
			m_strProMax.fGleason7 = strData.fGleason7;
		}

		// pgg45
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		pos = strchr(posTemp, ',');
		strncpy(szIndex, posTemp, pos - posTemp);
		strData.iPgg45_8 = atoi(szIndex);
		if (abs(strData.iPgg45_8) > m_strProMax.iPgg45_8)
		{
			m_strProMax.iPgg45_8 = strData.iPgg45_8;
		}

		// lpsa
		ZeroMemory(szIndex, INDEXLEN);
		posTemp = pos + 1;
		strncpy(szIndex, posTemp, szLine + _tcslen(szLine) - posTemp);
		strData.fLpsa9 = atof(szIndex);

		if (dwOption == READ_TRAINING_DATA)
		{
			m_listDataTraining.push_back(strData);
		}
		else
		{
			m_listDataTest.push_back(strData);
		}
	}

	fclose(fp);
Exit_ReadFile:
	return bRet;
}

BOOL CKNNMDemoProjectDlg::Calculator(ProstateData strProData)
{
	// Tinh khoang cach luu vao list.
	/* CACH THUC HIEN:
	1) lay tung phan tu trong list chinh thuc ra, tinh khoang cach.
	   Push phan tu do vao trong list Temp
    2) sau khi da lam nhu buoc 1 voi ta ca cac phan tu trong stack, tien hanh clean list chinh thuc.
	   Lay tung phan tu trong list Temp push lai vao list chinh thuc.
    3) trong qua trinh tinh toan co the luu lai danh sach vi tri cac nut ma co khoang cach ngan nhat.
	* cach tinh khoang cach:
	d(x,z) = 
	*/
	BOOL bRet = TRUE;
	//std::list<ProstateData> listTraining;
	std::list<ProstateData>::iterator listA;
	std::list<ProstateData>::iterator listB;
	ProstateData strTemp, strTemp2;
	float fTongHeSoKhoangCachKNN = 0;
	float fTuSo = 0;
	float fAnpha = 0;

	for (listA =  m_listDataTraining.begin(); listA != m_listDataTraining.end(); ++listA)
	{
		listA->fKhoangCach = sqrt((strProData.fLcavol1 - listA->fLcavol1)*(strProData.fLcavol1 - listA->fLcavol1)/(m_strProMax.fLcavol1*m_strProMax.fLcavol1)
			+ (strProData.fLweight2 - listA->fLweight2)*(strProData.fLweight2 - listA->fLweight2)/(m_strProMax.fLweight2*m_strProMax.fLweight2) 
			+ (strProData.iAge3 - listA->iAge3)*(strProData.iAge3 - listA->iAge3)/(m_strProMax.iAge3*m_strProMax.iAge3)
			+ (strProData.fLbph4 - listA->fLbph4)*(strProData.fLbph4 - listA->fLbph4)/(m_strProMax.fLbph4*m_strProMax.fLbph4)
			+ (strProData.fLsvi5 - listA->fLsvi5)*(strProData.fLsvi5 - listA->fLsvi5)/(m_strProMax.fLsvi5*m_strProMax.fLsvi5)
			+ (strProData.fLcp6 - listA->fLcp6)*(strProData.fLcp6 - listA->fLcp6)/(m_strProMax.fLcp6*m_strProMax.fLcp6)
			+ (strProData.fGleason7 - listA->fGleason7)*(strProData.fGleason7 - listA->fGleason7)/(m_strProMax.fGleason7*m_strProMax.fGleason7)
			+ (strProData.iPgg45_8 - listA->iPgg45_8)*(strProData.iPgg45_8 - listA->iPgg45_8)/(m_strProMax.iPgg45_8*m_strProMax.iPgg45_8)
			); 
		strTemp = *listA;
		// Chọn KNN
		if (m_listKNN.size() < atoi(m_szNumberKNN))
		{
			m_listKNN.push_back(strTemp);
		}
		else
		{
			// thu hien loai bo phan tu co khoang cach lon nhat.
			for (listB = m_listKNN.begin(); listB != m_listKNN.end(); ++listB)
			{
				// neu phan tu vua tinh duoc gan diem z hon thi doi cho.
				if(strTemp.fKhoangCach < listB->fKhoangCach)
				{
					strTemp2 = strTemp;
					strTemp = *listB;
					*listB = strTemp2;
				}
			}
		}
	}

	// da co danh sach KNN.
	// Chon he so anpha bang bao nhieu?
	// tam thoi lay anpha = 0.
	fAnpha = 0;
	strProData.fLpsa9 = 0;
	m_bTrungBinhCong = FALSE;
	if (m_bTrungBinhCong)
	{
		for (listB = m_listKNN.begin(); listB != m_listKNN.end(); ++listB)
		{
			strProData.fLpsa9 = strProData.fLpsa9 + listB->fLpsa9/m_listKNN.size();
		}
	}
	else
	{
		for (listB = m_listKNN.begin(); listB != m_listKNN.end(); ++listB)
		{
			fTongHeSoKhoangCachKNN = fTongHeSoKhoangCachKNN + 1/(fAnpha + listB->fKhoangCach);
			fTuSo = fTuSo + (listB->fLpsa9)/(fAnpha + listB->fKhoangCach);
			/*strProData.fLpsa9 = strProData.fLpsa9 + listB->fLpsa9/m_listKNN.size();*/
		}
		strProData.fLpsa9 = fTuSo/fTongHeSoKhoangCachKNN;
	}

	WriteToFile("%f,%f,%d,%f,%f,%f,%f,%d,%f",
		strProData.fLcavol1,
		strProData.fLweight2,
		strProData.iAge3,
		strProData.fLbph4,
		strProData.fLsvi5,
		strProData.fLcp6,
		strProData.fGleason7,
		strProData.iPgg45_8,
		strProData.fLpsa9
		);

Exit_Cal:
	return bRet;
}

void WriteToFile(LPCSTR szFormat, ...)
{
	// Dump debug information to Debug Window
	char szBuffer[1024];
	char szPathLogFile[MAX_PATH];

	va_list ap;
	va_start(ap, szFormat);
	vsprintf_s(szBuffer, 1024, szFormat, ap);

	//write data to file
	strcpy_s(szPathLogFile,"TestResult.csv");
	FILE* pFile = fopen(szPathLogFile, "at");
	fprintf(pFile, "%s\n",szBuffer);
	fclose(pFile);

	va_end(ap);
}
