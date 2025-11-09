#pragma once
#include "afxdialogex.h"
#include "ImagePro_Kim_Ji_HyeonDoc.h"

// CFormulaResultDialog 대화 상자

class CFormulaResultDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFormulaResultDialog)

public:
	CFormulaResultDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFormulaResultDialog();
	
	void SetResult(const FormulaRecognitionResult& result);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMULA_RESULT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	FormulaRecognitionResult m_result;
	CTabCtrl m_tabCtrl;
	CEdit m_editOriginal;
	CEdit m_editAsciiMath;
	CEdit m_editLatex;
	CEdit m_editResult;
	CEdit m_editConfidence;
	CEdit m_editHTML;
	CEdit m_editJSON;
	
	void UpdateTextTab();
	void UpdateHTMLTab();
	void UpdateDataTab();
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabFormat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonCopy();
	afx_msg void OnBnClickedButtonSave();
};

