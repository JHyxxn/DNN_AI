// CFormulaResultDialog.cpp: 구현 파일
//

#include "pch.h"
#include "ImagePro_Kim_Ji_Hyeon.h"
#include "afxdialogex.h"
#include "CFormulaResultDialog.h"
#include "ImagePro_Kim_Ji_HyeonDoc.h"

// CFormulaResultDialog 대화 상자

IMPLEMENT_DYNAMIC(CFormulaResultDialog, CDialogEx)

CFormulaResultDialog::CFormulaResultDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORMULA_RESULT_DIALOG, pParent)
{
}

CFormulaResultDialog::~CFormulaResultDialog()
{
}

void CFormulaResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_FORMAT, m_tabCtrl);
	DDX_Control(pDX, IDC_EDIT_ORIGINAL, m_editOriginal);
	DDX_Control(pDX, IDC_EDIT_ASCIIMATH, m_editAsciiMath);
	DDX_Control(pDX, IDC_EDIT_LATEX, m_editLatex);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Control(pDX, IDC_EDIT_CONFIDENCE, m_editConfidence);
	DDX_Control(pDX, IDC_EDIT_HTML, m_editHTML);
	DDX_Control(pDX, IDC_EDIT_JSON, m_editJSON);
}

BEGIN_MESSAGE_MAP(CFormulaResultDialog, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FORMAT, &CFormulaResultDialog::OnTcnSelchangeTabFormat)
	ON_BN_CLICKED(IDC_BUTTON_COPY, &CFormulaResultDialog::OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFormulaResultDialog::OnBnClickedButtonSave)
END_MESSAGE_MAP()

// CFormulaResultDialog 메시지 처리기

BOOL CFormulaResultDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 탭 추가
	m_tabCtrl.InsertItem(0, _T("Text"));
	m_tabCtrl.InsertItem(1, _T("HTML"));
	m_tabCtrl.InsertItem(2, _T("Data"));
	
	// 첫 번째 탭 선택
	m_tabCtrl.SetCurSel(0);
	
	// HTML과 JSON 편집 컨트롤은 처음에 숨김
	m_editHTML.ShowWindow(SW_HIDE);
	m_editJSON.ShowWindow(SW_HIDE);
	
	// Text 탭 컨트롤만 표시
	UpdateTextTab();
	
	// 편집 컨트롤 읽기 전용 설정
	m_editOriginal.SetReadOnly(TRUE);
	m_editAsciiMath.SetReadOnly(TRUE);
	m_editLatex.SetReadOnly(TRUE);
	m_editResult.SetReadOnly(TRUE);
	m_editConfidence.SetReadOnly(TRUE);
	m_editHTML.SetReadOnly(TRUE);
	m_editJSON.SetReadOnly(TRUE);

	return TRUE;
}

void CFormulaResultDialog::SetResult(const FormulaRecognitionResult& result)
{
	m_result = result;
	
	if (IsWindow(m_hWnd)) {
		UpdateTextTab();
		UpdateHTMLTab();
		UpdateDataTab();
	}
}

void CFormulaResultDialog::UpdateTextTab()
{
	CString str;
	
	// 원본 텍스트
	str = CString(m_result.original_text.c_str());
	m_editOriginal.SetWindowText(str);
	
	// AsciiMath
	str = CString(m_result.asciimath.c_str());
	m_editAsciiMath.SetWindowText(str);
	
	// LaTeX
	str = CString(m_result.latex.c_str());
	m_editLatex.SetWindowText(str);
	
	// 계산 결과
	if (m_result.calculation_success) {
		str.Format(_T("%.2f"), m_result.calculation_result);
	}
	else {
		str = _T("계산 실패");
	}
	m_editResult.SetWindowText(str);
	
	// 신뢰도
	str.Format(_T("%.1f%%"), m_result.confidence_rate * 100.0);
	m_editConfidence.SetWindowText(str);
}

void CFormulaResultDialog::UpdateHTMLTab()
{
	CImageProKimJiHyeonDoc* pDoc = NULL;
	// Doc 포인터를 얻는 방법이 필요하지만, 여기서는 직접 생성
	string html = "<div>\n";
	
	if (!m_result.original_text.empty()) {
		// HTML 이스케이프 (간단 버전)
		string escaped_text = m_result.original_text;
		size_t pos = 0;
		while ((pos = escaped_text.find('<', pos)) != string::npos) {
			escaped_text.replace(pos, 1, "&lt;");
			pos += 4;
		}
		pos = 0;
		while ((pos = escaped_text.find('>', pos)) != string::npos) {
			escaped_text.replace(pos, 1, "&gt;");
			pos += 4;
		}
		pos = 0;
		while ((pos = escaped_text.find('&', pos)) != string::npos) {
			if (escaped_text.substr(pos, 4) != "&lt;" && 
			    escaped_text.substr(pos, 4) != "&gt;" &&
			    escaped_text.substr(pos, 5) != "&amp;") {
				escaped_text.replace(pos, 1, "&amp;");
				pos += 5;
			}
			else {
				pos++;
			}
		}
		html += "  <p>원본 텍스트: " + escaped_text + "</p>\n";
	}
	
	html += "  <span class=\"math-inline\">\n";
	// AsciiMath와 LaTeX도 이스케이프 필요
	string escaped_ascii = m_result.asciimath;
	size_t pos = 0;
	while ((pos = escaped_ascii.find('<', pos)) != string::npos) {
		escaped_ascii.replace(pos, 1, "&lt;");
		pos += 4;
	}
	pos = 0;
	while ((pos = escaped_ascii.find('>', pos)) != string::npos) {
		escaped_ascii.replace(pos, 1, "&gt;");
		pos += 4;
	}
	
	string escaped_latex = m_result.latex;
	pos = 0;
	while ((pos = escaped_latex.find('<', pos)) != string::npos) {
		escaped_latex.replace(pos, 1, "&lt;");
		pos += 4;
	}
	pos = 0;
	while ((pos = escaped_latex.find('>', pos)) != string::npos) {
		escaped_latex.replace(pos, 1, "&gt;");
		pos += 4;
	}
	
	html += "    <asciimath style=\"display: none;\">" + escaped_ascii + "</asciimath>\n";
	html += "    <latex style=\"display: none;\">" + escaped_latex + "</latex>\n";
	html += "  </span>\n";
	
	if (m_result.calculation_success) {
		char buffer[64];
		sprintf_s(buffer, "%.2f", m_result.calculation_result);
		html += "  <p>계산 결과: " + string(buffer) + "</p>\n";
	}
	
	char conf_buffer[64];
	sprintf_s(conf_buffer, "%.1f%%", m_result.confidence_rate * 100.0);
	html += "  <p>신뢰도: " + string(conf_buffer) + "</p>\n";
	
	html += "</div>";
	
	CString str(html.c_str());
	m_editHTML.SetWindowText(str);
}

void CFormulaResultDialog::UpdateDataTab()
{
	CImageProKimJiHyeonDoc* pDoc = NULL;
	// Doc 포인터를 얻는 방법이 필요하지만, 여기서는 직접 생성
	string json = "{\n";
	
	char conf_buffer[64];
	sprintf_s(conf_buffer, "%.6f", m_result.confidence);
	json += "  \"confidence\": " + string(conf_buffer) + ",\n";
	
	sprintf_s(conf_buffer, "%.6f", m_result.confidence_rate);
	json += "  \"confidence_rate\": " + string(conf_buffer) + ",\n";
	
	json += "  \"data\": [\n";
	json += "    {\n";
	// JSON 이스케이프 함수 (간단 버전)
	auto escapeJson = [](const string& str) -> string {
		string result;
		for (size_t i = 0; i < str.length(); i++) {
			char c = str[i];
			if (c == '"') result += "\\\"";
			else if (c == '\\') result += "\\\\";
			else if (c == '\n') result += "\\n";
			else if (c == '\r') result += "\\r";
			else if (c == '\t') result += "\\t";
			else result += c;
		}
		return result;
	};
	
	json += "      \"type\": \"asciimath\",\n";
	json += "      \"value\": \"" + escapeJson(m_result.asciimath) + "\"\n";
	json += "    },\n";
	json += "    {\n";
	json += "      \"type\": \"latex\",\n";
	json += "      \"value\": \"" + escapeJson(m_result.latex) + "\"\n";
	json += "    }\n";
	json += "  ],\n";
	
	json += "  \"text\": \"" + escapeJson(m_result.original_text) + "\",\n";
	
	// HTML은 간단하게
	string html = "<div><span class=\"math-inline\"><asciimath style=\"display: none;\">" + 
	              m_result.asciimath + "</asciimath><latex style=\"display: none;\">" + 
	              m_result.latex + "</latex></span></div>";
	json += "  \"html\": \"" + escapeJson(html) + "\",\n";
	
	json += "  \"calculation\": {\n";
	char calc_buffer[64];
	sprintf_s(calc_buffer, "%.2f", m_result.calculation_result);
	json += "    \"result\": " + string(calc_buffer) + ",\n";
	json += "    \"success\": " + string(m_result.calculation_success ? "true" : "false") + "\n";
	json += "  }\n";
	
	json += "}";
	
	CString str(json.c_str());
	m_editJSON.SetWindowText(str);
}

void CFormulaResultDialog::OnTcnSelchangeTabFormat(NMHDR* pNMHDR, LRESULT* pResult)
{
	int nSel = m_tabCtrl.GetCurSel();
	
	// 모든 컨트롤 숨기기
	m_editOriginal.ShowWindow(SW_HIDE);
	m_editAsciiMath.ShowWindow(SW_HIDE);
	m_editLatex.ShowWindow(SW_HIDE);
	m_editResult.ShowWindow(SW_HIDE);
	m_editConfidence.ShowWindow(SW_HIDE);
	m_editHTML.ShowWindow(SW_HIDE);
	m_editJSON.ShowWindow(SW_HIDE);
	
	// Static 컨트롤도 숨기기/보이기
	CWnd* pWnd = GetDlgItem(IDC_STATIC_ORIGINAL);
	if (pWnd) pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem(IDC_STATIC_ASCIIMATH);
	if (pWnd) pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem(IDC_STATIC_LATEX);
	if (pWnd) pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem(IDC_STATIC_RESULT);
	if (pWnd) pWnd->ShowWindow(SW_HIDE);
	pWnd = GetDlgItem(IDC_STATIC_CONFIDENCE);
	if (pWnd) pWnd->ShowWindow(SW_HIDE);
	
	// 선택된 탭에 따라 표시
	if (nSel == 0) { // Text
		UpdateTextTab();
		m_editOriginal.ShowWindow(SW_SHOW);
		m_editAsciiMath.ShowWindow(SW_SHOW);
		m_editLatex.ShowWindow(SW_SHOW);
		m_editResult.ShowWindow(SW_SHOW);
		m_editConfidence.ShowWindow(SW_SHOW);
		
		// Static 컨트롤 표시
		pWnd = GetDlgItem(IDC_STATIC_ORIGINAL);
		if (pWnd) pWnd->ShowWindow(SW_SHOW);
		pWnd = GetDlgItem(IDC_STATIC_ASCIIMATH);
		if (pWnd) pWnd->ShowWindow(SW_SHOW);
		pWnd = GetDlgItem(IDC_STATIC_LATEX);
		if (pWnd) pWnd->ShowWindow(SW_SHOW);
		pWnd = GetDlgItem(IDC_STATIC_RESULT);
		if (pWnd) pWnd->ShowWindow(SW_SHOW);
		pWnd = GetDlgItem(IDC_STATIC_CONFIDENCE);
		if (pWnd) pWnd->ShowWindow(SW_SHOW);
	}
	else if (nSel == 1) { // HTML
		UpdateHTMLTab();
		m_editHTML.ShowWindow(SW_SHOW);
	}
	else if (nSel == 2) { // Data
		UpdateDataTab();
		m_editJSON.ShowWindow(SW_SHOW);
	}
	
	*pResult = 0;
}

void CFormulaResultDialog::OnBnClickedButtonCopy()
{
	int nSel = m_tabCtrl.GetCurSel();
	CString str;
	
	if (nSel == 0) { // Text
		m_editAsciiMath.GetWindowText(str);
	}
	else if (nSel == 1) { // HTML
		m_editHTML.GetWindowText(str);
	}
	else if (nSel == 2) { // Data
		m_editJSON.GetWindowText(str);
	}
	
	if (!str.IsEmpty()) {
		if (OpenClipboard()) {
			EmptyClipboard();
			HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, (str.GetLength() + 1) * sizeof(TCHAR));
			if (hGlob) {
				_tcscpy_s((TCHAR*)hGlob, str.GetLength() + 1, str);
				SetClipboardData(CF_UNICODETEXT, hGlob);
				CloseClipboard();
				AfxMessageBox(_T("클립보드에 복사되었습니다."));
			}
			else {
				CloseClipboard();
			}
		}
	}
}

void CFormulaResultDialog::OnBnClickedButtonSave()
{
	CFileDialog dlg(FALSE, _T("txt"), _T("formula_result"), 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Text Files (*.txt)|*.txt|HTML Files (*.html)|*.html|JSON Files (*.json)|*.json||"));
	
	if (dlg.DoModal() == IDOK) {
		CString filePath = dlg.GetPathName();
		int nSel = m_tabCtrl.GetCurSel();
		CString str;
		
		if (nSel == 0) { // Text
			m_editAsciiMath.GetWindowText(str);
		}
		else if (nSel == 1) { // HTML
			m_editHTML.GetWindowText(str);
		}
		else if (nSel == 2) { // Data
			m_editJSON.GetWindowText(str);
		}
		
		CFile file;
		if (file.Open(filePath, CFile::modeWrite | CFile::modeCreate)) {
			CStringA strA(str);
			file.Write(strA, strA.GetLength());
			file.Close();
			AfxMessageBox(_T("파일이 저장되었습니다."));
		}
	}
}

