#pragma once
#include "afxdialogex.h"
#define PIXEL_BINARIZATION_H_RANGE	1
#define PIXEL_GAMMA_CORRECTION	2
#define PIXEL_BINARY	3
#define PIXEL_QUANTIZATION	4

// 전방 선언
class CImageProKimJiHyeonView;
class CImageProKimJiHyeonDoc;
class CMainFrame;

// CSlideerDialog 대화 상자

class CSlideerDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSlideerDialog)

public:
	CSlideerDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSlideerDialog();
	int num_of_sliders;
	int operation;
	float m_initial_pos1;
	float m_initial_pos2;
	float m_min1_val;
	float m_min2_val;
	float m_max1_val;
	float m_max2_val;
	char m_title1_text[256];
	char m_title2_text[256];
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	float m_current_post1_disp;

	virtual BOOL OnInitDialog();
	CSliderCtrl m_slider1;
	CSliderCtrl m_slider2;
	CStatic m_title1;
	CStatic m_title2;
	CStatic m_min1;
	CStatic m_min2;
	CStatic m_max1;
	CStatic m_max2;
	CEdit m_edit1;
	CEdit m_edit2;
	float m_current_pos1_disp;
	float m_current_pos2_disp;
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	void SetValue(char* title1, float min1, float max1, float initial_pos1, char* title2, float min2, float max2, float initial_pos2);
	void SetValue2(char* title1, float min1, float max1, float initial_pos1, char* title2, float min2, float max2, float initial_pos2);
};
