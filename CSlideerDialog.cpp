// CSliderDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro_Kim_Ji_Hyeon.h"
#include "afxdialogex.h"
#include "CSlideerDialog.h"
#include "ImagePro_Kim_Ji_HyeonDoc.h"
#include "ImagePro_Kim_Ji_HyeonView.h"
#include "MainFrm.h"

// CSlideerDialog 대화 상자

IMPLEMENT_DYNAMIC(CSlideerDialog, CDialogEx)

CSlideerDialog::CSlideerDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	num_of_sliders = 1;
	operation = 0;
	m_initial_pos1 = 0.0f;
	m_initial_pos2 = 0.0f;
	m_min1_val = 0.0f;
	m_min2_val = 0.0f;
	m_max1_val = 255.0f;
	m_max2_val = 255.0f;
	m_current_pos1_disp = 0.0f;
	m_current_pos2_disp = 0.0f;
	strcpy_s(m_title1_text, "제목1");
	strcpy_s(m_title2_text, "제목2");
}

CSlideerDialog::~CSlideerDialog()
{
}

void CSlideerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider1);
	DDX_Control(pDX, IDC_SLIDER2, m_slider2);
	DDX_Control(pDX, IDC_TITLE1, m_title1);
	DDX_Control(pDX, IDC_TITLE2, m_title2);
	DDX_Control(pDX, IDC_MIN1, m_min1);
	DDX_Control(pDX, IDC_MAX1, m_max1);
	DDX_Control(pDX, IDC_MIN2, m_min2);
	DDX_Control(pDX, IDC_MAX2, m_max2);
	DDX_Text(pDX, IDC_EDIT1, m_current_pos1_disp);
	DDX_Text(pDX, IDC_EDIT2, m_current_pos2_disp);
}


BEGIN_MESSAGE_MAP(CSlideerDialog, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSlideerDialog::OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CSlideerDialog::OnCustomdrawSlider2)
END_MESSAGE_MAP()


// CSlideerDialog 메시지 처리기

BOOL CSlideerDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 슬라이더는 정수값으로 동작하므로 0에서 255까지 256개의 값을 입력 받는 
	// 것으로 설정
	// 실제로 입력 받을 데이터 범위가 A에서 B까지이면 이를 0에서 255로 매핑
	m_slider1.SetRange(0, 255);  // 범위 설정
	// 초기값 설정
	m_slider1.SetPos(static_cast<int>((m_initial_pos1 - m_min1_val) / (m_max1_val - m_min1_val) * 255));
	m_title1.SetWindowTextA(m_title1_text); // 제목1 값 설정
	char min1_text[256], max1_text[256];
	sprintf_s(min1_text, "%.2f", m_min1_val);
	sprintf_s(max1_text, "%.2f", m_max1_val);
	m_min1.SetWindowTextA(min1_text);  // 최소값1 설정
	m_max1.SetWindowTextA(max1_text); // 최대값1 설정

	// 슬라이더를 한 개만 사용하는 경우 2번 슬라이더를 숨김
	if (num_of_sliders == 1) {
		m_slider2.ShowWindow(0);   // 화면에 안나타나도록 설정
		m_title2.ShowWindow(0);
		m_edit2.ShowWindow(0);
		m_min2.ShowWindow(0);
		m_max2.ShowWindow(0);
	}
	else if (num_of_sliders == 2) {
		m_slider2.SetRange(0, 255); // 범위 설정
		// 초기값 설정
		m_slider2.SetPos(static_cast<int>((m_initial_pos2 - m_min2_val) / (m_max2_val - m_min2_val) * 255));

		m_title2.SetWindowTextA(m_title2_text); // 제목2 설정
		char min2_text[256], max2_text[256];
		sprintf_s(min2_text, "%.2f", m_min2_val);
		sprintf_s(max2_text, "%.2f", m_max2_val);
		m_min2.SetWindowTextA(min2_text);  // 최소값2 설정
		m_max2.SetWindowTextA(max2_text); // 최대값2 설정
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSlideerDialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	// 메인 윈도우를 받아옴
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	
	// 메인 윈도우에서 활성화된 프레임안의 활성화된 문서 객체를 받아옴
	CImageProKimJiHyeonDoc* pDoc = (CImageProKimJiHyeonDoc*)pFrame->GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);
	
	// 슬라이더의 0에서 255 사이의 현재 위치를 범위 내의 값으로 변환
	float val1 = static_cast<float>(m_slider1.GetPos()) / 255.0f * (m_max1_val - m_min1_val) + m_min1_val;
	float val2 = static_cast<float>(m_slider2.GetPos()) / 255.0f * (m_max2_val - m_min2_val) + m_min2_val;
	
	m_current_pos1_disp = val1;
	UpdateData(FALSE);  // 대화상자에 값 출력

	if (operation == PIXEL_BINARIZATION_H_RANGE)
		pDoc->PixelBinarizationHRangeSlider(val1, val2);
	else if (operation == PIXEL_GAMMA_CORRECTION)
		pDoc->PixelGammaCorrectionSlider2(val1);
	else if (operation == PIXEL_BINARY) {
		pDoc->PixelBinarySlider(val1);
	}
	else if (operation == PIXEL_QUANTIZATION) {
		pDoc->PixelQuantizations(val1);
	}
	
	// 뷰 업데이트
	CImageProKimJiHyeonView* pView = (CImageProKimJiHyeonView*)pFrame->GetActiveFrame()->GetActiveView();
	if (pView) {
		pView->Invalidate(TRUE);
	}
	
	*pResult = 0;
}

void CSlideerDialog::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	// 메인 윈도우를 받아옴
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	
	// 메인 윈도우에서 활성화된 프레임안의 활성화된 문서 객체를 받아옴
	CImageProKimJiHyeonDoc* pDoc = (CImageProKimJiHyeonDoc*)pFrame->GetActiveFrame()->GetActiveDocument();
	ASSERT(pDoc);

	// 슬라이더의 0에서 255 사이의 현재 위치를 범위 내의 값으로 변환
	float val1 = static_cast<float>(m_slider1.GetPos()) / 255.0f * (m_max1_val - m_min1_val) + m_min1_val;
	float val2 = static_cast<float>(m_slider2.GetPos()) / 255.0f * (m_max2_val - m_min2_val) + m_min2_val;
	
	m_current_pos2_disp = val2;
	UpdateData(FALSE);
	
	if (operation == PIXEL_BINARIZATION_H_RANGE)
		pDoc->PixelBinarizationHRangeSlider(val1, val2);
	
	// 뷰 업데이트
	CImageProKimJiHyeonView* pView = (CImageProKimJiHyeonView*)pFrame->GetActiveFrame()->GetActiveView();
	if (pView) {
		pView->Invalidate(TRUE);
	}
	
	*pResult = 0;
}

void CSlideerDialog::SetValue(char* title1, float min1, float max1, float initial_pos1, char* title2, float min2, float max2, float initial_pos2)
{
	// TODO: 여기에 구현 코드 추가.
	strcpy_s(m_title1_text, title1);
	strcpy_s(m_title2_text, title2);
	m_min1_val = min1;
	m_max1_val = max1;
	m_initial_pos1 = initial_pos1;
	m_min2_val = min2;
	m_max2_val = max2;
	m_initial_pos2 = initial_pos2;
}

void CSlideerDialog::SetValue2(char* title1, float min1, float max1, float initial_pos1, char* title2, float min2, float max2, float initial_pos2)
{
	// TODO: 여기에 구현 코드 추가.
	strcpy_s(m_title1_text, title1);
	strcpy_s(m_title2_text, title2);
	m_min1_val = min1;
	m_max1_val = max1;
	m_initial_pos1 = initial_pos1;
	m_min2_val = min2;
	m_max2_val = max2;
	m_initial_pos2 = initial_pos2;
}
