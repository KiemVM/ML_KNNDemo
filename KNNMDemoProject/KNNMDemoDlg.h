
// KNNMDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "list"
#include "math.h"

#define	READ_TRAINING_DATA	0x01
#define READ_TEST_DATA		0x02

typedef struct ProstateData
{
	double	fLcavol1;
	double	fLweight2;
	int		iAge3;
	double	fLbph4;
	double	fLsvi5;
	double	fLcp6;
	double	fGleason7;
	int		iPgg45_8;
	double	fLpsa9;
	double	fKhoangCach;	// Khoang cach so voi diem can test.
}ProstateData;
// CKNNMDemoProjectDlg dialog
class CKNNMDemoProjectDlg : public CDialog
{
// Construction
public:
	CKNNMDemoProjectDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_KNNMDEMOPROJECT_DIALOG };

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
public:
	afx_msg void OnBnClickedTrainingIdcButton1();
	afx_msg void OnBnClickedTestIdcButton3();
	afx_msg void OnBnClickedTrainingIdcButton2();
	afx_msg void OnBnClickedTestIdcButton4();
	afx_msg void OnBnClickedId();
	afx_msg void OnBnClickedIdcButton5();

	BOOL ReadData(DWORD dwOption);
	BOOL Training();
	BOOL Test();
	BOOL Calculator(ProstateData straProData);

public:
	CString m_szFileTraining;
	CString m_szFileTest;
	CString m_szNumberDataTraining;
	CString m_szNumberDataTest;
	CString m_szNumberKNN;
	int		m_iNumberDataTraining;
	int		m_iNumberDataTest;
	int		m_iNumberKNN;
	CEdit m_cEditTraining;
	CEdit m_cEditTest;
	CEdit m_cEditNoSampleTraining;
	CEdit m_cEditNoSampleTest;
	BOOL  m_bTraining;
	BOOL  m_bTest;
	CEdit m_cEditKNN;
	BOOL  m_bTrungBinhCong;
	std::list<ProstateData> m_listDataTraining;
	std::list<ProstateData> m_listDataTest;
	std::list<ProstateData> m_listKNN;
	ProstateData m_strProMax;
};
