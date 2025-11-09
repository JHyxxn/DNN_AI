
// ImagePro_Kim_Ji_HyeonDoc.cpp: CImageProKimJiHyeonDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_Kim_Ji_Hyeon.h"
#endif

#include "ImagePro_Kim_Ji_HyeonDoc.h"

#include <propkey.h>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <regex>
#include <cctype>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProKimJiHyeonDoc

IMPLEMENT_DYNCREATE(CImageProKimJiHyeonDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProKimJiHyeonDoc, CDocument)
END_MESSAGE_MAP()


// CImageProKimJiHyeonDoc 생성/소멸

CImageProKimJiHyeonDoc::CImageProKimJiHyeonDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProKimJiHyeonDoc::~CImageProKimJiHyeonDoc()
{
}

BOOL CImageProKimJiHyeonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProKimJiHyeonDoc serialization

void CImageProKimJiHyeonDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		String fname = ar.GetFile()->GetFilePath();
		inputImg = imread(fname, IMREAD_UNCHANGED);
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProKimJiHyeonDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProKimJiHyeonDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProKimJiHyeonDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProKimJiHyeonDoc 진단

#ifdef _DEBUG
void CImageProKimJiHyeonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProKimJiHyeonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProKimJiHyeonDoc 명령

void CImageProKimJiHyeonDoc::PixelAdd()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() == 1)
		resultImg = inputImg + 100;
	else
		resultImg = inputImg + Scalar(100, 100, 100);
}

void CImageProKimJiHyeonDoc::PixelMINUS()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() == 1)
		resultImg = inputImg - 100;
	else
		resultImg = inputImg - Scalar(100, 100, 100);

}

void CImageProKimJiHyeonDoc::PixelMUL()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() == 1)
		inputImg.convertTo(resultImg, -1, 1.2, 0);  // 흑백 이미지
	else
		inputImg.convertTo(resultImg, -1, 1.2, 0);  // 컬러 이미지
}

void CImageProKimJiHyeonDoc::PixelDIV()
{
	// TODO: 여기에 구현 코드 추가.
	// 픽셀 값을 1.2로 나누기
	if (inputImg.channels() == 1)
		inputImg.convertTo(resultImg, -1, 1.0 / 1.2, 0);
	else
		inputImg.convertTo(resultImg, -1, 1.0 / 1.2, 0);
}

void CImageProKimJiHyeonDoc::MySave()
{
	// TODO: 여기에 구현 코드 추가.
	String fname;
	CFile file;
	CFileDialog dlg(FALSE);     // TRUE : 파일 열기,    FALSE: 파일 저장 

	if (dlg.DoModal() == IDOK) {
		fname = dlg.GetPathName(); // 파일 이름 받아오기
		bool ret = imwrite(fname, resultImg);

		if (ret == false) AfxMessageBox("이미지 저장 실패");
	}
}

void CImageProKimJiHyeonDoc::PixelHistoEq()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	equalizeHist(inputImg, resultImg);
}

void CImageProKimJiHyeonDoc::PixelContrastStretching()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	normalize(inputImg, resultImg, 0, 255, NORM_MINMAX);
}

void CImageProKimJiHyeonDoc::PixelBinarization()
{
	// TODO: 여기에 구현 코드 추가.
	int T =254;
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	threshold(inputImg, resultImg, T, 255, THRESH_BINARY);
}

void CImageProKimJiHyeonDoc::PixelBinarizationHRange()
{
	// TODO: 여기에 구현 코드 추가.
	Mat inputImg_HSV;

	if (inputImg.channels() != 3) {
		AfxMessageBox("컬러 영상을 입력해주세요");
		return;
	}
	cvtColor(inputImg, inputImg_HSV, COLOR_BGR2HSV);
	inRange(inputImg_HSV, Scalar(15, 0, 0), Scalar(30, 255, 255), resultImg);
}

void CImageProKimJiHyeonDoc::PixelBinarizationAutoTresh()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	threshold(inputImg, resultImg, 0, 255, THRESH_OTSU);
}

void CImageProKimJiHyeonDoc::PixelInvert()
{
	// TODO: 여기에 구현 코드 추가.
	bitwise_not(inputImg, resultImg);
}

void CImageProKimJiHyeonDoc::PixelQuantization()
{
	// TODO: 여기에 구현 코드 추가.
	int N = 4;
	Mat lookUpTable(1, 256, CV_8U); // 1행 256열의 영상 생성
	for (int i = 0; i < 256; i++) {
		int level = i / (256 / N), value;
		if (level == 0) value = 0;
		else if (level == N - 1) value = 255;
		else value = (level * (256 / N) + (level + 1) * (256 / N)) / 2;
		lookUpTable.at<BYTE>(0, i) = value;
	}
	LUT(inputImg, lookUpTable, resultImg);
}

void CImageProKimJiHyeonDoc::PixelBinarizationAutoThresh()
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	threshold(inputImg, resultImg, 0, 255, THRESH_OTSU);

}

void CImageProKimJiHyeonDoc::PixelRangeHighligthing()
{
	// TODO: 여기에 구현 코드 추가.
	int start = 100, end = 150;

	Mat lookUpTable(1, 256, CV_8U);
	for (int i = 0; i < 256; i++)
		if (i >= start && i <= end) lookUpTable.at<BYTE>(0, i) = 255;
		else lookUpTable.at<BYTE>(0, i) = i;

	LUT(inputImg, lookUpTable, resultImg);
}

void CImageProKimJiHyeonDoc::PixelGammaCorrection()
{
	// TODO: 여기에 구현 코드 추가.
	float gamma = 0.4f;

	Mat lookUpTable(1, 256, CV_8U);
	for (int i = 0; i < 256; ++i) {
		int value = static_cast<int>(pow(i / 255.0f, gamma) * 255.0f);
		if (value > 255) value = 255;
		lookUpTable.at<BYTE>(0, i) = value;
	}
	LUT(inputImg, lookUpTable, resultImg);
}

void CImageProKimJiHyeonDoc::PixelTwoImagesAdd()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	add(inputImg, inputImg2, resultImg);
}
void CImageProKimJiHyeonDoc::LoadTwoImages()
{
	// TODO: 여기에 구현 코드 추가.
	CFileDialog dlg(TRUE);   // 파일 선택 대화상자 객체 선언
	//        TRUE : 파일 열기
	//         FALSE : 파일 저장
	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {   // 파일 선택 대화 상자 실행 
		String fname = dlg.GetPathName();
		inputImg = imread(fname);
		AfxMessageBox("Select the Second Image");

		if (dlg.DoModal() == IDOK) {   // 파일 선택 대화 상자 실행 
			String fname = dlg.GetPathName();
			inputImg2 = imread(fname);
		}
	}
}

void CImageProKimJiHyeonDoc::PixelBinarizationAdaptiveTresh(void)
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.channels() > 1)
		cvtColor(inputImg, inputImg, COLOR_BGR2GRAY);
	adaptiveThreshold(inputImg, resultImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 7);

}

void CImageProKimJiHyeonDoc::PixelTwoImagesAddLogo()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	Mat roi = inputImg(Rect(0, 0, inputImg2.cols, inputImg2.rows));
	Mat img2gray, mask, mask_inv, img1_bg, img2_fg, dst;
	cvtColor(inputImg2, img2gray, COLOR_BGR2GRAY);
	threshold(img2gray, mask, 10, 255, THRESH_BINARY);
	bitwise_not(mask, mask_inv);
	bitwise_and(inputImg2, inputImg2, img2_fg, mask);
	bitwise_and(roi, roi, img1_bg, mask_inv);
	add(img1_bg, img2_fg, dst);
	resultImg = inputImg.clone();
	dst.copyTo(resultImg(Rect(0, 0, inputImg2.cols, inputImg2.rows)));
}


void CImageProKimJiHyeonDoc::PixelTwoImagesMinus()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	subtract(inputImg, inputImg2, resultImg);
}

void CImageProKimJiHyeonDoc::PixelTwoImagesAnd()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	bitwise_and(inputImg, inputImg2, resultImg);
}

void CImageProKimJiHyeonDoc::PixelTwoImagesOr()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	bitwise_or(inputImg, inputImg2, resultImg);
}

void CImageProKimJiHyeonDoc::PixelTwoImagesXOr()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();
	bitwise_xor(inputImg, inputImg2, resultImg);
}

void CImageProKimJiHyeonDoc::PixelBinarizationHRangeSlider(int min, int max)
{
	// TODO: 여기에 구현 코드 추가.
	Mat inputImg_HSV;

	if (inputImg.channels() != 3) {
		AfxMessageBox("컬러 영상을 입력해주세요");
		return;
	}
	cvtColor(inputImg, inputImg_HSV, COLOR_BGR2HSV);
	inRange(inputImg_HSV, Scalar(min, 0, 0), Scalar(max, 255, 255), resultImg);
	UpdateAllViews(FALSE);
}

void CImageProKimJiHyeonDoc::PixelGammaCorrectionSlider(float gamma)
{
	// TODO: 여기에 구현 코드 추가.
	Mat lookUpTable(1, 256, CV_8U);
	for (int i = 0; i < 256; ++i) {
		int value = static_cast<int>(pow(i / 255.0f, gamma) * 255.0f);
		if (value > 255) value = 255;
		lookUpTable.at<BYTE>(0, i) = value;
	}
	LUT(inputImg, lookUpTable, resultImg);
	UpdateAllViews(FALSE);
}

void CImageProKimJiHyeonDoc::PixelBinarySlider(int thresh_val)
{
	// inputImg가 비어있으면 리턴
	if (inputImg.empty()) return;

	if (thresh_val < 0) thresh_val = 0;
	if (thresh_val > 255) thresh_val = 255;

	// 그레이스케일 변환
	Mat gray;
	if (inputImg.channels() == 3)
		cvtColor(inputImg, gray, COLOR_BGR2GRAY);
	else
		gray = inputImg.clone();

	// 이진화 수행
	threshold(gray, resultImg, thresh_val, 255, THRESH_BINARY);

	// 뷰 갱신 (화면 다시 그리기)
	UpdateAllViews(FALSE);
}

void CImageProKimJiHyeonDoc::PixelGammaCorrectionSlider2(float gamma)
{
	// TODO: 여기에 구현 코드 추가.
	Mat lookUpTable(1, 256, CV_8U);
	for (int i = 0; i < 256; ++i) {
		int value = static_cast<int>(pow(i / 255.0f, gamma) * 255.0f);
		if (value > 255) value = 255;
		lookUpTable.at<BYTE>(0, i) = value;
	}
	LUT(inputImg, lookUpTable, resultImg);
	UpdateAllViews(FALSE);
}

void CImageProKimJiHyeonDoc::PixelQuantizations(int levels)
{
	// TODO: 여기에 구현 코드 추가.
	if (inputImg.empty()) return;

	// 단계 범위 제한
	if (levels < 2) levels = 2;
	if (levels > 64) levels = 64;

	// 입력 영상을 그레이스케일로 변환
	Mat gray;
	if (inputImg.channels() == 3)
		cvtColor(inputImg, gray, COLOR_BGR2GRAY);
	else
		gray = inputImg.clone();

	// 양자화 수행
	Mat quantized = gray.clone();
	int step = 256 / levels;   // 각 단계 구간 크기
	for (int i = 0; i < gray.rows; i++) {
		for (int j = 0; j < gray.cols; j++) {
			int val = gray.at<uchar>(i, j);
			int q = (val / step) * step;   // 해당 구간 대표값으로 매핑
			quantized.at<uchar>(i, j) = q;
		}
	}

	resultImg = quantized;

	// 뷰 갱신
	UpdateAllViews(FALSE);
}

void CImageProKimJiHyeonDoc::RegionBlurring()
{
	// TODO: 여기에 구현 코드 추가.
	blur(inputImg, resultImg, Size(5, 5));
}

void CImageProKimJiHyeonDoc::RegionBlurringGaussian()
{
	// TODO: 여기에 구현 코드 추가.
	GaussianBlur(inputImg, resultImg, Size(5, 5), 0);
}

void CImageProKimJiHyeonDoc::RegionBlurringMedian()
{
	// TODO: 여기에 구현 코드 추가.
	medianBlur(inputImg, resultImg, 5);
}

void CImageProKimJiHyeonDoc::RegionBlurringBilateral()
{
	// TODO: 여기에 구현 코드 추가.
	bilateralFilter(inputImg, resultImg, 5, 80, 80);
}

void CImageProKimJiHyeonDoc::RegionSharpening()
{
	// TODO: 여기에 구현 코드 추가.
	float data[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };
	Mat kernel(3, 3, CV_32FC1, data);
	filter2D(inputImg, resultImg, -1, kernel);
}

void CImageProKimJiHyeonDoc::RegionSobel()
{
	// TODO: 여기에 구현 코드 추가.
	Mat grad_v, grad_h;
	float arr1[9] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 };
	Mat kernel_v(3, 3, CV_32FC1, arr1);
	float arr2[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	Mat kernel_h(3, 3, CV_32FC1, arr2);
	Mat img;
	img = inputImg.clone();
	if (img.channels() > 1) cvtColor(img, img, COLOR_BGR2GRAY);
	filter2D(img, grad_v, CV_32FC1, kernel_v);
	filter2D(img, grad_h, CV_32FC1, kernel_h);
	magnitude(grad_v, grad_h, img); // img = sqrt(grad_v² + grad_h²)
	img.convertTo(resultImg, CV_8UC1); // 32비트 실수를 8비트 uchar로 변환
}

void CImageProKimJiHyeonDoc::RegionCanny()
{
	// TODO: 여기에 구현 코드 추가.
	Mat img;
	int lowThreshold = 50;
	const int ratio = 3;
	const int kernel_size = 3;
	img = inputImg.clone();
	if (img.channels() > 1) cvtColor(img, img, COLOR_BGR2GRAY);
	blur(img, img, Size(3, 3));
	Canny(img, resultImg, lowThreshold, lowThreshold * ratio, kernel_size);
}

void CImageProKimJiHyeonDoc::RegionPrewitt()
{
	// TODO: 여기에 구현 코드 추가.
	Mat grad_v, grad_h;
	float arr1[9] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
	Mat kernel_v(3, 3, CV_32FC1, arr1);
	float arr2[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	Mat kernel_h(3, 3, CV_32FC1, arr2);
	Mat img;
	img = inputImg.clone();
	if (img.channels() > 1) cvtColor(img, img, COLOR_BGR2GRAY);
	filter2D(img, grad_v, CV_32FC1, kernel_v);
	filter2D(img, grad_h, CV_32FC1, kernel_h);
	magnitude(grad_v, grad_h, img);
	img.convertTo(resultImg, CV_8UC1);
}

void CImageProKimJiHyeonDoc::RegionRoberts()
{
	// TODO: 여기에 구현 코드 추가.
	Mat grad_v, grad_h;
	float arr1[4] = { 1, 0, 0, -1 };
	Mat kernel_v(2, 2, CV_32FC1, arr1);
	float arr2[4] = { 0, 1, -1, 0 };
	Mat kernel_h(2, 2, CV_32FC1, arr2);
	Mat img;
	img = inputImg.clone();
	if (img.channels() > 1) cvtColor(img, img, COLOR_BGR2GRAY);
	filter2D(img, grad_v, CV_32FC1, kernel_v);
	filter2D(img, grad_h, CV_32FC1, kernel_h);
	magnitude(grad_v, grad_h, img);
	img.convertTo(resultImg, CV_8UC1);
}

void CImageProKimJiHyeonDoc::RegionLaplacian()
{
	// TODO: 여기에 구현 코드 추가.
	Mat img;
	img = inputImg.clone();
	if (img.channels() > 1) cvtColor(img, img, COLOR_BGR2GRAY);
	Laplacian(img, resultImg, CV_8U, 3);
}

void CImageProKimJiHyeonDoc::RegionEmbossing()
{
	// TODO: 여기에 구현 코드 추가.
	float data[9] = { -1, 0, 0, 0, 0, 0, 0, 0, 1 };
	Mat kernel(3, 3, CV_32FC1, data);
	Mat img;
	
	if (inputImg.channels() > 1) {
		vector<Mat> channels;
		cvtColor(inputImg, img, COLOR_BGR2HSV);
		split(img, channels);
		filter2D(channels[2], channels[2], -1, kernel, Point(-1, -1), 128);
		merge(channels, img);
		cvtColor(img, resultImg, COLOR_HSV2BGR);
	}
	else {
		filter2D(inputImg, resultImg, -1, kernel, Point(-1, -1), 128);
	}
}

void CImageProKimJiHyeonDoc::RegionWatercolor()
{
	// TODO: 여기에 구현 코드 추가.
	Mat img1, img2;
	
	img1 = inputImg.clone();
	for (int i = 0; i < 20; i++)
		if (i % 2 == 0) bilateralFilter(img1, img2, 7, 32, 32);
		else bilateralFilter(img2, img1, 7, 32, 32);
	resultImg = img1.clone();
}

void CImageProKimJiHyeonDoc::MorphologyErosion()
{
	// TODO: 여기에 구현 코드 추가.
	erode(inputImg, resultImg, Mat());
}

void CImageProKimJiHyeonDoc::MorphologyDilation()
{
	// TODO: 여기에 구현 코드 추가.
	dilate(inputImg, resultImg, Mat());
}

void CImageProKimJiHyeonDoc::MorphologyOpening()
{
	// TODO: 여기에 구현 코드 추가.
	Mat tmp;
	erode(inputImg, tmp, Mat());
	erode(tmp, tmp, Mat());
	erode(tmp, tmp, Mat());
	dilate(tmp, tmp, Mat());
	dilate(tmp, tmp, Mat());
	dilate(tmp, resultImg, Mat());
}

void CImageProKimJiHyeonDoc::MorphologyClosing()
{
	// TODO: 여기에 구현 코드 추가.
	Mat tmp;
	dilate(inputImg, tmp, Mat());
	dilate(tmp, tmp, Mat());
	dilate(tmp, tmp, Mat());
	erode(tmp, tmp, Mat());
	erode(tmp, tmp, Mat());
	erode(tmp, resultImg, Mat());
}

void CImageProKimJiHyeonDoc::MorphologyGradient()
{
	// TODO: 여기에 구현 코드 추가.
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(inputImg, resultImg, MORPH_GRADIENT, element);
}

void CImageProKimJiHyeonDoc::MorphologyTopHat()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(inputImg, resultImg, MORPH_TOPHAT, element);
}

void CImageProKimJiHyeonDoc::MorphologyBlackHat()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(inputImg, resultImg, MORPH_BLACKHAT, element);
}

void CImageProKimJiHyeonDoc::MorphologyHitOrMiss()
{
	Mat gray, bw;
	gray = inputImg.clone();
	
	// 컬러 영상이면 그레이스케일로 변환
	if (gray.channels() == 3) 
		cvtColor(gray, gray, COLOR_BGR2GRAY);
	
	// 이진 영상으로 변환 (Hit-or-Miss는 이진 영상에서만 작동)
	threshold(gray, bw, 0, 255, THRESH_OTSU);
	
	Mat out_imgs[4];
	int data1[25] = { 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0};
	int data2[25] = { 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0 };
	int data3[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int data4[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	Mat top(5, 5, CV_32SC1, data1);
	Mat bottom(5, 5, CV_32SC1, data2);
	Mat right(5, 5, CV_32SC1, data3);
	Mat left(5, 5, CV_32SC1, data4);
	
	// 각 방향별 Hit-or-Miss 연산 수행 (이진 영상에 적용)
	morphologyEx(bw, out_imgs[0], MORPH_HITMISS, top);    // top
	morphologyEx(bw, out_imgs[1], MORPH_HITMISS, bottom); // bottom
	morphologyEx(bw, out_imgs[2], MORPH_HITMISS, left);   // left
	morphologyEx(bw, out_imgs[3], MORPH_HITMISS, right);  // right
	
	// 합성 결과 생성
	Mat combined = out_imgs[0] + out_imgs[1] + out_imgs[2] + out_imgs[3];
	
	// 3x2 그리드로 결과 이미지 생성
	// 첫 번째 행: 원본 이미지, 합성 결과
	// 두 번째 행: Top 결과, Bottom 결과
	// 세 번째 행: Left 결과, Right 결과
	int rows = inputImg.rows;
	int cols = inputImg.cols;
	
	// 원본 이미지도 그레이스케일로 변환 (표시용)
	Mat displayOriginal;
	if (inputImg.channels() == 3)
		cvtColor(inputImg, displayOriginal, COLOR_BGR2GRAY);
	else
		displayOriginal = inputImg.clone();
	
	// 3x2 그리드를 위한 결과 이미지 생성 (3행 2열)
	resultImg = Mat(Size(cols * 2, rows * 3), displayOriginal.type());
	
	// 첫 번째 행
	displayOriginal.copyTo(resultImg(Rect(0, 0, cols, rows)));           // 원본 이미지
	combined.copyTo(resultImg(Rect(cols, 0, cols, rows)));             // 합성 결과
	
	// 두 번째 행
	out_imgs[0].copyTo(resultImg(Rect(0, rows, cols, rows)));           // Top 결과
	out_imgs[1].copyTo(resultImg(Rect(cols, rows, cols, rows)));       // Bottom 결과
	
	// 세 번째 행
	out_imgs[2].copyTo(resultImg(Rect(0, rows * 2, cols, rows)));       // Left 결과
	out_imgs[3].copyTo(resultImg(Rect(cols, rows * 2, cols, rows)));   // Right 결과
}

void CImageProKimJiHyeonDoc::MorphologyLineDetection()
{
	Mat gray, bw;
	gray = inputImg;
	if (gray.channels() == 3) cvtColor(gray, gray, COLOR_BGR2GRAY);
	
	bitwise_not(gray, gray); // 배경이 0인 영상으로 변환
	threshold(gray, bw, 0, 255, THRESH_OTSU); // 이진 영상으로 변환
	
	Mat horizontal = bw.clone();
	Mat vertical = bw.clone();
	
	// 수평선 검출
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(15, 1));
	erode(horizontal, horizontal, horizontalStructure);
	dilate(horizontal, horizontal, horizontalStructure);
	bitwise_not(horizontal, horizontal);
	
	// 수직선 검출
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, 4));
	erode(vertical, vertical, verticalStructure);
	dilate(vertical, vertical, verticalStructure);
	bitwise_not(vertical, vertical);
	
	// 입력 영상의 높이의 2배가 되는 출력 영상 생성
	// 윗 부분에 수직선 검출 결과를 아랫 부분에 수평선 검출 결과를 저장
	resultImg = Mat(Size(inputImg.cols, inputImg.rows*2), vertical.type());
	vertical.copyTo(resultImg(Rect(0, 0, inputImg.cols, inputImg.rows)));
	horizontal.copyTo(resultImg(Rect(0, inputImg.rows, inputImg.cols, inputImg.rows)));
}

void CImageProKimJiHyeonDoc::MorphologyCountCell()
{
	resultImg = inputImg.clone();
	if (resultImg.channels() > 1) cvtColor(resultImg, resultImg, COLOR_BGR2GRAY);
	threshold(resultImg, resultImg, 128, 255, THRESH_BINARY);
	bitwise_not(resultImg, resultImg);
	erode(resultImg, resultImg, Mat());
	erode(resultImg, resultImg, Mat());
	erode(resultImg, resultImg, Mat());
	dilate(resultImg, resultImg, Mat());
	dilate(resultImg, resultImg, Mat());
	dilate(resultImg, resultImg, Mat());
	
	// 세포수 계산
	Mat labelImage(resultImg.size(), CV_32S);
	int nLabels = connectedComponents(resultImg, labelImage, 8);
	
	char buf[80];
	sprintf_s(buf, "Number of cells = %d", nLabels - 1);
	AfxMessageBox(buf);
}

void CImageProKimJiHyeonDoc::GeometryZoominPixelCopy()
{
	resize(inputImg, resultImg, Size(0, 0), 4.0, 4.0, INTER_NEAREST);
}

void CImageProKimJiHyeonDoc::GeometryZoominInterpolation()
{
	resize(inputImg, resultImg, Size(0, 0), 4.0, 4.0, INTER_LINEAR);
}

void CImageProKimJiHyeonDoc::GeometryZoomoutSubsampling()
{
	resize(inputImg, resultImg, Size(0, 0), 1 / 3.0, 1 / 3.0, INTER_NEAREST);
}

void CImageProKimJiHyeonDoc::GeometryZoomoutAvg()
{
	resize(inputImg, resultImg, Size(0, 0), 1 / 3.0, 1 / 3.0, INTER_AREA);
}

void CImageProKimJiHyeonDoc::GeometryRotate()
{
	Point2f center(inputImg.cols / 2.0, inputImg.rows / 2.0);
	Mat rot = getRotationMatrix2D(center, 30, 1.0);
	Rect2f bbox = RotatedRect(center, inputImg.size(), 30).boundingRect2f();
	rot.at<double>(0, 2) += (bbox.width - inputImg.cols) / 2.0;
	rot.at<double>(1, 2) += (bbox.height - inputImg.rows) / 2.0;
	warpAffine(inputImg, resultImg, rot, bbox.size());
}

void CImageProKimJiHyeonDoc::GeometryFlipVertical()
{
	flip(inputImg, resultImg, 0);
}

void CImageProKimJiHyeonDoc::GeometryFlipHorizontal()
{
	flip(inputImg, resultImg, 1);
}

void CImageProKimJiHyeonDoc::GeometryFlipBoth()
{
	flip(inputImg, resultImg, -1);
}

void CImageProKimJiHyeonDoc::GeometryWarping()
{
	control_line source_lines[23] =
	{{116,7,207,5},{34,109,90,21},{30,128,55,249},{65,261,118,320},
	{123,321,171,321},{179,319,240,264},{247,251,282,135},{228,8,281,114},
	{78,106,123,109},{187,115,235,114},{72,142,99,128},{74,150,122,154},
	{108,127,123,146},{182,152,213,132},{183,159,229,157},{219,131,240,154},
	{80,246,117,212},{127,222,146,223},{154,227,174,221},{183,213,228,252},
	{114,255,186,257},{109,258,143,277},{152,278,190,262}};

	control_line dest_lines[23] =
	{{120,8,200,6},{12,93,96,16},{16,110,74,271},{96,290,126,336},
	{142,337,181,335},{192,335,232,280},{244,259,288,108},{212,13,285,92},
	{96,135,136,118},{194,119,223,125},{105,145,124,134},{110,146,138,151},
	{131,133,139,146},{188,146,198,134},{189,153,218,146},{204,133,221,140},
	{91,268,122,202},{149,206,159,209},{170,209,181,204},{208,199,235,265},
	{121,280,205,284},{112,286,160,301},{166,301,214,287}};

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;
	int line;
	int x, y;
	int source_x, source_y;
	int num_lines = 23;

	resultImg.create(inputImg.size(), inputImg.type());

	double u; // 수직 교차점의 위치
	double h; // 제어선으로부터 픽셀의 수직 변위
	double d; // 제어선과 픽셀 사이의 거리
	double tx, ty; // 결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp; // 각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치
	double weight; // 각 제어선의 가중치
	double totalWeight; // 가중치의 합

	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	// 출력 영상의 각 픽셀에 대하여
	for (y = 0; y < inputImg.rows; y++)
	{
		for (x = 0; x < inputImg.cols; x++)
		{
			totalWeight = 0.0;
			tx = 0.0;
			ty = 0.0;

			// 각 제어선에 대하여
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((double)(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				// 수직교차점의 위치 및 픽셀의 수직 변위 계산
				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / (double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				h = (double)((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				// 제어선과 픽셀 사이의 거리 계산
				if (u < 0) d = sqrt((double)(x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((double)(x - x2) * (x - x2) + (y - y2) * (y - y2));
				else d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;
				src_line_length = sqrt((double)(src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				// 입력 영상에서의 대응 픽셀 위치 계산
				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				// 제어선에 대한 가중치 계산
				weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

				// 대응 픽셀과의 변위 계산
				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalWeight += weight;
			}

			source_x = x + (int)(tx / totalWeight + 0.5);
			source_y = y + (int)(ty / totalWeight + 0.5);

			// 영상의 경계를 벗어나는지 검사
			if (source_x < 0) source_x = 0;
			if (source_x > inputImg.cols - 1) source_x = inputImg.cols - 1;
			if (source_y < 0) source_y = 0;
			if (source_y > inputImg.rows - 1) source_y = inputImg.rows - 1;

			if (inputImg.channels() == 1)
				resultImg.at<BYTE>(y, x) = inputImg.at<BYTE>(source_y, source_x);
			else if (inputImg.channels() == 3)
				resultImg.at<Vec3b>(y, x) = inputImg.at<Vec3b>(source_y, source_x);
		}
	}
}

void CImageProKimJiHyeonDoc::GeometryMorphing()
{
#define NUM_FRAMES 10

	control_line source_lines[23] =
	{{116,7,207,5},{34,109,90,21},{30,128,55,249},{65,261,118,320},
	{123,321,171,321},{179,319,240,264},{247,251,282,135},{228,8,281,114},
	{78,106,123,109},{187,115,235,114},{72,142,99,128},{74,150,122,154},
	{108,127,123,146},{182,152,213,132},{183,159,229,157},{219,131,240,154},
	{80,246,117,212},{127,222,146,223},{154,227,174,221},{183,213,228,252},
	{114,255,186,257},{109,258,143,277},{152,278,190,262}};

	control_line dest_lines[23] =
	{{120,8,200,6},{12,93,96,16},{16,110,74,271},{96,290,126,336},
	{142,337,181,335},{192,335,232,280},{244,259,288,108},{212,13,285,92},
	{96,135,136,118},{194,119,223,125},{105,145,124,134},{110,146,138,151},
	{131,133,139,146},{188,146,198,134},{189,153,218,146},{204,133,221,140},
	{91,268,122,202},{149,206,159,209},{170,209,181,204},{208,199,235,265},
	{121,280,205,284},{112,286,160,301},{166,301,214,287}};

	// 두 입력 영상을 읽어들임
	LoadTwoImages();

	// 중간 프레임의 워핑 결과를 저장을 위한 기억장소 할당
	Mat warpedImg;
	Mat warpedImg2;
	warpedImg.create(inputImg.size(), inputImg.type());
	warpedImg2.create(inputImg.size(), inputImg.type());

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;
	int dest_x1, dest_y1, dest_x2, dest_y2;
	double src_line_length, dest_line_length;
	int line;
	int x, y;
	int source_x, source_y;
	int source_x2, source_y2;
	int num_lines = 23;
	int last_row, last_col;
	int frame;
	int i;

	double u; // 수직 교차점의 위치
	double h; // 제어선으로부터 픽셀의 수직 변위
	double d; // 제어선과 픽셀 사이의 거리
	double tx, ty; // 결과영상 픽셀에 대응되는 입력 영상 1 픽셀 사이의 변위의 합
	double tx2, ty2; // 결과영상 픽셀에 대응되는 입력 영상 2 픽셀 사이의 변위의 합
	double xp, yp; // 각 제어선에 대해 계산된 입력 영상 1의 대응되는 픽셀 위치
	double xp2, yp2; // 각 제어선에 대해 계산된 입력 영상 2의 대응되는 픽셀 위치
	double weight; // 각 제어선의 가중치
	double totalWeight; // 가중치의 합
	double fweight; // 중간 프레임에 대한 가중치

	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	control_line warp_lines[23];

	// 각 중간 프레임에 대하여
	for (frame = 1; frame <= NUM_FRAMES; frame++)
	{
		morphedImg[frame - 1].create(inputImg.size(), inputImg.type());
		last_row = inputImg.rows - 1;
		last_col = inputImg.cols - 1;

		// 중간 프레임에 대한 가중치 계산
		fweight = (double)(frame) / NUM_FRAMES;

		// 중간 프레임에 대한 제어선 계산
		for (line = 0; line < num_lines; line++)
		{
			warp_lines[line].Px = (int)(source_lines[line].Px + (dest_lines[line].Px - source_lines[line].Px) * fweight);
			warp_lines[line].Py = (int)(source_lines[line].Py + (dest_lines[line].Py - source_lines[line].Py) * fweight);
			warp_lines[line].Qx = (int)(source_lines[line].Qx + (dest_lines[line].Qx - source_lines[line].Qx) * fweight);
			warp_lines[line].Qy = (int)(source_lines[line].Qy + (dest_lines[line].Qy - source_lines[line].Qy) * fweight);
		}

		// 출력 영상의 각 픽셀에 대하여
		for (y = 0; y < inputImg.rows; y++)
		{
			for (x = 0; x < inputImg.cols; x++)
			{
				totalWeight = 0.0;
				tx = 0.0;
				ty = 0.0;
				tx2 = 0.0;
				ty2 = 0.0;

				// 각 제어선에 대하여
				for (line = 0; line < num_lines; line++)
				{
					dest_x1 = warp_lines[line].Px;
					dest_y1 = warp_lines[line].Py;
					dest_x2 = warp_lines[line].Qx;
					dest_y2 = warp_lines[line].Qy;

					dest_line_length = sqrt((double)(dest_x2 - dest_x1) * (dest_x2 - dest_x1) + (dest_y2 - dest_y1) * (dest_y2 - dest_y1));

					// 수직교차점의 위치 및 픽셀의 수직 변위 계산
					u = (double)((x - dest_x1) * (dest_x2 - dest_x1) + (y - dest_y1) * (dest_y2 - dest_y1)) / (double)((dest_x2 - dest_x1) * (dest_x2 - dest_x1) + (dest_y2 - dest_y1) * (dest_y2 - dest_y1));
					h = (double)((y - dest_y1) * (dest_x2 - dest_x1) - (x - dest_x1) * (dest_y2 - dest_y1)) / dest_line_length;

					// 제어선과 픽셀 사이의 거리 계산
					if (u < 0) d = sqrt((double)(x - dest_x1) * (x - dest_x1) + (y - dest_y1) * (y - dest_y1));
					else if (u > 1) d = sqrt((double)(x - dest_x2) * (x - dest_x2) + (y - dest_y2) * (y - dest_y2));
					else d = fabs(h);

					src_x1 = source_lines[line].Px;
					src_y1 = source_lines[line].Py;
					src_x2 = source_lines[line].Qx;
					src_y2 = source_lines[line].Qy;
					src_line_length = sqrt((double)(src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

					// 입력 영상 1에서의 대응 픽셀 위치 계산
					xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
					yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

					dest_x1 = dest_lines[line].Px;
					dest_y1 = dest_lines[line].Py;
					dest_x2 = dest_lines[line].Qx;
					dest_y2 = dest_lines[line].Qy;

					// 입력 영상 2에서의 대응 픽셀 위치 계산
					xp2 = dest_x1 + u * (dest_x2 - dest_x1) - h * (dest_y2 - dest_y1) / dest_line_length;
					yp2 = dest_y1 + u * (dest_y2 - dest_y1) + h * (dest_x2 - dest_x1) / dest_line_length;

					// 제어선에 대한 가중치 계산
					weight = pow((pow((double)(dest_line_length), p) / (a + d)), b);

					// 입력 영상 1의 대응 픽셀과의 변위 계산
					tx += (xp - x) * weight;
					ty += (yp - y) * weight;

					// 입력 영상 2의 대응 픽셀과의 변위 계산
					tx2 += (xp2 - x) * weight;
					ty2 += (yp2 - y) * weight;

					totalWeight += weight;
				}

				// 입력 영상 1의 대응 픽셀 위치 계산
				source_x = x + (int)(tx / totalWeight + 0.5);
				source_y = y + (int)(ty / totalWeight + 0.5);

				// 입력 영상 2의 대응 픽셀 위치 계산
				source_x2 = x + (int)(tx2 / totalWeight + 0.5);
				source_y2 = y + (int)(ty2 / totalWeight + 0.5);

				// 영상의 경계를 벗어나는지 검사
				if (source_x < 0) source_x = 0;
				if (source_x > last_col) source_x = last_col;
				if (source_y < 0) source_y = 0;
				if (source_y > last_row) source_y = last_row;
				if (source_x2 < 0) source_x2 = 0;
				if (source_x2 > last_col) source_x2 = last_col;
				if (source_y2 < 0) source_y2 = 0;
				if (source_y2 > last_row) source_y2 = last_row;

				// 워핑 결과 저장
				if (inputImg.channels() == 1)
				{
					warpedImg.at<BYTE>(y, x) = inputImg.at<BYTE>(source_y, source_x);
					warpedImg2.at<BYTE>(y, x) = inputImg2.at<BYTE>(source_y2, source_x2);
				}
				else if (inputImg.channels() == 3)
				{
					warpedImg.at<Vec3b>(y, x) = inputImg.at<Vec3b>(source_y, source_x);
					warpedImg2.at<Vec3b>(y, x) = inputImg2.at<Vec3b>(source_y2, source_x2);
				}
			}
		}

		// 모핑 결과 합병
		for (y = 0; y < inputImg.rows; y++)
		{
			for (x = 0; x < inputImg.cols; x++)
			{
				if (inputImg.channels() == 1)
					morphedImg[frame - 1].at<BYTE>(y, x) = (int)((1.0 - fweight) * warpedImg.at<BYTE>(y, x) + fweight * warpedImg2.at<BYTE>(y, x));
				else if (inputImg.channels() == 3)
					morphedImg[frame - 1].at<Vec3b>(y, x) = ((1.0 - fweight) * warpedImg.at<Vec3b>(y, x) + fweight * warpedImg2.at<Vec3b>(y, x));
			}
		}
	} // Geometry Morphing() 함수 끝
}

void CImageProKimJiHyeonDoc::GeometryWarpingMouse(int Ax, int Ay, int Bx, int By)
{
	// TODO: 마우스로 선택한 영역에 대한 워핑 구현
	// 현재는 기본 구현만 제공
	resultImg = inputImg.clone();
}

void CImageProKimJiHyeonDoc::FaceTracking(int Ax, int Ay, int Bx, int By)
{
	// TODO: 얼굴 추적 구현
	// 현재는 기본 구현만 제공
	resultImg = inputImg.clone();
}

void CImageProKimJiHyeonDoc::DnnImageClassification()
{
	string model_path = "D:/dnn/bvlc_googlenet.caffemodel";
	string config_path = "D:/dnn/bvlc_googlenet.prototxt";
	resultImg = inputImg.clone();
	Net net = readNet(model_path, config_path);
	Mat blob = blobFromImage(inputImg, 1.0, Size(224, 224), Scalar(104, 117, 123));
	net.setInput(blob);
	Mat prob = net.forward();

	int classId;
	double maxVal;
	Point maxLoc;
	minMaxLoc(prob, 0, &maxVal, 0, &maxLoc);
	classId = maxLoc.x;

	ifstream ifs("D:/dnn/classification_classes_ILSVRC2012.txt");
	string line;
	vector<string> classes;
	while (getline(ifs, line))
		classes.push_back(line);

	string label = format("%s: %.2f", classes[classId].c_str(), maxVal);
	putText(resultImg, label, Point(0, 55), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
}

void CImageProKimJiHyeonDoc::DnnMosaic()
{
	// 1. 모델 불러오기
	string modelPath = "D:/dnn/fast_neural_style_mosaic.onnx";
	Net net = readNet(modelPath);

	// 2. 입력 데이터 준비
	Mat img;
	resize(inputImg, img, Size(224, 224));
	Mat blob = blobFromImage(img, 1.0, Size(), Scalar(), true);
	net.setInput(blob);

	// 3. 추론 실행
	Mat result = net.forward();

	// 4. 포인터로부터 Mat 만들기
	int height = result.size[2];
	int width = result.size[3];
	// 결과 데이터를 복사 (주의: OpenCV는 HWC, result는 CHW)
	Mat R = Mat(Size(width, height), CV_32F, result.ptr(0, 0));
	Mat G = Mat(Size(width, height), CV_32F, result.ptr(0, 1));
	Mat B = Mat(Size(width, height), CV_32F, result.ptr(0, 2));

	// 5. CHW → HWC (merge channels)
	Mat channels[] = { R, G, B };
	Mat image(height, width, CV_32FC3);
	merge(channels, 3, image); // image: CV_32FC3, RGB 순서

	double minVal, maxVal;
	minMaxLoc(image, &minVal, &maxVal);
	Mat normImage;
	image.convertTo(normImage, CV_32F, 1.0 / (maxVal - minVal), -minVal / (maxVal - minVal));

	// 6. RGB → BGR변환
	cvtColor(normImage, normImage, COLOR_RGB2BGR);

	// 7. float → uchar (0~255)
	Mat finalImage;
	normImage.convertTo(finalImage, CV_8UC3, 255.0);
	resize(finalImage, resultImg, inputImg.size());
}

void CImageProKimJiHyeonDoc::DnnFacialExpressionRecognition()
{
	string model_path = "D:/dnn/facial_expression_recognition_mobilefacenet_2022july.onnx";
	string detector_model_path = "D:/dnn/face_detection_yunet_2023mar.onnx";
	float detect_threshold = 0.9;
	float nms_threshold = 0.3;
	int top_k = 5000;
	Size input_size(320, 320);
	int backend_id = DNN_BACKEND_OPENCV;
	int target_id = DNN_TARGET_CPU;

	Ptr<FaceDetectorYN> face_detector = FaceDetectorYN::create(
		detector_model_path, "", input_size, detect_threshold, nms_threshold,
		top_k, backend_id, target_id);

	Net model = readNet(model_path);
	model.setPreferableBackend(backend_id);
	model.setPreferableTarget(target_id);

	float std[5][2] = { // 표준 위치
		{38.2946, 51.6963}, // 왼쪽눈
		{73.5318, 51.5014}, // 오른쪽 눈
		{56.0252, 71.7366}, // 코
		{41.5493, 92.3655}, // 왼쪽 입 가장자리
		{70.7299, 92.2041} // 오른쪽 입 가장자리
	};

	vector<String> expressionEnum = {
		"angry", "disgust", "fearful", "happy", "neutral", "sad", "surprised"
	};

	Mat stdPoints = Mat(5, 2, CV_32F, std);
	Size patchSize = Size(112, 112);
	Scalar imageMean = Scalar(0.5, 0.5, 0.5);
	Scalar imageStd = Scalar(0.5, 0.5, 0.5);
	const String inputNames = "data";
	const String outputNames = "label";

	// 2. 얼굴 검출
	face_detector->setInputSize(inputImg.size());
	face_detector->setTopK(5000);
	Mat faces;
	face_detector->detect(inputImg, faces);
	resultImg = inputImg.clone();

	for (int i = 0; i < faces.rows; ++i)
	{
		Mat face = faces.row(i);
		// 눈, 코, 입 좌표 추출
		float face_data[5][2] = {
			{face.at<float>(4), face.at<float>(5)}, // 왼쪽 눈
			{face.at<float>(6), face.at<float>(7)}, // 오른쪽 눈
			{face.at<float>(8), face.at<float>(9)}, // 코
			{face.at<float>(10), face.at<float>(11)}, // 왼쪽 입 가장자리
			{face.at<float>(12), face.at<float>(13)} // 오른쪽 입 가장자리
		};
		Mat points = Mat(5, 2, CV_32F, face_data);

		// 얼굴 정렬 (Geometric Transformation)
		Mat transformation = estimateAffine2D(points, stdPoints);
		Mat aligned = Mat::zeros(patchSize.height, patchSize.width, inputImg.type());
		warpAffine(inputImg, aligned, transformation, patchSize);

		// 영상 정규화 (Image Normalization)
		aligned.convertTo(aligned, CV_32F, 1.0 / 255.0);
		aligned -= imageMean;
		aligned /= imageStd;

		// DNN 추론
		Mat inputBlob = blobFromImage(aligned);
		model.setInput(inputBlob, inputNames);
		// 7개 표정에 대한 확률값 출력
		Mat outputBlob = model.forward(outputNames);

		Point maxLoc;
		minMaxLoc(outputBlob, 0, 0, 0, &maxLoc);

		String exp;
		if (maxLoc.x >= 0 && maxLoc.x < (int)expressionEnum.size())
			exp = expressionEnum[maxLoc.x];
		else
			exp = "";

		int x1 = (int)face.at<float>(0);
		int y1 = (int)face.at<float>(1);
		int w = (int)face.at<float>(2);
		int h = (int)face.at<float>(3);
		float conf = face.at<float>(14);

		rectangle(resultImg, Rect(x1, y1, w, h), Scalar(0, 0, 255), 2);
		putText(resultImg, format("%s", exp.c_str()), Point(x1, y1 + 12),
			FONT_HERSHEY_DUPLEX, 0.30, Scalar(0, 255, 0));
	}
}

void CImageProKimJiHyeonDoc::DnnHumanSegmentation()
{
	static int model_initialized = false;
	static Net net;
	static Size currentSize;
	string model_path = "D:/dnn/human_segmentation_pphumanseg_2023mar.onnx";
	Scalar imageMean = Scalar(0.5, 0.5, 0.5);
	Scalar imageStd = Scalar(0.5, 0.5, 0.5);
	Size modelInputSize = Size(192, 192);
	int backend_id = DNN_BACKEND_OPENCV;
	int target_id = DNN_TARGET_CPU;

	if (model_initialized == false) {
		net = readNet(model_path);
		net.setPreferableBackend(backend_id);
		net.setPreferableTarget(target_id);
		model_initialized = true;
	}

	if (model_initialized == true) {
		currentSize = inputImg.size();
		Mat preprocessed = Mat::zeros(modelInputSize, inputImg.type());
		resize(inputImg, preprocessed, modelInputSize);
		preprocessed.convertTo(preprocessed, CV_32F, 1.0 / 255.0);
		preprocessed -= imageMean;
		preprocessed /= imageStd;

		Mat inputBlob = blobFromImage(preprocessed);
		net.setInput(inputBlob);
		Mat result = net.forward();
		// 네트워크 결과가 192x192 크기의 0에서 1사이의 값으로 반환됨
		// (0.5 미만이면 사람, 이상이면 배경)
		resultImg = Mat(192, 192, CV_32F, result.ptr<float>());
		resize(resultImg, resultImg, currentSize); // 원래 영상 크기로 변환
		threshold(resultImg, resultImg, 0.5, 1.0, THRESH_BINARY);
		// 0에서 1사이의 실수 값을 0에서 255의 부호 없는 정수로 변환
		resultImg.convertTo(resultImg, CV_8U, 255);
	}
}

void CImageProKimJiHyeonDoc::DnnObjectTracking(int Ax, int Ay, int Bx, int By)
{
	static int model_initialized = false;
	static Rect selectRect;
	static Ptr<TrackerDaSiamRPN> tracker;
	// 템플릿과 비교를 위한 모델
	string net = "D:/dnn/dasiamrpn_model.onnx";
	// 추적할 템플릿에 대한 분류 맵 생성을 위한 모델
	string kernel_cls1 = "D:/dnn/dasiamrpn_kernel_cls1.onnx";
	// 추적할 템플릿에 대한 회귀 맵 생성을 위한 모델
	string kernel_r1 = "D:/dnn/dasiamrpn_kernel_r1.onnx";

	if (Ax > -1) {
		// 모델 초기화
		int minx = Ax < Bx ? Ax : Bx;
		int miny = Ay < By ? Ay : By;
		int width = abs(Bx - Ax);
		int height = abs(By - Ay);
		selectRect = Rect(minx, miny, width, height);

		TrackerDaSiamRPN::Params params;
		params.model = net;
		params.kernel_cls1 = kernel_cls1;
		params.kernel_r1 = kernel_r1;
		params.backend = DNN_BACKEND_OPENCV;
		params.target = DNN_TARGET_CPU;
		tracker = TrackerDaSiamRPN::create(params);
		tracker->init(inputImg, selectRect); // 추적할 개체에 대한 특징 추출
		model_initialized = true;
	}

	if (model_initialized == true) {
		Rect rect;
		bool ok = tracker->update(inputImg, rect); // 객체 추적
		float score = tracker->getTrackingScore();
		resultImg = inputImg.clone();

		if (ok) {
			rectangle(resultImg, rect, Scalar(0, 255, 0), 2);
			string scoreLabel = format("Score: %f", score);
			putText(resultImg, scoreLabel, Point(0, 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
		}
	}
}

void CImageProKimJiHyeonDoc::DnnQrcodeRecognition()
{
	string detect_prototxt = "D:/dnn/detect_2021nov.prototxt";
	string detect_model = "D:/dnn/detect_2021nov.caffemodel";
	string sr_prototxt = "D:/dnn/sr_2021nov.prototxt"; // super resolution 모델
	string sr_model = "D:/dnn/sr_2021nov.caffemodel"; // QR 코드가 작을때 사용

	Ptr<wechat_qrcode::WeChatQRCode> model = makePtr<wechat_qrcode::WeChatQRCode>(detect_prototxt, detect_model, sr_prototxt, sr_model);

	vector<string> results;
	vector<Mat> points;
	results = model->detectAndDecode(inputImg, points);

	resultImg = inputImg.clone();
	double fontScale = 0.5;
	int fontSize = 1;
	Scalar points_color = Scalar(0, 255, 0);
	Scalar text_color = Scalar(0, 255, 0);

	for (int i = 0; i < results.size(); i++) {
		Mat p = points[i];
		for (int r = 0; r < p.rows; r++) {
			Point point(p.at<float>(r, 0), p.at<float>(r, 1));
			circle(resultImg, point, 10, points_color, -1);
		}

		int qrcode_center_x = (p.at<float>(0, 0) + p.at<float>(2, 0)) / 2;
		int qrcode_center_y = (p.at<float>(0, 1) + p.at<float>(2, 1)) / 2;

		int baseline = 0;
		Size text_size = getTextSize(results[i], FONT_HERSHEY_DUPLEX, fontScale, fontSize, &baseline);
		Point text_pos(qrcode_center_x - text_size.width / 2, qrcode_center_y + text_size.height / 2);
		putText(resultImg, results[i], text_pos, FONT_HERSHEY_DUPLEX, fontScale, text_color, fontSize);
	}
}

void CImageProKimJiHyeonDoc::DnnDeblurring()
{
	// 1. 모델 불러오기
	string modelPath = "D:/dnn/nafnet_REDS_width64.onnx";
	Net net = readNet(modelPath);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	// 2. 입력 데이터 준비
	Mat img;
	inputImg.convertTo(img, CV_32F, 1.0 / 255.0);
	resize(img, img, Size(256, 256));
	Mat blob = blobFromImage(img, 1.0, Size(), Scalar(), true);
	net.setInput(blob);

	// 3. 추론 실행
	Mat result = net.forward();

	// 4. 포인터로부터 Mat 만들기
	const int height = result.size[2];
	const int width = result.size[3];
	// 주의: OpenCV는 HWC, result는 CHW
	Mat R(height, width, CV_32F, result.ptr<float>(0, 0));
	Mat G(height, width, CV_32F, result.ptr<float>(0, 1));
	Mat B(height, width, CV_32F, result.ptr<float>(0, 2));

	// 5. CHW → HWC (merge channels)
	Mat channels[] = { R, G, B };
	Mat image(height, width, CV_32FC3);
	merge(channels, 3, image);
	// image: CV_32FC3, RGB 순서

	// 6. 정규화 (minVal, maxVal을 찾아서 0~1 범위로 정규화)
	double minVal, maxVal;
	minMaxLoc(image, &minVal, &maxVal);
	Mat normImage;
	image.convertTo(normImage, CV_32F, 1.0 / (maxVal - minVal), -minVal / (maxVal - minVal));

	// 7. RGB → BGR 변환
	cvtColor(normImage, normImage, COLOR_RGB2BGR);

	// 8. float → uchar (0~255)
	Mat finalImage;
	normImage.convertTo(finalImage, CV_8UC3, 255.0);
	resize(finalImage, resultImg, inputImg.size());
}

void CImageProKimJiHyeonDoc::DnnFaceDetection()
{
	static int model_initialized = false;
	static Ptr<FaceDetectorYN> detector;
	string model_path = "D:/dnn/face_detection_yunet_2023mar.onnx";
	float scoreThreshold = 0.9;
	float nmsThreshold = 0.3;
	int topK = 5000;
	int thickness = 2;

	if (model_initialized == false) {
		detector = FaceDetectorYN::create(model_path, "",
			Size(320, 320), scoreThreshold, nmsThreshold, topK);
		model_initialized = true;
	}

	detector->setInputSize(Size(inputImg.cols, inputImg.rows));

	Mat faces;
	detector->detect(inputImg, faces);
	resultImg = inputImg.clone();

	for (int i = 0; i < faces.rows; i++) {
		rectangle(resultImg, Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), 
			int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), Scalar(0, 255, 0), thickness);
		circle(resultImg, Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 
			2, Scalar(255, 0, 0), thickness);
		circle(resultImg, Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 
			2, Scalar(0, 0, 255), thickness);
		circle(resultImg, Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 
			2, Scalar(0, 255, 0), thickness);
		circle(resultImg, Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 
			2, Scalar(255, 0, 255), thickness);
		circle(resultImg, Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 
			2, Scalar(0, 255, 255), thickness);
	}
}

void CImageProKimJiHyeonDoc::DnnFaceMatching()
{
	LoadTwoImages();
	string detector_model_path = "D:/dnn/face_detection_yunet_2023mar.onnx";
	string model_path = "D:/dnn/face_recognition_sface_2021dec.onnx";
	int backend_id = DNN_BACKEND_OPENCV;
	int target_id = DNN_TARGET_CPU;
	float detect_threshold = 0.9;
	float nms_threshold = 0.3;
	int top_k = 5000;
	int distance_type = 0;
	Size input_size(320, 320);

	Ptr<FaceDetectorYN> face_detector = FaceDetectorYN::create(
		detector_model_path, "", input_size, detect_threshold, nms_threshold,
		top_k, backend_id, target_id);

	Ptr<FaceRecognizerSF> face_recognizer = FaceRecognizerSF::create(
		model_path, "", backend_id, target_id);

	// 첫 번째 이미지에서 얼굴 검출 및 특징 추출
	face_detector->setInputSize(inputImg.size());
	face_detector->setTopK(1);
	Mat target_face;
	face_detector->detect(inputImg, target_face);

	Mat target_aligned;
	face_recognizer->alignCrop(inputImg, target_face, target_aligned);

	Mat features;
	Mat target_features;
	face_recognizer->feature(target_aligned, features);
	target_features = features.clone();

	// 두 번째 이미지에서 얼굴 검출 및 매칭
	face_detector->setInputSize(inputImg2.size());
	face_detector->setTopK(5000);
	Mat query_faces;
	face_detector->detect(inputImg2, query_faces);
	double threshold_cosine = 0.363;

	resultImg = inputImg2.clone();

	for (int i = 0; i < query_faces.rows; ++i) {
		Mat aligned;
		face_recognizer->alignCrop(inputImg2, query_faces.row(i), aligned);

		Mat query_features;
		face_recognizer->feature(aligned, features);
		query_features = features.clone();

		double score = face_recognizer->match(target_features, query_features, distance_type);

		int x1 = (int)query_faces.at<float>(i, 0);
		int y1 = (int)query_faces.at<float>(i, 1);
		int w = (int)query_faces.at<float>(i, 2);
		int h = (int)query_faces.at<float>(i, 3);
		float conf = query_faces.at<float>(i, 14);

		Scalar box_color = (score >= threshold_cosine) ? Scalar(0, 255, 0) : Scalar(0, 0, 255);
		rectangle(resultImg, Rect(x1, y1, w, h), box_color, 2);
		putText(resultImg, format("%.2f", score), Point(x1, y1 + 12),
			FONT_HERSHEY_DUPLEX, 0.30, box_color);
	}
}

void CImageProKimJiHyeonDoc::DnnAgeAndGenderRecognition()
{
	// 1. 얼굴 검출 모델 설정
	string detector_model_path = "D:/dnn/face_detection_yunet_2023mar.onnx";
	float detect_threshold = 0.9;
	float nms_threshold = 0.3;
	int top_k = 1;
	Size input_size(320, 320);
	int backend_id = DNN_BACKEND_OPENCV;
	int target_id = DNN_TARGET_CPU;

	Ptr<FaceDetectorYN> face_detector = FaceDetectorYN::create(detector_model_path,
		"", input_size, detect_threshold, nms_threshold,
		top_k, backend_id, target_id);
	face_detector->setInputSize(inputImg.size());
	face_detector->setTopK(1);

	// 2. 얼굴 검출
	Mat faces;
	face_detector->detect(inputImg, faces);
	if (faces.rows == 0) {
		AfxMessageBox("얼굴을 찾을 수 없습니다.");
		return;
	}

	// 3. 얼굴 영역 추출(검출된 영역에 30% 여백 추가, 정사각형 형태로 추출)
	Mat face = faces.row(0);
	float left = face.at<float>(0);
	float top = face.at<float>(1);
	float width = face.at<float>(2);
	float height = face.at<float>(3);
	float length = max(width, height);
	float new_width = length * 1.6;
	float new_height = length * 1.6;

	left = max(0.0, left - (new_width - width) / 2.0);
	top = max(0.0, top - (new_height - height) / 2.0);
	width = min((float)inputImg.cols - left, new_width);
	height = min((float)inputImg.rows - top, new_height);

	if (left < 0 || top < 0 || width <= 0 || height <= 0) {
		AfxMessageBox("얼굴을 찾을 수 없습니다.");
		return;
	}

	Mat face_img = inputImg(Rect((int)left, (int)top, (int)width, (int)height));
	resultImg = face_img.clone(); // 검출된 얼굴 영상을 resultImg에 복사

	// 4. 나이, 성별 검출 모델 불러오기
	Net age_net = readNet("D:/dnn/vgg_ilsvrc_16_age_chalearn_iccv2015.caffemodel",
		"D:/dnn/age.prototxt");
	Net gender_net = readNet("D:/dnn/vgg_ilsvrc_16_gender_imdb_wiki.caffemodel",
		"D:/dnn/gender.prototxt");

	// 5. 입력 준비
	Mat blob = blobFromImage(face_img, 1.0, Size(224, 224), Scalar(104, 117, 123));
	age_net.setInput(blob);

	// 6. 나이 추론 모델 실행
	Mat prob = age_net.forward(); // 101개의 확률값 반환

	// 7. 결과값 중 확률이 제일 큰 나이 선택
	int age;
	Point maxLoc;
	minMaxLoc(prob, 0, 0, 0, &maxLoc);
	age = maxLoc.x;

	// 8. 성별 인식 추론 모델 실행
	gender_net.setInput(blob);
	prob = gender_net.forward(); // 2개의 확률값 반환

	// 9. 결과값 중 확률이 제일 큰 성별 선택
	int gender;
	minMaxLoc(prob, 0, 0, 0, &maxLoc);
	gender = maxLoc.x;

	// 10. 결과 출력
	string label;
	if (gender == 0) {
		label = format("성별 : 여성, 나이 : %d", age);
	}
	else {
		label = format("성별 : 남성, 나이 : %d", age);
	}
	AfxMessageBox(label.c_str());
}

void CImageProKimJiHyeonDoc::DnnHumanParsing()
{
	static int model_initialized = false;
	static Net net;
	string model_path = "D:/dnn/lip_jppnet_384.pb";
	int backend = DNN_BACKEND_OPENCV; // GPU를 사용하지 않으면 실시간 동작 불가능
	int target = DNN_TARGET_CPU; // GPU를 사용하지 않으면 실시간 동작 불가능

	if (model_initialized == false) {
		net = readNet(model_path);
		net.setPreferableBackend(backend);
		net.setPreferableTarget(target);
		model_initialized = true;
	}

	// 입력 준비
	Mat blob = blobFromImage(inputImg, 1.0, Size(384, 384), Scalar(104.00698793, 116.66876762, 122.67891434));
	net.setInput(blob);
	Mat out = net.forward();

	// 20개 클래스에 대한 확률값을 받아옴
	Mat result[20];
	for (int k = 0; k < 20; k++)
		result[k] = Mat(384, 384, CV_32F, out.ptr<float>(0, k));

	// 각 픽셀별로 20개 클래스의 확률 값 중 제일 큰 것을 찾음
	Mat classMap(384, 384, CV_8UC1);
	for (int y = 0; y < 384; ++y) {
		for (int x = 0; x < 384; x++) {
			float maxVal = -1;
			int maxIdx = -1;
			for (int c = 0; c < 20; c++) {
				float val = result[c].at<float>(y, x);
				if (val > maxVal) {
					maxVal = val;
					maxIdx = c;
				}
			}
			classMap.at<uchar>(y, x) = maxIdx;
		}
	}

	// 각 픽셀의 색상을 가장 확률값이 큰 클래스의 색상으로 설정
	Vec3b colors[] = {
		Vec3b(0, 0, 0), Vec3b(128, 0, 0), Vec3b(255, 0, 0), Vec3b(0, 85, 0),
		Vec3b(51, 0, 170), Vec3b(85, 255, 0), Vec3b(0, 0, 85), Vec3b(0, 119, 221),
		Vec3b(85, 85, 0), Vec3b(0, 85, 85), Vec3b(85, 51, 0), Vec3b(52, 86, 128),
		Vec3b(0, 128, 0), Vec3b(0, 0, 255), Vec3b(51, 170, 221), Vec3b(0, 255, 255),
		Vec3b(85, 255, 170), Vec3b(170, 255, 85), Vec3b(255, 255, 0), Vec3b(255, 170, 0)
	};

	Mat colorMask(384, 384, CV_8UC3);
	for (int y = 0; y < 384; ++y) {
		for (int x = 0; x < 384; ++x) {
			int idx = classMap.at<uchar>(y, x);
			colorMask.at<Vec3b>(y, x) = colors[idx];
		}
	}

	// 원래 크기로 변환
	resize(colorMask, resultImg, inputImg.size());
}

void CImageProKimJiHyeonDoc::DnnImageSegmentation()
{
	static int model_initialzed = false;
	static Net net;
	static vector<string> classes;
	string model_path = "D:/dnn/Enet-model-best.net";
	string classes_path = "D:/dnn/Enet-classes.txt";

	if (model_initialzed == false) {
		ifstream ifs(classes_path.c_str());
		if (!ifs.is_open()) {
			AfxMessageBox("File not found: Enet-classes.txt");
			return;
		}
		string line;
		while (getline(ifs, line))
			classes.push_back(line);
		net = readNet(model_path);
		net.setPreferableBackend(DNN_BACKEND_OPENCV);
		net.setPreferableTarget(DNN_TARGET_CPU);
		model_initialzed = true;
	}

	Mat blob;
	blobFromImage(inputImg, blob, 1.0 / 255.0, Size(512, 256), Scalar(0, 0, 0), true, false);
	net.setInput(blob);
	Mat score = net.forward();

	const int chns = score.size[1]; // 검출된 영역 개수
	const int rows = score.size[2];
	const int cols = score.size[3];

	// 검출된 채널(영역)마다 색상 생성
	Mat segm;
	vector<Vec3b> colors;
	colors.push_back(Vec3b()); // 배경
	for (int i = 1; i < chns; ++i) {
		Vec3b color;
		for (int j = 0; j < 3; ++j)
			color[j] = (colors[i - 1][j] + rand() % 256) / 2;
		colors.push_back(color);
	}

	// 각 픽셀별로 어느 채널의 확률값이 제일 큰지 검사
	Mat maxCl = Mat::zeros(rows, cols, CV_8UC1); // 확률값이 큰 클래스 번호 저장
	Mat maxVal(rows, cols, CV_32FC1, score.ptr<float>(0, 0)); // 첫 번째 채널로 초기화

	for (int ch = 1; ch < chns; ch++) {
		Mat ch_score(rows, cols, CV_32FC1, score.ptr<float>(0, ch));
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				if (ch_score.at<float>(row, col) > maxVal.at<float>(row, col)) {
					maxVal.at<float>(row, col) = ch_score.at<float>(row, col);
					maxCl.at<uchar>(row, col) = ch;
				}
			}
		}
	}

	// 픽셀별로 제일 확률이 높은 채널 색상으로 색칠
	segm.create(rows, cols, CV_8UC3);
	for (int row = 0; row < rows; row++) {
		Vec3b* ptrSegm = segm.ptr<Vec3b>(row);
		for (int col = 0; col < cols; col++) {
			ptrSegm[col] = colors[maxCl.at<uchar>(row, col)];
		}
	}

	// 원래 크기로 변환
	resize(segm, segm, inputImg.size(), 0, 0, INTER_NEAREST);
	addWeighted(inputImg, 0.1, segm, 0.9, 0.0, resultImg);
}

void CImageProKimJiHyeonDoc::DnnObjectDetection()
{
	vector<string> classes;
	string line;
	ifstream ifs("D:/dnn/object_detection_classes_yolov3.txt");
	while (getline(ifs, line))
		classes.push_back(line);

	string model_path = "D:/dnn/yolov3.weights";
	string config_path = "D:/dnn/yolov3.cfg";

	resultImg = inputImg.clone();
	Net net = readNet(model_path, config_path);

	vector<String> outNames = net.getUnconnectedOutLayersNames();
	// yolo_82, yolo_94, yolo_106 의 3개의 출력 레이어가 있음

	Mat blob;
	blobFromImage(inputImg, blob, 1.0, Size(416, 416), Scalar(), true, false, CV_8U);
	net.setInput(blob, "", 1.0 / 255.0, Scalar(0, 0, 0));
	vector<Mat> outs;
	net.forward(outs, outNames); // 3개의 출력 레이어에 대해 추론 수행

	int classId;
	vector<vector<float>> confidences(80); // 80개의 클래스
	vector<vector<Rect>> boxes(80);

	// 네트워크 출력 : NxC 형태 N: 검출된 객체 수, C:85(영역정보 5개 값 + 80개 클래스 확률)
	// 첫5개 값 [중심점 x, 중심점 y, 넓이, 높이, 영역에 객체가 있을 확률]
	float confThreshold = 0.1; //

	for (int i = 0; i < outs.size(); i++) {
		for (int j = 0; j < outs[i].rows; j++) {
			Mat detection = outs[i].row(j);
			Mat pos = detection.colRange(0, 4); // 첫 4개의 값 추출
			float objectness = detection.at<float>(4); // 영역에 객체가 있을 확률
			Mat scores = detection.colRange(5, detection.cols); // 5번째 부터 80개 객체일 확률값
			Point classIdPoint;
			double classConf;
			minMaxLoc(scores, 0, &classConf, 0, &classIdPoint); // 80개 중 최대값 위치 검출
			float confidence = objectness * (float)classConf; // 최종 신뢰도 = 객체 확률 * 클래스 확률

			if (confidence > confThreshold) {
				// 첫4개 값 [중심점 x, 중심점 y, 넓이, 높이] : 0~1사이의 값으로
				// 전체 영상에서의 상대적인 위치값으로 표현
				int centerX = (int)(detection.at<float>(0) * inputImg.cols);
				int centerY = (int)(detection.at<float>(1) * inputImg.rows);
				int width = (int)(detection.at<float>(2) * inputImg.cols);
				int height = (int)(detection.at<float>(3) * inputImg.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classId = classIdPoint.x; // 확률값이 제일 큰 객체 번호
				// 해당 객체 목록에 확률값과 영역 정보 저장
				confidences[classId].push_back((float)confidence);
				boxes[classId].push_back(Rect(left, top, width, height));
			}
		}
	}

	// NMS(Non-Maximum Surpression) : 한 객체에 대하여 여러 개의 영역이 검출될 수
	// 있으므로 서로 겹치는 영역중에서 확률값이 제일 큰 것을 남기고 나머지는 삭제
	// 영역이 중복되는 검출 결과 중 확률이 가장 큰 것 만 남김
	// 확률이 가장 큰 영역을 저장
	for (int classId = 0; classId < 80; classId++) {
		if (!boxes[classId].empty()) {
			vector<int> nmsIndices;
			NMSBoxes(boxes[classId], confidences[classId], 0.1, 0.4, nmsIndices);

			for (int k = 0; k < nmsIndices.size(); k++) {
				Rect box = boxes[classId][nmsIndices[k]];
				float conf = confidences[classId][nmsIndices[k]];
				rectangle(resultImg, Point(box.x, box.y), Point(box.x + box.width, box.y + box.height), Scalar(0, 255, 0));
				string label = classes[classId] + ": " + format("%.2f", conf);
				putText(resultImg, label, Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
			}
		}
	}
}

void CImageProKimJiHyeonDoc::DnnPoseRecognition()
{
	const int POSE_PAIRS[17][2] = {
		{1,2}, {1,5}, {2,3}, {3,4}, {5,6}, {6,7},
		{1,8}, {8,9}, {9,10},
		{1,11}, {11,12}, {12,13},
		{1,0}, {0,14}, {14,16}, {0,15}, {15,17}
	};

	resultImg = inputImg.clone();
	string model_path = "D:/dnn/pose_iter_440000.caffemodel";
	string config_path = "D:/dnn/openpose_pose_coco.prototxt";
	Net net = readNet(model_path, config_path);
	Mat blob;
	blobFromImage(inputImg, blob, 1.0 / 255.0, Size(368, 368), Scalar(0, 0, 0), false, false);
	net.setInput(blob);
	Mat result = net.forward();

	// result 는 4차원임
	// - 영상수 x 관절수 x 46 x 46 형태로 출력됨
	int H = 46; // 영상을 46 x 46 개의 영역으로 나누어 관절 검출
	int W = 46;
	int npairs = 17, nparts = 18; // 18개 관절이 검출됨
	vector<Point> points(18);

	// 관절의 위치를 검출
	for (int n = 0; n < nparts; n++) {
		Mat prob(H, W, CV_32F, result.ptr<float>(0, n)); // 관절이 존재할 확률 맵 구성
		Point maxLoc;
		double maxVal;
		minMaxLoc(prob, 0, &maxVal, 0, &maxLoc); // 최대값 위치를 찾음
		if (maxVal > 0.1) points[n] = maxLoc;
		else points[n] = Point(-1, -1);
	}

	// 영상 크기에 맞게 확대
	float SX = float(inputImg.cols) / W;
	float SY = float(inputImg.rows) / H;

	// 연결된 관절을 찾아서 선을 그림
	for (int n = 0; n < npairs; n++) {
		Point2f a = points[POSE_PAIRS[n][0]]; // 연결된 관절 번호를 가져옴
		Point2f b = points[POSE_PAIRS[n][1]];

		if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0) // 검출 위치가 음수이면 건너뜀
			continue;

		a.x *= SX; a.y *= SY; // 영상 크기에 맞게 확대
		b.x *= SX; b.y *= SY;
		line(resultImg, a, b, Scalar(0, 200, 0), 2);
		circle(resultImg, a, 3, Scalar(0, 0, 200), -1);
		circle(resultImg, b, 3, Scalar(0, 0, 200), -1);
	}
}

void CImageProKimJiHyeonDoc::DnnDigitsRecognition()
{
	string model_path = "D:/dnn/lenet.caffemodel";
	string config_path = "D:/dnn/lenet.prototxt";
	float confThreshold = 0.7;

	Mat labels, stats, centroids;
	Point position;
	Rect getRectangle;
	bool ifDrawingBox = false;
	int classId = 0;
	double probability = 0;
	Rect basicRect = Rect(0, 0, inputImg.cols, inputImg.rows);

	Net net = readNet(model_path, config_path);
	Mat image = inputImg.clone();

	resultImg = inputImg.clone();
	cvtColor(image, image, COLOR_BGR2GRAY);
	blur(image, image, Size(3, 3));
	adaptiveThreshold(image, image, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 7);
	bitwise_not(image, image); // 배경이 0인 영상으로 변환

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(image, image, element, Point(-1, -1), 1);

	int nccomps = connectedComponentsWithStats(image, labels, stats, centroids);

	for (int i = 1; i < nccomps; i++) { // 0번은 백그라운드이므로 1번에서 시작
		ifDrawingBox = false;

		if (stats.at<int>(i, CC_STAT_AREA) > 80 && stats.at<int>(i, CC_STAT_AREA) < 3000) {
			ifDrawingBox = true;
			int margin = stats.at<int>(i, CC_STAT_HEIGHT) / 4;
			getRectangle = Rect(stats.at<int>(i, CC_STAT_LEFT) - margin,
				stats.at<int>(i, CC_STAT_TOP) - margin,
				stats.at<int>(i, CC_STAT_WIDTH) + 2 * margin,
				stats.at<int>(i, CC_STAT_HEIGHT) + 2 * margin);
			getRectangle &= basicRect; // 중첩된 영역에 대한 사각형 반환
			// 영상 범위를 벗어나지 않도록 하기 위한 작업

			if (ifDrawingBox && !getRectangle.empty()) {
				Mat roi = image(getRectangle);
				Mat inputBlob = blobFromImage(roi, 1.0, Size(28, 28));
				net.setInput(inputBlob);
				Mat pred = net.forward();
				// 0부터 9까지의 숫자일 확률값 반환
				Point classNumber;
				minMaxLoc(pred, NULL, &probability, NULL, &classNumber);
				classId = classNumber.x;
				if (probability < confThreshold) continue;

				rectangle(resultImg, getRectangle, Scalar(128, 255, 128), 2);
				position = Point(getRectangle.br().x - 7, getRectangle.br().y + 25);
				putText(resultImg, to_string(classId), position, FONT_HERSHEY_SIMPLEX, 1.0, Scalar(128, 128, 255), 2);
			}
		}
	}
}

#pragma warning(disable: 4996) // td_model 변수 선언에 대한 오류 비활성화
void CImageProKimJiHyeonDoc::DnnEnglishWordRecognition()
{
	static int model_initialzed = false;
	static TextDetectionModel_DB td_model;
	static Net tr_model;
	string tr_modelPath = "D:/dnn/text_recognition_CRNN_CH_2021sep.onnx";
	string td_modelPath = "D:/dnn/text_detection_en_ppocrv3_2023may.onnx";
	Size inpSize(736, 736);
	float binThresh = 0.3; // DBNet은 각 픽셀이 텍스트일 확률을 예측. 확률 맵을 텍스트 vs 비텍스트로 나누는 기준값
	float polyThresh = 0.5; // DBNet은 텍스트 영역을 확률 맵으로 예측 후, 임계값 이상의 점들을 폴리곤(다각형) 형태로 변환
	int maxCand = 200;      // 발견할 텍스트의 최대 개수
	double unRatio = 2.0;   // 검출된 텍스트 영역의 경계 확장 비율

	if (model_initialzed == false) {
		td_model = TextDetectionModel_DB(readNet(td_modelPath));
		td_model.setPreferableBackend(DNN_BACKEND_OPENCV);
		td_model.setPreferableTarget(DNN_TARGET_CPU);
		td_model.setBinaryThreshold(binThresh);
		td_model.setPolygonThreshold(polyThresh);
		td_model.setUnclipRatio(unRatio);
		td_model.setMaxCandidates(maxCand);
		td_model.setInputParams(1.0 / 255.0, inpSize, Scalar(122.67891434, 116.66876762, 104.00698793));

		tr_model = readNet(tr_modelPath);
		tr_model.setPreferableBackend(DNN_BACKEND_OPENCV);
		tr_model.setPreferableTarget(DNN_TARGET_CPU);
		model_initialzed = true;
	}

	vector<string> charset = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"!", "\"", "#", "$", "%", "&", "(", ")", "*", "+", ",", "-", ".", "/",
		":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`",
		"{", "|", "}", "~"
	};

	Size inputSize = Size(100, 32);
	Mat targetVertices = Mat(4, 1, CV_32FC2);
	targetVertices.row(0) = Vec2f(0, inputSize.height - 1);
	targetVertices.row(1) = Vec2f(0, 0);
	targetVertices.row(2) = Vec2f(inputSize.width - 1, 0);
	targetVertices.row(3) = Vec2f(inputSize.width - 1, inputSize.height - 1);

	int originalW = inputImg.cols;
	int originalH = inputImg.rows;
	double scaleHeight = originalH / double(inpSize.height);
	double scaleWidth = originalW / double(inpSize.width);
	Mat image;
	vector<vector<Point>> pt;
	vector<float> confidence;

	resize(inputImg, image, inpSize);
	td_model.detect(image, pt, confidence); // 텍스트 영역 검출

	resultImg = inputImg.clone();
	if (pt.size() > 0 && confidence.size() > 0) {
		for (int k = 0; k < pt.size(); k++) {
			vector<Point> box = pt[k];
			Mat result = Mat(box);

			Mat vertices;
			result.convertTo(vertices, CV_32FC2);
			Mat rotationMatrix = getPerspectiveTransform(vertices, targetVertices);
			Mat cropped; // 텍스트 영역을 100x32 크기의 영상으로 변환
			warpPerspective(image, cropped, rotationMatrix, inputSize);
			Mat blob = blobFromImage(cropped, 1.0 / 127.5, inputSize, Scalar::all(127.5));

			tr_model.setInput(blob);
			Mat outputBlob = tr_model.forward();
			// 1채널 25x96 확률 행렬 형태로 변환 (25글자이하의 단어 인식)
			Mat character(25, 96, CV_32F, outputBlob.ptr<float>());
			string text("");
			for (int i = 0; i < character.rows; i++) { // 각 글자마다 최대 확률값 위치 탐색
				Point maxIdx;
				minMaxLoc(character.row(i), 0, 0, 0, &maxIdx);
				if (maxIdx.x != 0) text += charset[maxIdx.x - 1];
				else text += "-";
			}

			// 한 글자가 여러 번 중복해서 인식되는 경우가 있으므로 중복 제거 필요
			string textFilter("");
			for (int i = 0; i < text.length(); i++) {
				if (text[i] != '-' && !(i > 0 && text[i] == text[i - 1]))
					textFilter += text[i];
			}
			text = "\"" + textFilter + "\"";

			vector<Point> pts = box;
			for (int i = 0; i < 4; i++) {
				pts[i].x = int(pts[i].x * scaleWidth);
				pts[i].y = int(pts[i].y * scaleHeight);
			}
			for (int i = 0; i < 3; i++)
				line(resultImg, pts[i], pts[i + 1], Scalar(0, 255, 0), 2);
			line(resultImg, pts[3], pts[0], Scalar(0, 255, 0), 2);
			putText(resultImg, text, pts[0], FONT_HERSHEY_COMPLEX, 0.8, Scalar(0, 0, 255), 1);
		}
	}
}

void CImageProKimJiHyeonDoc::DnnColorization()
{
	static float hull_pts[] = {
		-90.,-90.,-90.,-90.,-90.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
		-70.,-70.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,
		-50.,-50.,-50.,-50.,-50.,-50.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-30.,
		-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,
		-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
		-10.,-10.,-10.,-10.,-10.,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.,10.,10,10,10,10,10,10.,
		10.,10.,10.,10.,10,10,10,10.,10.,10.,10.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,
		20.,20.,20.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,40.,40.,40.,40.,
		40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,
		50.,50.,50.,50.,50.,50.,50.,50.,50,60,60.,60.,60,60,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,
		60.,60.,60.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,80.,80.,80.,
		80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,
		-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,-110.,
		-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,
		-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,-90.,
		-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,-80.,
		-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,-70.,
		-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,-60.,
		-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,-50.,
		-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,-40.,
		-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,-30.,
		-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,-20.,
		-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,
		20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,20.,
		30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,30.,
		40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,40.,
		50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,50.,
		60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,60.,
		70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,70.,
		80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,80.,
		90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,90.,
		100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100
	};

	string model_path = "D:/dnn/colorization_release_v2.caffemodel";
	string config_path = "D:/dnn/colorization_deploy_v2.prototxt";

	const int W_in = 224;
	const int H_in = 224;

	Net net = readNet(config_path, model_path);

	int sz[] = { 2, 313, 1, 1 };
	const Mat pts_in_hull(4, sz, CV_32F, hull_pts);
	// class8_ab 레이어가 313개의 ab 색상 중심 정보를 가지고 있어야 하는데 모델에
	// 내장되어 있지 않고 직접 넣어주어야 함
	Ptr<Layer> class8_ab = net.getLayer("class8_ab");
	class8_ab->blobs.push_back(pts_in_hull);

	// conv8_313_rh 레이어는 확률 분포를 조정하는 rescaling bias 레이어인데 고정된
	// 값 2.606을 사용(실험으로 구한 값)
	Ptr<Layer> conv8_313_rh = net.getLayer("conv8_313_rh");
	conv8_313_rh->blobs.push_back(Mat(1, 313, CV_32F, Scalar(2.606)));

	Mat gray = inputImg.clone();
	Mat img;
	cvtColor(gray, img, COLOR_GRAY2RGB); // RGB 영상으로 변환

	Mat lab, L, input;
	img.convertTo(img, CV_32F, 1.0 / 255); // 픽셀값을 0에서 1사이로 변환
	cvtColor(img, lab, COLOR_RGB2Lab); // Lab 컬러로 변환
	extractChannel(lab, L, 0); // 0번 채널을 추출
	resize(L, input, Size(W_in, H_in));
	input -= 50;

	// L 채널에 대하여 추론 적용
	Mat inputBlob = blobFromImage(input);
	net.setInput(inputBlob);
	Mat result = net.forward();

	// 추론 결과에서 a 채널과 b 채널 결과 추출
	Size siz(result.size[2], result.size[3]);
	Mat a = Mat(siz, CV_32F, result.ptr<float>(0, 0));
	Mat b = Mat(siz, CV_32F, result.ptr<float>(0, 1));
	resize(a, a, img.size());
	resize(b, b, img.size());

	// BGR컬러로 변환
	Mat chn[] = { L, a, b };
	merge(chn, 3, lab);
	cvtColor(lab, resultImg, COLOR_Lab2BGR);
	resultImg.convertTo(resultImg, CV_8U, 255.0);
}

bool CImageProKimJiHyeonDoc::detect_face_and_landmarks(Mat& image, Rect& out_box, vector<Point2f>& out_landmarks)
{
	static int model_initialized = false;
	static Ptr<FaceDetectorYN> detector;
	string model_path = "D:/dnn/face_detection_yunet_2023mar.onnx";
	float conf_thresh = 0.3;
	float scoreThreshold = 0.9;
	float nmsThreshold = 0.3;
	int topK = 5000;
	int thickness = 2;

	// 1. 모델 초기화
	if (model_initialized == false) {
		detector = FaceDetectorYN::create(model_path, "", Size(320, 320), scoreThreshold, nmsThreshold, topK, DNN_BACKEND_CUDA, DNN_TARGET_CUDA);
		model_initialized = true;
	}
	detector->setInputSize(Size(image.cols, image.rows));

	// 2. 얼굴 검출 및 랜드마크 추출
	Mat faces;
	detector->detect(image, faces);

	// 3. 얼굴이 검출되지 않으면 종료
	if (faces.rows == 0) return false;

	// 4. 가장 확률이 높은 얼굴 선택
	bool found = false;
	float best_score = 0.f;
	for (int i = 0; i < faces.rows; i++) {
		// 첫 4개 값: bbox, 다음 10개 값: 5개 랜드마크(x,y), 마지막 값: 신뢰도
		const float* data = faces.ptr<float>(i);
		float score = data[14];
		// 신뢰도가 임계값보다 낮으면 무시
		if (score < conf_thresh) continue;
		// bbox: 첫 4개 값
		Rect face_box(data[0], data[1], data[2], data[3]);

		// 5개 랜드마크: 다음 10개 값
		vector<Point2f> lm;
		for (int j = 0; j < 5; ++j) {
			float lx = data[4 + j * 2];
			float ly = data[4 + j * 2 + 1];
			lm.emplace_back(lx, ly); // emplace: 자리를 잡다
		}

		// 가장 확률이 높은 얼굴 선택
		if (score > best_score) {
			best_score = score;
			out_box = face_box;
			out_landmarks = lm;
			found = true;
		}
	}
	return found;
}

Mat CImageProKimJiHyeonDoc::align_face(Mat& image, vector<Point2f>& src_pts, Mat& mat, int output_size)
{
	// 기준이 되는 랜드마크 좌표(왼쪽 눈, 오른쪽 눈, 코, 왼쪽 입꼬리, 오른쪽 입꼬리)
	vector<Point2f> dst_pts = { { 192.98138, 239.94708 },
		{318.90277, 240.1936 },
		{ 256.63416, 314.01935 },
		{ 201.26117, 371.41043 },
		{ 313.08905, 371.15118 } };

	// 2x3 어파인 변환 행렬 계산
	mat = estimateAffinePartial2D(src_pts, dst_pts);

	// 얼굴 정렬 및 크기 조정
	Mat aligned;
	warpAffine(image, aligned, mat, Size(512, 512), INTER_LINEAR, BORDER_REFLECT);
	resize(aligned, aligned, Size(output_size, output_size), 0, 0, INTER_LINEAR);
	return aligned;
}

void CImageProKimJiHyeonDoc::DnnFaceSwap()
{
	static int model_initialized = false;
	static Net arcface_net;
	static Net simswap_net;
	static Mat id_vector;
	string arcface_model_path = "D:/dnn/arcface_model.onnx";
	string simswap_model_path = "D:/dnn/simswap_simplified.onnx";
	string out_path = "D:/images/out.mp4";

	// 1. 모델 초기화
	if (model_initialized == false) {
		arcface_net = readNet(arcface_model_path);
		simswap_net = readNet(simswap_model_path);
		arcface_net.setPreferableBackend(DNN_BACKEND_CUDA);
		arcface_net.setPreferableTarget(DNN_TARGET_CUDA);
		simswap_net.setPreferableBackend(DNN_BACKEND_CUDA);
		simswap_net.setPreferableTarget(DNN_TARGET_CUDA);
		model_initialized = true;
	}

	// 교체할 얼굴 영상에서 얼굴 검출 및 특징 벡터 추출
	if (new_swap_image_loaded == true) {
		Rect box;
		vector<Point2f> Im;
		bool found = detect_face_and_landmarks(inputImg, box, Im);
		if (!found) {
			throw runtime_error("교체용 얼굴 영상에서 얼굴을 찾을 수 없습니다.");
		}

		// 3. SimSwap 입력을 위한 얼굴 정렬 (112x112) :
		Mat mat; // Im(눈,코,입 위치)와 얼굴 정렬 행렬 mat도 계산함
		Mat aligned = align_face(inputImg, Im, mat, 112);

		// 교체 얼굴 이미지 복사 및 확인
		faceSwapImg = aligned.clone();
		resize(faceSwapImg, faceSwapImg, Size(256, 256), 0, 0, INTER_LINEAR);

		// 4. SimSwap 모델을 위한 입력 전처리 : RGB, [-1,1]
		aligned.convertTo(aligned, CV_32F, 1 / 255.0);
		Scalar imageMean = Scalar(0.406, 0.456, 0.485);
		Scalar imageStd = Scalar(0.225, 0.224, 0.229);
		aligned -= imageMean;
		aligned /= imageStd;
		cvtColor(aligned, aligned, COLOR_BGR2RGB);
		Mat arc_blob = blobFromImage(aligned); // 1x3xHxW
		arcface_net.setInput(arc_blob);

		// ArcFace 모델 추론 실행 (512 차원 특징 벡터 추출)
		Mat emb = arcface_net.forward();
		// L2 정규화 (simswap 모델에서 요구): 벡터의 크기가 1이 되도록 정규화
		normalize(emb, id_vector, 1.0, 0.0, NORM_L2); // 1x512
		new_swap_image_loaded = false;
	}

	// 출력 동영상 파일 준비
	if (!writer.isOpened()) {
		writer = VideoWriter(out_path, VideoWriter::fourcc('H', '2', '6', '4'), 30.0, Size(inputImg2.cols, inputImg2.rows));
	}

	// 2. 입력 영상에서 얼굴 검출 및 랜드마크 추출
	Mat output_frame = inputImg2.clone();
	Rect box;
	vector<Point2f> Im;
	bool found = detect_face_and_landmarks(inputImg2, box, Im);
	if (!found) {
		writer.write(inputImg2);
		resultImg = inputImg2.clone();
		return;
	}

	// 3. SimSwap 입력을 위한 얼굴 정렬 (512x512) :
	Mat mat; // Im(눈,코,입 위치)와 얼굴 정렬 행렬 mat도 계산함
	Mat aligned_target = align_face(inputImg2, Im, mat, 512);

	// 4. SimSwap 모델을 위한 입력 전처리 : RGB, [0,1]
	Mat simswap_input = blobFromImage(aligned_target, 1.0 / 255.0, Size(), Scalar(0, 0, 0), true, false);

	// 5. SimSwap 모델 입력 설정
	simswap_net.setInput(simswap_input, "img");
	simswap_net.setInput(id_vector, "id_vector");

	// 6. SimSwap 모델 추론 실행
	Mat simswap_out = simswap_net.forward(); // 1x3x512x512 float32

	// 7. SimSwap 출력 후처리
	Mat R = Mat(Size(512, 512), CV_32F, simswap_out.ptr<float>(0, 0));
	Mat G = Mat(Size(512, 512), CV_32F, simswap_out.ptr<float>(0, 1));
	Mat B = Mat(Size(512, 512), CV_32F, simswap_out.ptr<float>(0, 2));
	Mat chn[] = { B, G, R };
	Mat swapped_face;
	merge(chn, 3, swapped_face);
	swapped_face.convertTo(swapped_face, CV_8U, 255.0);

	// 8. 원래 영상과 교체된 얼굴 영상 혼합
	// 입력 영상에서 얼굴을 정렬할때 사용한 행렬의 역행렬 계산 (2x3)
	Mat mat_rev = Mat::zeros(2, 3, CV_64F);
	double a = mat.at<double>(0, 0), b = mat.at<double>(0, 1), c = mat.at<double>(0, 2);
	double d = mat.at<double>(1, 0), e = mat.at<double>(1, 1), f = mat.at<double>(1, 2);
	double div1 = a * e - b * d;
	if (div1 == 0) div1 = 1e-8;
	mat_rev.at<double>(0, 0) = e / div1;
	mat_rev.at<double>(0, 1) = -b / div1;
	mat_rev.at<double>(0, 2) = -(c * e - b * f) / div1;
	double div2 = b * d - a * e;
	if (div2 == 0) div2 = 1e-8;
	mat_rev.at<double>(1, 0) = d / div2;
	mat_rev.at<double>(1, 1) = -a / div2;
	mat_rev.at<double>(1, 2) = -(c * d - a * f) / div2;

	// 흰 이미지 생성
	Mat img_white(512, 512, CV_32F, Scalar(255.0));

	// 교체된 얼굴 영상과 흰 이미지에 대하여 역행렬을 사용하여 원래 영상 크기로 워핑
	Size orisize(inputImg2.cols, inputImg2.rows);
	Mat target_image;
	warpAffine(swapped_face, target_image, mat_rev, orisize, INTER_LINEAR, BORDER_CONSTANT);
	Mat warped_white;
	warpAffine(img_white, warped_white, mat_rev, orisize, INTER_LINEAR, BORDER_CONSTANT);

	// 마스크 영상 생성
	warped_white.setTo(255, warped_white > 20);
	Mat img_mask = warped_white;

	// 마스크 영상 침식
	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
	erode(img_mask, img_mask, kernel, Point(-1, -1), 1);

	// 마스크 영상을 흐리게 하기
	Size blur_size(7, 7);
	GaussianBlur(img_mask, img_mask, blur_size, 0);

	// 마스크 영상 정규화 [0,1]
	Mat img_mask_f;
	img_mask.convertTo(img_mask_f, CV_32F, 1.0 / 255.0);

	// 혼합할 영상을 float32로 변환
	Mat target_image_float;
	target_image.convertTo(target_image_float, CV_32F, 1.0);

	// 원래 영상도 float32로 변환
	Mat img;
	inputImg2.convertTo(img, CV_32F); // HxWx3

	// 마스크 영상을 3채널로 복사
	Mat mask_3;
	vector<Mat> out_channels(3, img_mask_f);
	merge(out_channels, mask_3); // HxWx3

	// 혼합 : result = mask * target + (1-mask) * original
	img = mask_3.mul(target_image_float) + (Scalar::all(1.0) - mask_3).mul(img);
	img.convertTo(resultImg, CV_8U); // uint8
	writer.write(resultImg);
}

void CImageProKimJiHyeonDoc::DnnLaneDetection()
{
	static int model_initialized = false;
	static Net net;
	int griding_num = 200;
	int img_w = 800;
	int img_h = 288;
	int num_lanes = 4;
	int num_classes = griding_num + 1; // 200 + 1 (배경 클래스)
	int num_rows = 18;
	vector<int> row_anchor = { 121, 131, 141, 150, 160, 170, 180, 189, 199, 209, 219, 228,
		238, 248, 258, 267, 277, 287 };

	string modelPath = "D:/dnn/ultra_falst_lane_detection_culane_288x800.onnx";
	int backend_id = DNN_BACKEND_CUDA; //DNN_BACKEND_OPENCV;
	int target_id = DNN_TARGET_CUDA; // DNN_TARGET_CPU;

	// 1. 모델 초기화
	if (model_initialized == false) {
		net = readNet(modelPath);
		net.setPreferableBackend(backend_id);
		net.setPreferableTarget(target_id);
		model_initialized = true;
	}

	// 2. 입력 영상 전처리
	Scalar imageMean = Scalar(0.406, 0.456, 0.485);
	Scalar imageStd = Scalar(0.225, 0.224, 0.229);
	Mat img;
	inputImg.convertTo(img, CV_32F, 1.0 / 255.0);
	resize(img, img, Size(img_w, img_h));
	img -= imageMean;
	img /= imageStd;
	Mat blob = blobFromImage(img, 1.0, Size(), Scalar(), true);
	net.setInput(blob);

	// 3. 추론 실행
	Mat result = net.forward(); // shape: (1, 201, 18, 4)

	// 4. 후처리: 각 행(row_anchor)에서 각 차선(lane)의 클래스(200개 그리드 + 배경) 예측
	int dims[] = { 201, 18, 4 };
	Mat output_mat(3, dims, CV_32F, result.ptr<float>());
	vector<vector<Point>> lanes_points;
	vector<bool> lanes_detected;

	// 각 차선에 대해
	for (int lane = 0; lane < num_lanes; ++lane) {
		vector<Point> points;
		// 각 행에 대해
		for (int row = 0; row < num_rows; ++row) {
			// lane 차선의 row 행의 201개 확률값 받아오기
			// 출력 텐서 인덱싱 : [1, 201, 18, 4]
			Mat logits_mat(1, num_classes, CV_32F);
			for (int c = 0; c < num_classes; ++c)
				logits_mat.at<float>(0, c) = output_mat.at<float>(c, row, lane);

			// 201 개의 확률값 중에서 최대값 인덱스 찾기
			Point max_loc;
			minMaxLoc(logits_mat, 0, 0, 0, &max_loc);
			int class_idx = max_loc.x;

			// 배경 클래스가 아니면, x 좌표 계산
			if (class_idx > 0) { // 0은 배경
				float x = class_idx * (float(img_w) / num_classes);
				int y = row_anchor[row];
				points.emplace_back(Point((int)x, y));
			}
		}

		// 차선 좌표 저장
		if (!points.empty()) {
			lanes_points.push_back(points);
			lanes_detected.push_back(true);
		}
		else {
			lanes_points.push_back(vector<Point>());
			lanes_detected.push_back(false);
		}
	}

	// 5. 시각화
	Mat vis = inputImg.clone();
	resize(vis, vis, Size(img_w, img_h));
	Mat lane_segment_img = vis.clone();

	// 각 차선의 점들을 색을 달리하여 시각화
	Scalar lane_colors[] = { Scalar(0,0,255), Scalar(0,255,0), Scalar(255,0,0), Scalar(0,255,255) };
	for (int i = 0; i < lanes_points.size(); ++i) {
		Scalar color = Scalar(0, 255, 0);
		if (!lanes_detected[i]) color = Scalar(0, 0, 255);
		for (int k = 0; k < lanes_points[i].size(); k++) {
			Point pt = lanes_points[i][k];
			circle(vis, pt, 3, lane_colors[i], -1);
		}
	}

	// 자동차 앞의 왼쪽 차선과 오른쪽 차선 사이를 채우기
	// 유효한 점이 충분할 때만
	if (lanes_points.size() >= 3) {
		vector<Point> left_lane = lanes_points[1];
		vector<Point> right_lane = lanes_points[2];
		if (left_lane.size() >= 2 || right_lane.size() >= 2) {
			// 상단부터 하단으로 이어 붙이기 : left + reverse(right)
			vector<Point> polygon;
			polygon.insert(polygon.end(), left_lane.begin(), left_lane.end());
			polygon.insert(polygon.end(), right_lane.rbegin(), right_lane.rend());
			vector<vector<Point>> polys = { polygon };
			fillPoly(lane_segment_img, polys, Scalar(255, 191, 0), LINE_AA);
			addWeighted(vis, 0.7, lane_segment_img, 0.3, 0, vis);
		}
	}

	resize(vis, resultImg, inputImg.size());
}

void CImageProKimJiHyeonDoc::DnnFormulaRecognition()
{
	if (inputImg.empty()) {
		AfxMessageBox("이미지를 먼저 로드하세요.");
		return;
	}

	// 1. OCR로 수식 텍스트 추출
	static int model_initialized = false;
	static TextDetectionModel_DB td_model;
	static Net tr_model;
	string tr_modelPath = "D:/dnn/text_recognition_CRNN_CH_2021sep.onnx";
	string td_modelPath = "D:/dnn/text_detection_en_ppocrv3_2023may.onnx";
	Size inpSize(736, 736);
	float binThresh = 0.3;
	float polyThresh = 0.5;
	int maxCand = 200;
	double unRatio = 2.0;

	if (model_initialized == false) {
		td_model = TextDetectionModel_DB(readNet(td_modelPath));
		td_model.setPreferableBackend(DNN_BACKEND_OPENCV);
		td_model.setPreferableTarget(DNN_TARGET_CPU);
		td_model.setBinaryThreshold(binThresh);
		td_model.setPolygonThreshold(polyThresh);
		td_model.setUnclipRatio(unRatio);
		td_model.setMaxCandidates(maxCand);
		td_model.setInputParams(1.0 / 255.0, inpSize, Scalar(122.67891434, 116.66876762, 104.00698793));

		tr_model = readNet(tr_modelPath);
		tr_model.setPreferableBackend(DNN_BACKEND_OPENCV);
		tr_model.setPreferableTarget(DNN_TARGET_CPU);
		model_initialized = true;
	}

	vector<string> charset = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"!", "\"", "#", "$", "%", "&", "(", ")", "*", "+", ",", "-", ".", "/",
		":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`",
		"{", "|", "}", "~"
	};

	Size inputSize = Size(100, 32);
	Mat targetVertices = Mat(4, 1, CV_32FC2);
	targetVertices.row(0) = Vec2f(0, inputSize.height - 1);
	targetVertices.row(1) = Vec2f(0, 0);
	targetVertices.row(2) = Vec2f(inputSize.width - 1, 0);
	targetVertices.row(3) = Vec2f(inputSize.width - 1, inputSize.height - 1);

	Mat image;
	vector<vector<Point>> pt;
	vector<float> confidence;

	resize(inputImg, image, inpSize);
	td_model.detect(image, pt, confidence);

	resultImg = inputImg.clone();
	string formula_text = "";

	if (pt.size() > 0 && confidence.size() > 0) {
		// 모든 텍스트 영역에서 수식 추출
		for (int k = 0; k < pt.size(); k++) {
			vector<Point> box = pt[k];
			Mat result = Mat(box);

			Mat vertices;
			result.convertTo(vertices, CV_32FC2);
			Mat rotationMatrix = getPerspectiveTransform(vertices, targetVertices);
			Mat cropped;
			warpPerspective(image, cropped, rotationMatrix, inputSize);
			Mat blob = blobFromImage(cropped, 1.0 / 127.5, inputSize, Scalar::all(127.5));

			tr_model.setInput(blob);
			Mat outputBlob = tr_model.forward();
			Mat character(25, 96, CV_32F, outputBlob.ptr<float>());
			string text("");
			for (int i = 0; i < character.rows; i++) {
				Point maxIdx;
				minMaxLoc(character.row(i), 0, 0, 0, &maxIdx);
				if (maxIdx.x != 0) text += charset[maxIdx.x - 1];
				else text += "-";
			}

			// 중복 제거
			string textFilter("");
			for (int i = 0; i < text.length(); i++) {
				if (text[i] != '-' && !(i > 0 && text[i] == text[i - 1]))
					textFilter += text[i];
			}
			formula_text += textFilter + " ";
		}
	}

	// 공백 제거 및 정리
	if (formula_text.empty()) {
		putText(resultImg, "수식을 인식할 수 없습니다.", Point(10, 30),
			FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
		return;
	}

	// 수식 정규화
	string normalized = formula_text;
	// 공백 제거
	normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());
	// 특수 문자 변환 (string::replace 사용)
	size_t pos = 0;
	while ((pos = normalized.find('×', pos)) != string::npos) {
		normalized.replace(pos, 1, "*");
		pos++;
	}
	pos = 0;
	while ((pos = normalized.find('÷', pos)) != string::npos) {
		normalized.replace(pos, 1, "/");
		pos++;
	}
	// 지수 변환 (문자열 치환)
	pos = 0;
	while ((pos = normalized.find('²', pos)) != string::npos) {
		normalized.replace(pos, 1, "^2");
		pos += 2;
	}
	pos = 0;
	while ((pos = normalized.find('³', pos)) != string::npos) {
		normalized.replace(pos, 1, "^3");
		pos += 2;
	}
	
	// 제곱근 변환 (√x → sqrt(x))
	normalized = preprocessSquareRoot(normalized);
	
	// 절댓값 변환 (|x| → abs(x))
	normalized = preprocessAbsoluteValue(normalized);
	
	// 함수명 정규화 (대소문자 통일)
	normalized = normalizeFunctionNames(normalized);

	// 등호 처리 (방정식인 경우)
	size_t equal_pos = normalized.find('=');
	if (equal_pos != string::npos) {
		// 등호가 있으면 좌변과 우변을 각각 계산
		string left_side = normalized.substr(0, equal_pos);
		string right_side = normalized.substr(equal_pos + 1);
		
		double left_result = 0.0, right_result = 0.0;
		bool left_success = false, right_success = false;
		
		try {
			left_result = evaluateSimpleExpression(left_side);
			left_success = true;
		}
		catch (...) {
			left_success = false;
		}
		
		try {
			right_result = evaluateSimpleExpression(right_side);
			right_success = true;
		}
		catch (...) {
			right_success = false;
		}
		
		// 결과 시각화
		string display_text = "Formula: " + formula_text;
		putText(resultImg, display_text, Point(10, 30),
			FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
		
		if (left_success && right_success) {
			string result_text = format("Left: %.2f, Right: %.2f", left_result, right_result);
			putText(resultImg, result_text, Point(10, 60),
				FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
			
			// 등식이 성립하는지 확인
			if (abs(left_result - right_result) < 0.01) {
				putText(resultImg, "Equation is TRUE", Point(10, 90),
					FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
			}
			else {
				putText(resultImg, "Equation is FALSE", Point(10, 90),
					FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
			}
		}
		else {
			putText(resultImg, "Calculation Error", Point(10, 60),
				FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
		}
		return;
	}

	// 등호가 없는 경우 (일반 계산)
	double result = 0.0;
	bool calculation_success = false;
	
	try {
		// 간단한 계산기 구현 (우선순위 고려)
		result = evaluateSimpleExpression(normalized);
		calculation_success = true;
	}
	catch (...) {
		calculation_success = false;
	}

	// 결과 시각화
	string display_text = "Formula: " + formula_text;
	putText(resultImg, display_text, Point(10, 30),
		FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);

	if (calculation_success) {
		string result_text = format("Result: %.2f", result);
		putText(resultImg, result_text, Point(10, 60),
			FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
	}
	else {
		putText(resultImg, "Calculation Error", Point(10, 60),
			FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
	}
}

// 고급 수식 인식 함수 (구조화된 결과 반환)
FormulaRecognitionResult CImageProKimJiHyeonDoc::DnnFormulaRecognitionAdvanced()
{
	FormulaRecognitionResult result;
	
	if (inputImg.empty()) {
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}

	// 1. OCR로 수식 텍스트 추출
	static int model_initialized = false;
	static TextDetectionModel_DB td_model;
	static Net tr_model;
	string tr_modelPath = "C:/dnn/text_recognition_CRNN_CH_2021sep.onnx";
	string td_modelPath = "C:/dnn/text_detection_en_ppocrv3_2023may.onnx";
	Size inpSize(736, 736);
	float binThresh = 0.3;
	float polyThresh = 0.5;
	int maxCand = 200;
	double unRatio = 2.0;

	if (model_initialized == false) {
		// 파일 존재 여부 확인
		ifstream td_file(td_modelPath);
		if (!td_file.good()) {
			string error_msg = "모델 파일을 찾을 수 없습니다:\n" + td_modelPath + "\n\n파일 경로를 확인해주세요.";
			AfxMessageBox(CString(error_msg.c_str()));
			result.original_text = "";
			result.confidence = 0.0;
			result.confidence_rate = 0.0;
			result.calculation_success = false;
			return result;
		}
		td_file.close();

		ifstream tr_file(tr_modelPath);
		if (!tr_file.good()) {
			string error_msg = "모델 파일을 찾을 수 없습니다:\n" + tr_modelPath + "\n\n파일 경로를 확인해주세요.";
			AfxMessageBox(CString(error_msg.c_str()));
			result.original_text = "";
			result.confidence = 0.0;
			result.confidence_rate = 0.0;
			result.calculation_success = false;
			return result;
		}
		tr_file.close();

		// 모델 로드 시도 (예외 처리)
		try {
			td_model = TextDetectionModel_DB(readNet(td_modelPath));
			td_model.setPreferableBackend(DNN_BACKEND_OPENCV);
			td_model.setPreferableTarget(DNN_TARGET_CPU);
			td_model.setBinaryThreshold(binThresh);
			td_model.setPolygonThreshold(polyThresh);
			td_model.setUnclipRatio(unRatio);
			td_model.setMaxCandidates(maxCand);
			td_model.setInputParams(1.0 / 255.0, inpSize, Scalar(122.67891434, 116.66876762, 104.00698793));

			tr_model = readNet(tr_modelPath);
			tr_model.setPreferableBackend(DNN_BACKEND_OPENCV);
			tr_model.setPreferableTarget(DNN_TARGET_CPU);
			model_initialized = true;
		}
		catch (const cv::Exception& e) {
			string error_msg = "모델 로드 중 오류가 발생했습니다:\n\n";
			error_msg += "파일: " + td_modelPath + "\n또는\n";
			error_msg += "파일: " + tr_modelPath + "\n\n";
			error_msg += "오류 내용: " + string(e.what());
			AfxMessageBox(CString(error_msg.c_str()));
			result.original_text = "";
			result.confidence = 0.0;
			result.confidence_rate = 0.0;
			result.calculation_success = false;
			return result;
		}
		catch (...) {
			string error_msg = "알 수 없는 오류가 발생했습니다.\n\n모델 파일 경로를 확인해주세요:\n";
			error_msg += td_modelPath + "\n" + tr_modelPath;
			AfxMessageBox(CString(error_msg.c_str()));
			result.original_text = "";
			result.confidence = 0.0;
			result.confidence_rate = 0.0;
			result.calculation_success = false;
			return result;
		}
	}

	// 모델이 제대로 초기화되었는지 확인
	if (!model_initialized) {
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}

	vector<string> charset = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
		"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
		"!", "\"", "#", "$", "%", "&", "(", ")", "*", "+", ",", "-", ".", "/",
		":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`",
		"{", "|", "}", "~"
	};

	Size inputSize = Size(100, 32);
	Mat targetVertices = Mat(4, 1, CV_32FC2);
	targetVertices.row(0) = Vec2f(0, inputSize.height - 1);
	targetVertices.row(1) = Vec2f(0, 0);
	targetVertices.row(2) = Vec2f(inputSize.width - 1, 0);
	targetVertices.row(3) = Vec2f(inputSize.width - 1, inputSize.height - 1);

	Mat image;
	vector<vector<Point>> pt;
	vector<float> confidence;

	// 입력 이미지 검증
	if (inputImg.empty() || inputImg.cols == 0 || inputImg.rows == 0) {
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}

	// 손글씨 인식을 위한 이미지 전처리 강화
	Mat processedImg = inputImg.clone();
	
	// 1. 채널 변환 (BGR로 통일)
	if (processedImg.channels() == 1) {
		cvtColor(processedImg, processedImg, COLOR_GRAY2BGR);
	}
	else if (processedImg.channels() == 4) {
		cvtColor(processedImg, processedImg, COLOR_BGRA2BGR);
	}
	
	// 2. 그레이스케일 변환 (OCR에 유리)
	Mat gray;
	cvtColor(processedImg, gray, COLOR_BGR2GRAY);
	
	// 3. 노이즈 제거 (손글씨 선명도 향상)
	Mat denoised;
	GaussianBlur(gray, denoised, Size(3, 3), 0);
	
	// 4. 대비 향상 (CLAHE - 적응형 히스토그램 균등화)
	Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
	Mat enhanced;
	clahe->apply(denoised, enhanced);
	
	// 5. 이진화 (OTSU - 자동 임계값)
	Mat binary;
	threshold(enhanced, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);
	
	// 6. 다시 BGR로 변환 (모델 입력 형식에 맞춤)
	cvtColor(binary, image, COLOR_GRAY2BGR);
	
	// 7. 크기 조정
	resize(image, image, inpSize);
	
	// 텍스트 검출 시도 (예외 처리)
	try {
		td_model.detect(image, pt, confidence);
	}
	catch (const cv::Exception& e) {
		string error_msg = "텍스트 검출 중 오류가 발생했습니다:\n\n";
		error_msg += "오류 내용: " + string(e.what()) + "\n\n";
		error_msg += "이미지 크기: " + to_string(inputImg.cols) + "x" + to_string(inputImg.rows);
		AfxMessageBox(CString(error_msg.c_str()));
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}
	catch (...) {
		string error_msg = "텍스트 검출 중 알 수 없는 오류가 발생했습니다.";
		AfxMessageBox(CString(error_msg.c_str()));
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}

	resultImg = inputImg.clone();
	string formula_text = "";
	result.detected_texts.clear();
	result.text_confidences.clear();

	if (pt.size() > 0 && confidence.size() > 0) {
		// 여러 줄 수식을 줄별로 처리하기 위해 Y 좌표로 정렬
		vector<pair<int, int>> text_boxes; // (y_center, index)
		for (int k = 0; k < pt.size(); k++) {
			if (pt[k].size() >= 4) {
				// 박스의 중심 Y 좌표 계산
				int y_sum = 0;
				for (const Point& p : pt[k]) {
					y_sum += p.y;
				}
				int y_center = y_sum / pt[k].size();
				text_boxes.push_back(make_pair(y_center, k));
			}
		}
		
		// Y 좌표로 정렬 (위에서 아래로)
		sort(text_boxes.begin(), text_boxes.end());
		
		// 각 텍스트 영역을 줄별로 인식
		for (size_t idx = 0; idx < text_boxes.size(); idx++) {
			int k = text_boxes[idx].second;
			vector<Point> box = pt[k];
			Mat result_box = Mat(box);

			Mat vertices;
			result_box.convertTo(vertices, CV_32FC2);
			Mat rotationMatrix = getPerspectiveTransform(vertices, targetVertices);
			Mat cropped;
			warpPerspective(image, cropped, rotationMatrix, inputSize);
			Mat blob = blobFromImage(cropped, 1.0 / 127.5, inputSize, Scalar::all(127.5));

			tr_model.setInput(blob);
			Mat outputBlob = tr_model.forward();
			Mat character(25, 96, CV_32F, outputBlob.ptr<float>());
			string text("");
			for (int i = 0; i < character.rows; i++) {
				Point maxIdx;
				minMaxLoc(character.row(i), 0, 0, 0, &maxIdx);
				if (maxIdx.x != 0) text += charset[maxIdx.x - 1];
				else text += "-";
			}

			// 중복 제거
			string textFilter("");
			for (int i = 0; i < text.length(); i++) {
				if (text[i] != '-' && !(i > 0 && text[i] == text[i - 1]))
					textFilter += text[i];
			}
			
			if (!textFilter.empty()) {
				// 줄 구분을 위해 개행 문자 추가 (마지막 줄 제외)
				if (idx < text_boxes.size() - 1) {
					formula_text += textFilter + "\n";
				}
				else {
					formula_text += textFilter;
				}
				result.detected_texts.push_back(textFilter);
				if (k < confidence.size()) {
					result.text_confidences.push_back(confidence[k]);
				}
			}
		}
	}

	// 공백 제거 및 정리
	if (formula_text.empty()) {
		result.original_text = "";
		result.confidence = 0.0;
		result.confidence_rate = 0.0;
		result.calculation_success = false;
		return result;
	}

	// 원본 텍스트 저장
	result.original_text = formula_text;

	// 신뢰도 계산
	if (result.text_confidences.empty()) {
		// 텍스트 검출 신뢰도가 없으면 낮은 신뢰도로 설정
		result.confidence = 0.3; // 낮은 신뢰도
	}
	else {
		result.confidence = calculateConfidence(result.text_confidences);
		// 신뢰도가 너무 높게 나오는 경우 제한
		if (result.confidence > 1.0) {
			result.confidence = 1.0;
		}
		// 손글씨 인식은 일반적으로 낮은 신뢰도를 가지므로 보정
		// OCR 모델이 손글씨에 최적화되지 않았을 가능성 고려
		if (result.confidence > 0.9) {
			result.confidence = result.confidence * 0.85; // 15% 감소
		}
	}
	
	// 수식 정규화
	string normalized = formula_text;
	// 개행 문자를 공백으로 변환 (여러 줄 수식을 하나로 합치기)
	size_t newline_pos = 0;
	while ((newline_pos = normalized.find('\n', newline_pos)) != string::npos) {
		normalized.replace(newline_pos, 1, " ");
		newline_pos++;
	}
	// 공백 제거
	normalized.erase(remove(normalized.begin(), normalized.end(), ' '), normalized.end());
	// 특수 문자 변환 (string::replace 사용)
	size_t pos = 0;
	while ((pos = normalized.find('×', pos)) != string::npos) {
		normalized.replace(pos, 1, "*");
		pos++;
	}
	pos = 0;
	while ((pos = normalized.find('÷', pos)) != string::npos) {
		normalized.replace(pos, 1, "/");
		pos++;
	}
	// 지수 변환 (문자열 치환)
	pos = 0;
	while ((pos = normalized.find('²', pos)) != string::npos) {
		normalized.replace(pos, 1, "^2");
		pos += 2;
	}
	pos = 0;
	while ((pos = normalized.find('³', pos)) != string::npos) {
		normalized.replace(pos, 1, "^3");
		pos += 2;
	}
	normalized = preprocessSquareRoot(normalized);
	normalized = preprocessAbsoluteValue(normalized);
	normalized = normalizeFunctionNames(normalized);

	// AsciiMath 변환
	result.asciimath = convertToAsciiMath(normalized);
	
	// LaTeX 변환
	result.latex = convertToLaTeX(normalized);

	// 등호 처리
	size_t equal_pos = normalized.find('=');
	if (equal_pos != string::npos) {
		string left_side = normalized.substr(0, equal_pos);
		string right_side = normalized.substr(equal_pos + 1);
		
		double left_result = 0.0, right_result = 0.0;
		bool left_success = false, right_success = false;
		
		try {
			left_result = evaluateSimpleExpression(left_side);
			left_success = true;
		}
		catch (...) {
			left_success = false;
		}
		
		try {
			right_result = evaluateSimpleExpression(right_side);
			right_success = true;
		}
		catch (...) {
			right_success = false;
		}
		
		if (left_success && right_success) {
			result.calculation_result = left_result;
			result.calculation_success = (abs(left_result - right_result) < 0.01);
		}
		else {
			result.calculation_success = false;
		}
	}
	else {
		// 등호가 없는 경우 계산
		try {
			result.calculation_result = evaluateSimpleExpression(normalized);
			result.calculation_success = true;
		}
		catch (...) {
			result.calculation_success = false;
		}
	}

	// 전체 신뢰도 계산 (OCR 신뢰도 + 계산 성공 여부)
	result.confidence_rate = result.confidence;
	if (result.calculation_success) {
		result.confidence_rate = min(1.0, result.confidence_rate * 1.1); // 계산 성공 시 약간 증가
	}
	// 신뢰도가 1.0을 초과하지 않도록 제한
	if (result.confidence_rate > 1.0) {
		result.confidence_rate = 1.0;
	}

	return result;
}

// 제곱근 전처리 함수 (√x → sqrt(x))
string CImageProKimJiHyeonDoc::preprocessSquareRoot(const string& formula)
{
	string result = formula;
	size_t pos = 0;
	
	// √ 기호 찾기
	while ((pos = result.find("√", pos)) != string::npos) {
		// √ 기호를 sqrt(로 변환
		result.replace(pos, 1, "sqrt(");
		pos += 5;
		
		// 다음 숫자나 괄호까지 찾아서 닫는 괄호 추가
		size_t end = pos;
		int paren_count = 1;
		
		// 숫자나 괄호 찾기
		while (end < result.length()) {
			if (result[end] == '(') {
				paren_count++;
				end++;
			}
			else if (result[end] == ')') {
				paren_count--;
				if (paren_count == 0) {
					end++;
					break;
				}
				end++;
			}
			else if (isdigit(result[end]) || result[end] == '.' || result[end] == '-') {
				end++;
			}
			else if (paren_count == 1 && 
					 (result[end] == '+' || result[end] == '-' || 
					  result[end] == '*' || result[end] == '/' || result[end] == '^')) {
				break;
			}
			else {
				end++;
			}
		}
		
		// 닫는 괄호 추가
		if (end > pos) {
			result.insert(end, ")");
			pos = end + 1;
		}
	}
	
	return result;
}

// 절댓값 전처리 함수 (|x| → abs(x))
string CImageProKimJiHyeonDoc::preprocessAbsoluteValue(const string& formula)
{
	string result = formula;
	size_t pos = 0;
	
	// | 기호 찾기
	while ((pos = result.find('|', pos)) != string::npos) {
		// 첫 번째 |를 abs(로 변환
		result.replace(pos, 1, "abs(");
		pos += 4;
		
		// 다음 | 찾기
		size_t end = result.find('|', pos);
		if (end != string::npos) {
			// 두 번째 |를 )로 변환
			result.replace(end, 1, ")");
			pos = end + 1;
		}
		else {
			// 닫는 |가 없으면 끝까지
			result += ")";
			break;
		}
	}
	
	return result;
}

// 함수명 정규화 (대소문자 통일)
string CImageProKimJiHyeonDoc::normalizeFunctionNames(const string& formula)
{
	string result = formula;
	
	// 지원하는 함수 목록
	vector<string> functions = {"sin", "cos", "tan", "sinh", "cosh", "tanh", 
								 "log", "ln", "sqrt", "exp", "abs"};
	
	for (const string& func : functions) {
		// 대소문자 구분 없이 찾기
		size_t pos = 0;
		while ((pos = result.find(func, pos)) != string::npos) {
			// 함수명인지 확인 (앞에 알파벳이 없어야 함)
			if (pos == 0 || !isalpha(result[pos - 1])) {
				// 소문자로 변환
				for (size_t i = 0; i < func.length(); i++) {
					result[pos + i] = tolower(result[pos + i]);
				}
			}
			pos += func.length();
		}
	}
	
	return result;
}

// 함수 전처리 함수 (sin(30), log(10) 등을 계산 가능한 형태로)
string CImageProKimJiHyeonDoc::preprocessFunctions(const string& formula)
{
	string result = formula;
	
	// 함수 패턴 찾기: 함수명(인수)
	// 예: sin(30), cos(45), log(10), sqrt(4)
	
	vector<string> functions = {"sin", "cos", "tan", "sinh", "cosh", "tanh", 
								 "log", "ln", "sqrt", "exp", "abs"};
	
	for (const string& func : functions) {
		size_t pos = 0;
		while ((pos = result.find(func + "(", pos)) != string::npos) {
			size_t func_start = pos;
			size_t arg_start = pos + func.length() + 1; // 함수명 + '('
			
			// 인수 찾기 (괄호 안의 내용)
			size_t arg_end = arg_start;
			int paren_count = 1;
			
			while (arg_end < result.length() && paren_count > 0) {
				if (result[arg_end] == '(') paren_count++;
				else if (result[arg_end] == ')') paren_count--;
				arg_end++;
			}
			
			if (paren_count == 0) {
				// 인수 추출
				string arg_str = result.substr(arg_start, arg_end - arg_start - 1);
				
				try {
					// 인수를 먼저 계산 (재귀적)
					double arg_value = evaluateSimpleExpression(arg_str);
					
					// 함수 적용
					double func_value = 0.0;
					const double PI = 3.14159265358979323846;
					if (func == "sin") func_value = sin(arg_value * PI / 180.0); // 도 단위
					else if (func == "cos") func_value = cos(arg_value * PI / 180.0);
					else if (func == "tan") func_value = tan(arg_value * PI / 180.0);
					else if (func == "sinh") func_value = sinh(arg_value);
					else if (func == "cosh") func_value = cosh(arg_value);
					else if (func == "tanh") func_value = tanh(arg_value);
					else if (func == "log") func_value = log10(arg_value);
					else if (func == "ln") func_value = log(arg_value);
					else if (func == "sqrt") func_value = sqrt(arg_value);
					else if (func == "exp") func_value = exp(arg_value);
					else if (func == "abs") func_value = fabs(arg_value);
					
					// 함수 호출을 계산된 값으로 교체
					char buffer[64];
					sprintf_s(buffer, "%.10g", func_value);
					string replacement(buffer);
					
					result.replace(func_start, arg_end - func_start, replacement);
					pos = func_start + replacement.length();
					continue;
				}
				catch (...) {
					// 계산 실패 시 그대로 유지
					pos = arg_end;
				}
			}
			else {
				pos++;
			}
		}
	}
	
	return result;
}

// 확장된 수식 계산 함수 - 지수, 분수, 변수 처리
double CImageProKimJiHyeonDoc::evaluateSimpleExpression(const string& formula)
{
	// 1단계: 함수 처리 (sin, cos, log, sqrt 등)
	string processed = preprocessFunctions(formula);
	
	// 2단계: 분수 처리 (예: "1/2" -> "0.5")
	processed = preprocessFractions(processed);
	
	// 3단계: 변수 처리 (변수가 있으면 계산 불가로 처리하거나 기본값 사용)
	processed = preprocessVariables(processed);
	
	// 4단계: 지수와 기본 연산 처리
	return evaluateWithExponent(processed);
}

// 분수 전처리 함수 (예: "1/2" -> "0.5")
string CImageProKimJiHyeonDoc::preprocessFractions(const string& formula)
{
	string result = formula;
	
	// 간단한 분수 패턴 찾기: 숫자/숫자 (괄호 안이거나 연산자 사이)
	// 예: "1/2", "3/4", "-1/4", "(1/2)"
	size_t pos = 0;
	while ((pos = result.find('/', pos)) != string::npos) {
		// '/' 앞뒤로 숫자가 있는지 확인
		size_t start = pos;
		size_t end = pos + 1;
		
		// 분자 찾기 (뒤로)
		while (start > 0 && (isdigit(result[start - 1]) || result[start - 1] == '.')) {
			start--;
		}
		// 음수 처리
		if (start > 0 && result[start - 1] == '-') {
			start--;
		}
		
		// 분모 찾기 (앞으로)
		while (end < result.length() && (isdigit(result[end]) || result[end] == '.')) {
			end++;
		}
		
		// 분수 부분 추출 (단순 숫자/숫자 형태만)
		if (start < pos && end > pos + 1) {
			// 앞뒤가 연산자나 괄호인지 확인
			bool is_fraction = true;
			if (start > 0 && isalnum(result[start - 1]) && result[start - 1] != ')') {
				is_fraction = false;  // 변수나 다른 숫자와 연결됨
			}
			if (end < result.length() && isalnum(result[end]) && result[end] != '(') {
				is_fraction = false;  // 변수나 다른 숫자와 연결됨
			}
			
			if (is_fraction) {
				string numerator_str = result.substr(start, pos - start);
				string denominator_str = result.substr(pos + 1, end - pos - 1);
				
				// 음수 처리
				bool is_negative = false;
				if (numerator_str[0] == '-') {
					is_negative = true;
					numerator_str = numerator_str.substr(1);
				}
				
				try {
					double numerator = stod(numerator_str);
					double denominator = stod(denominator_str);
					
					if (denominator != 0) {
						double fraction_value = numerator / denominator;
						if (is_negative) fraction_value = -fraction_value;
						
						// 분수를 계산된 값으로 교체
						char buffer[64];
						sprintf_s(buffer, "%.10g", fraction_value);  // 과학적 표기법 방지
						string replacement(buffer);
						
						result.replace(start, end - start, replacement);
						pos = start + replacement.length();
						continue;
					}
				}
				catch (...) {
					// 변환 실패 시 그대로 유지
				}
			}
		}
		
		pos++;
	}
	
	return result;
}

// 변수 전처리 함수 (변수가 있으면 경고 또는 기본값 사용)
string CImageProKimJiHyeonDoc::preprocessVariables(const string& formula)
{
	string result = formula;
	bool has_variables = false;
	
	// 변수 패턴 찾기: 알파벳 (a-z, A-Z)
	// 단, 이미 처리된 함수명이나 상수는 제외
	for (size_t i = 0; i < result.length(); i++) {
		if (isalpha(result[i])) {
			// 변수로 간주 (단, e, pi 같은 상수는 나중에 처리 가능)
			// 일단 변수가 있으면 계산 불가로 처리
			has_variables = true;
			break;
		}
	}
	
	if (has_variables) {
		// 변수가 있는 경우, 숫자*변수 형태는 변수를 1로 치환
		// 예: "2x" -> "2*1", "3a" -> "3*1"
		for (size_t i = 0; i < result.length() - 1; i++) {
			if (isdigit(result[i]) && isalpha(result[i + 1])) {
				result.insert(i + 1, "*1");
				i += 2;
			}
		}
		
		// 단독 변수는 1로 치환
		for (size_t i = 0; i < result.length(); i++) {
			if (isalpha(result[i]) && 
				(i == 0 || !isdigit(result[i - 1])) &&
				(i == result.length() - 1 || !isdigit(result[i + 1]))) {
				result[i] = '1';
			}
		}
	}
	
	return result;
}

// 지수를 포함한 수식 계산
double CImageProKimJiHyeonDoc::evaluateWithExponent(const string& formula)
{
	// 스택 기반 계산기로 우선순위 처리
	// 우선순위: ^ > *, / > +, -
	
	stack<double> numbers;
	stack<char> operators;
	
	string current_num = "";
	
	// 연산자 우선순위 함수
	auto precedence = [](char op) -> int {
		if (op == '+' || op == '-') return 1;
		if (op == '*' || op == '/') return 2;
		if (op == '^') return 3;  // 지수가 가장 높은 우선순위
		return 0;
	};
	
	// 연산 수행 함수
	auto applyOperator = [](stack<double>& nums, stack<char>& ops) {
		if (nums.size() < 2 || ops.empty()) return;
		double b = nums.top(); nums.pop();
		double a = nums.top(); nums.pop();
		char op = ops.top(); ops.pop();
		
		switch (op) {
		case '+': nums.push(a + b); break;
		case '-': nums.push(a - b); break;
		case '*': nums.push(a * b); break;
		case '/': 
			if (b == 0) throw runtime_error("Division by zero");
			nums.push(a / b); 
			break;
		case '^': nums.push(pow(a, b)); break;  // 지수 계산
		}
	};
	
	for (size_t i = 0; i < formula.length(); i++) {
		char c = formula[i];
		
		if (isdigit(c) || c == '.' || c == '-') {
			// 음수 처리: '-'가 연산자가 아닌 경우 (숫자의 일부)
			if (c == '-' && (i == 0 || (!isdigit(formula[i - 1]) && formula[i - 1] != '.' && formula[i - 1] != ')'))) {
				current_num += c;
			}
			else if (c != '-' || !current_num.empty()) {
				current_num += c;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			if (!current_num.empty()) {
				numbers.push(stod(current_num));
				current_num = "";
			}
			
			// 우선순위에 따라 연산 수행
			// 지수는 오른쪽 결합이므로 특별 처리
			if (c == '^') {
				// 지수는 바로 push (오른쪽 결합)
				operators.push(c);
			}
			else {
				while (!operators.empty() && operators.top() != '(' &&
					   precedence(operators.top()) >= precedence(c)) {
					applyOperator(numbers, operators);
				}
				operators.push(c);
			}
		}
		else if (c == '(') {
			if (!current_num.empty()) {
				numbers.push(stod(current_num));
				current_num = "";
			}
			operators.push(c);
		}
		else if (c == ')') {
			if (!current_num.empty()) {
				numbers.push(stod(current_num));
				current_num = "";
			}
			while (!operators.empty() && operators.top() != '(') {
				applyOperator(numbers, operators);
			}
			if (!operators.empty()) operators.pop(); // '(' 제거
		}
	}
	
	// 마지막 숫자 처리
	if (!current_num.empty()) {
		numbers.push(stod(current_num));
	}
	
	// 남은 연산 수행 (지수는 오른쪽부터)
	while (!operators.empty()) {
		applyOperator(numbers, operators);
	}
	
	if (numbers.empty()) {
		throw runtime_error("Invalid expression");
	}
	
	return numbers.top();
}

// 신뢰도 계산 함수
double CImageProKimJiHyeonDoc::calculateConfidence(const vector<float>& confidences)
{
	if (confidences.empty()) {
		return 0.0;
	}
	
	double sum = 0.0;
	for (float conf : confidences) {
		sum += conf;
	}
	
	return sum / confidences.size();
}

// AsciiMath 변환 함수
string CImageProKimJiHyeonDoc::convertToAsciiMath(const string& formula)
{
	string result = formula;
	
	// 기본적으로는 정규화된 수식을 그대로 사용
	// 추가 변환이 필요한 경우 여기서 처리
	// 예: sqrt(x) -> sqrt(x) (이미 처리됨)
	// 예: sin(30) -> sin(30) (이미 처리됨)
	
	return result;
}

// LaTeX 변환 함수 (Mathpix 수준으로 개선)
string CImageProKimJiHyeonDoc::convertToLaTeX(const string& formula)
{
	string result = formula;
	size_t pos = 0;
	
	// 1. 지수 처리 개선 (^2 → ^{2}, a^3 → a^{3})
	pos = 0;
	while ((pos = result.find('^', pos)) != string::npos) {
		if (pos < result.length() - 1) {
			char next = result[pos + 1];
			if (isdigit(next)) {
				// 단일 숫자 지수는 중괄호로 감싸기
				result.insert(pos + 1, "{");
				result.insert(pos + 3, "}");
				pos += 4;
			}
			else if (next == '(') {
				// 괄호가 있으면 그대로 유지
				pos++;
			}
			else {
				pos++;
			}
		}
		else {
			pos++;
		}
	}
	
	// 2. 분수 처리 개선 (a/b → \frac{a}{b})
	pos = 0;
	while ((pos = result.find('/', pos)) != string::npos) {
		// 분수 형태인지 확인 (앞뒤에 숫자나 변수가 있어야 함)
		if (pos > 0 && pos < result.length() - 1) {
			char prev = result[pos - 1];
			char next = result[pos + 1];
			if ((isdigit(prev) || isalpha(prev) || prev == ')') &&
				(isdigit(next) || isalpha(next) || next == '(')) {
				// 분자 찾기 (앞쪽)
				size_t num_start = pos;
				while (num_start > 0 && 
					   (isdigit(result[num_start - 1]) || isalpha(result[num_start - 1]) || 
						result[num_start - 1] == ')' || result[num_start - 1] == '}')) {
					num_start--;
				}
				
				// 분모 찾기 (뒤쪽)
				size_t den_end = pos + 1;
				while (den_end < result.length() && 
					   (isdigit(result[den_end]) || isalpha(result[den_end]) || 
						result[den_end] == '(' || result[den_end] == '{')) {
					den_end++;
				}
				
				// 괄호 처리
				if (result[den_end - 1] == ')' || result[den_end - 1] == '}') {
					// 괄호 쌍 찾기
					int paren_count = 1;
					size_t den_start = den_end - 1;
					while (den_start > pos && paren_count > 0) {
						if (result[den_start] == ')' || result[den_start] == '}') paren_count++;
						else if (result[den_start] == '(' || result[den_start] == '{') paren_count--;
						den_start--;
					}
					if (paren_count == 0) den_start++;
				}
				else {
					// 단순 변수나 숫자
				}
				
				// 분자와 분모 추출
				string numerator = result.substr(num_start, pos - num_start);
				string denominator = result.substr(pos + 1, den_end - pos - 1);
				
				// \frac{분자}{분모}로 변환
				string frac = "\\frac{" + numerator + "}{" + denominator + "}";
				result.replace(num_start, den_end - num_start, frac);
				pos = num_start + frac.length();
				continue;
			}
		}
		pos++;
	}
	
	// 3. 곱하기 변환
	pos = 0;
	while ((pos = result.find('*', pos)) != string::npos) {
		// 앞뒤가 숫자나 변수인 경우에만 변환
		if (pos > 0 && pos < result.length() - 1) {
			char prev = result[pos - 1];
			char next = result[pos + 1];
			if ((isdigit(prev) || isalpha(prev) || prev == '}' || prev == ')') &&
				(isdigit(next) || isalpha(next) || next == '{' || next == '(')) {
				result.replace(pos, 1, " \\times ");
				pos += 8;
				continue;
			}
		}
		pos++;
	}
	
	// 제곱근 변환
	pos = 0;
	while ((pos = result.find("sqrt(", pos)) != string::npos) {
		result.replace(pos, 5, "\\sqrt{");
		pos += 6;
		// 닫는 괄호 찾기
		size_t end = pos;
		int paren_count = 1;
		while (end < result.length() && paren_count > 0) {
			if (result[end] == '(') paren_count++;
			else if (result[end] == ')') paren_count--;
			end++;
		}
		if (paren_count == 0 && end > pos) {
			result.replace(end - 1, 1, "}");
		}
		pos = end;
	}
	
	// 삼각함수 변환
	vector<pair<string, string>> functions = {
		{"sin(", "\\sin("},
		{"cos(", "\\cos("},
		{"tan(", "\\tan("},
		{"sinh(", "\\sinh("},
		{"cosh(", "\\cosh("},
		{"tanh(", "\\tanh("},
		{"log(", "\\log("},
		{"ln(", "\\ln("},
		{"exp(", "\\exp("},
		{"abs(", "\\left|"}
	};
	
	for (const auto& func : functions) {
		pos = 0;
		while ((pos = result.find(func.first, pos)) != string::npos) {
			result.replace(pos, func.first.length(), func.second);
			pos += func.second.length();
			
			// abs의 경우 닫는 괄호를 |로 변환
			if (func.first == "abs(") {
				size_t end = pos;
				int paren_count = 1;
				while (end < result.length() && paren_count > 0) {
					if (result[end] == '(') paren_count++;
					else if (result[end] == ')') {
						paren_count--;
						if (paren_count == 0) {
							result.replace(end, 1, "\\right|");
							break;
						}
					}
					end++;
				}
			}
		}
	}
	
	return result;
}

// HTML 출력 생성 함수
string CImageProKimJiHyeonDoc::generateHTMLOutput(const FormulaRecognitionResult& result)
{
	string html = "<div>\n";
	
	// 원본 텍스트
	if (!result.original_text.empty()) {
		html += "  <p>원본 텍스트: " + escapeHTML(result.original_text) + "</p>\n";
	}
	
	// 수식 (AsciiMath와 LaTeX 포함)
	html += "  <span class=\"math-inline\">\n";
	html += "    <asciimath style=\"display: none;\">" + escapeHTML(result.asciimath) + "</asciimath>\n";
	html += "    <latex style=\"display: none;\">" + escapeHTML(result.latex) + "</latex>\n";
	html += "  </span>\n";
	
	// 계산 결과
	if (result.calculation_success) {
		char buffer[64];
		sprintf_s(buffer, "%.2f", result.calculation_result);
		html += "  <p>계산 결과: " + string(buffer) + "</p>\n";
	}
	
	// 신뢰도
	char conf_buffer[64];
	sprintf_s(conf_buffer, "%.1f%%", result.confidence_rate * 100.0);
	html += "  <p>신뢰도: " + string(conf_buffer) + "</p>\n";
	
	html += "</div>";
	
	return html;
}

// JSON 출력 생성 함수
string CImageProKimJiHyeonDoc::generateJSONOutput(const FormulaRecognitionResult& result)
{
	string json = "{\n";
	
	// 신뢰도
	char conf_buffer[64];
	sprintf_s(conf_buffer, "%.6f", result.confidence);
	json += "  \"confidence\": " + string(conf_buffer) + ",\n";
	
	sprintf_s(conf_buffer, "%.6f", result.confidence_rate);
	json += "  \"confidence_rate\": " + string(conf_buffer) + ",\n";
	
	// 데이터 배열
	json += "  \"data\": [\n";
	json += "    {\n";
	json += "      \"type\": \"asciimath\",\n";
	json += "      \"value\": \"" + escapeJSON(result.asciimath) + "\"\n";
	json += "    },\n";
	json += "    {\n";
	json += "      \"type\": \"latex\",\n";
	json += "      \"value\": \"" + escapeJSON(result.latex) + "\"\n";
	json += "    }\n";
	json += "  ],\n";
	
	// 텍스트
	json += "  \"text\": \"" + escapeJSON(result.original_text) + "\",\n";
	
	// HTML
	json += "  \"html\": \"" + escapeJSON(generateHTMLOutput(result)) + "\",\n";
	
	// 계산 결과
	json += "  \"calculation\": {\n";
	char calc_buffer[64];
	sprintf_s(calc_buffer, "%.2f", result.calculation_result);
	json += "    \"result\": " + string(calc_buffer) + ",\n";
	json += "    \"success\": " + string(result.calculation_success ? "true" : "false") + "\n";
	json += "  }\n";
	
	json += "}";
	
	return json;
}

// JSON 이스케이프 함수
string CImageProKimJiHyeonDoc::escapeJSON(const string& str)
{
	string result;
	result.reserve(str.length() * 2); // 예상 크기 예약
	
	for (size_t i = 0; i < str.length(); i++) {
		char c = str[i];
		switch (c) {
		case '"': result += "\\\""; break;
		case '\\': result += "\\\\"; break;
		case '\b': result += "\\b"; break;
		case '\f': result += "\\f"; break;
		case '\n': result += "\\n"; break;
		case '\r': result += "\\r"; break;
		case '\t': result += "\\t"; break;
		default:
			if (c < 0x20) {
				// 제어 문자는 유니코드 이스케이프
				char buffer[7];
				sprintf_s(buffer, "\\u%04x", (unsigned char)c);
				result += buffer;
			}
			else {
				result += c;
			}
			break;
		}
	}
	
	return result;
}

// HTML 이스케이프 함수
string CImageProKimJiHyeonDoc::escapeHTML(const string& str)
{
	string result;
	result.reserve(str.length() * 2); // 예상 크기 예약
	
	for (size_t i = 0; i < str.length(); i++) {
		char c = str[i];
		switch (c) {
		case '<': result += "&lt;"; break;
		case '>': result += "&gt;"; break;
		case '&': result += "&amp;"; break;
		case '"': result += "&quot;"; break;
		case '\'': result += "&#39;"; break;
		default:
			result += c;
			break;
		}
	}
	
	return result;
}
