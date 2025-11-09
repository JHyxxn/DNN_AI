
// ImagePro_Kim_Ji_HyeonView.h: CImageProKimJiHyeonView 클래스의 인터페이스
//

#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;


class CImageProKimJiHyeonView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProKimJiHyeonView() noexcept;
	DECLARE_DYNCREATE(CImageProKimJiHyeonView)

// 특성입니다.
public:
	CImageProKimJiHyeonDoc* GetDocument()	const;
	int drawHist = false;
	int viewMode;           // 영상 출력 모드
	VideoCapture vcap;      // 동영상 캡처 객체
	int operation;          // 동영상 처리 연산 종류
	int Ax, Ay, Bx, By;     // 마우스 드래그 좌표
	BOOL mouse_input_started; // 마우스 입력 시작 여부
	string VideoFileName;   // 동영상 파일 경로

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProKimJiHyeonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	void drawImage(CDC* pDC, Mat img, int offset_x, int offset_y);
	afx_msg void OnPixelMinus();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnMySave();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnDrawHistogramOnoff();
	afx_msg void OnPixelBinarizationHRange();
	afx_msg void OnPixelInvert();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelBinarizationAutoThresh();
	afx_msg void OnPixelQuantization();
	afx_msg void OnPixelRangeHighlighting();
	afx_msg void OnPixelGammaCorrection();
	afx_msg void OnPixelTwoImagesAdd();
	afx_msg void OnPixelBinarizationAdaptiveThresh();
	afx_msg void PixelBinarizationAdaptiveThresh();
	afx_msg void OnPixelTwoImagesAddLogo();
	afx_msg void OnPixelTwoImagesMinus();
	afx_msg void OnPixelTwoImagesAnd();
	afx_msg void OnPixelTwoImagesOr();
	afx_msg void OnPixelTwoImagesXor();
	afx_msg void OnPixelBinarizationHRangeSlider();
	afx_msg void OnPixelGammaCorrectionSlider();
	afx_msg void OnPixelBinarySlider();
	afx_msg void OnPixelBinarySlider2();
	afx_msg void OnPixelQuantizationSlider();
	afx_msg void OnRegionBlurring();
	afx_msg void OnRegionBlurringGaussian();
	afx_msg void OnRegionBlurringMedian();
	afx_msg void OnRegionBlurringBilateral();
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionCanny();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionLaplacian();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionWatercolor();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyOpening();
	afx_msg void OnMorphologyClosing();
	afx_msg void OnMorphologyGradient();
	afx_msg void OnMorphologyTopHat();
	afx_msg void OnMorphologyBlackHat();
	afx_msg void OnMorphologyHitOrMiss();
	afx_msg void OnMorphologyLineDetection();
	afx_msg void OnMorphologyCountCell();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutAvg();
	afx_msg void OnGeometryRotate();
	afx_msg void OnGeometryFlipVertical();
	afx_msg void OnGeometryFlipHorizontal();
	afx_msg void OnGeometryFlipBoth();
	afx_msg void OnGeometryWarping();
	afx_msg void OnGeometryMorphing();
	afx_msg void OnVideoSharpening();
	afx_msg void OnCameraView();
	afx_msg void OnCameraSharpening();
	afx_msg void OnCameraSubtract();
	afx_msg void OnCameraSaveStart();
	afx_msg void OnCameraSaveEnd();
	afx_msg void OnDnnImageClassification();
	afx_msg void OnDnnMosaic();
	afx_msg void OnDnnFacialExpressionRecognition();
	afx_msg void OnDnnHumanSegmentation();
	afx_msg void OnDnnObjectTracking();
	afx_msg void OnDnnQrcodeRecognition();
	afx_msg void OnDnnDeblurring();
	afx_msg void OnDnnFaceDetection();
	afx_msg void OnDnnFaceMatching();
	afx_msg void OnDnnAgeAndGenderRecognition();
	afx_msg void OnDnnHumanParsing();
	afx_msg void OnDnnImageSegmentation();
	afx_msg void OnDnnObjectDetection();
	afx_msg void OnDnnPoseRecognition();
	afx_msg void OnDnnDigitsRecognition();
	afx_msg void OnDnnEnglishWordRecognition();
	afx_msg void OnDnnColorization();
	afx_msg void OnDnnFaceSwapVideo();
	afx_msg void OnDnnLaneDetectionVideo();
	afx_msg void OnDnnFormulaRecognition();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ImagePro_Kim_Ji_HyeonView.cpp의 디버그 버전
inline CImageProKimJiHyeonDoc* CImageProKimJiHyeonView::GetDocument() const
   { return reinterpret_cast<CImageProKimJiHyeonDoc*>(m_pDocument); }
#endif

