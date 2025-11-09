// ImagePro_Kim_Ji_HyeonView.cpp: CImageProKimJiHyeonView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImagePro_Kim_Ji_Hyeon.h"
#endif

#include "ImagePro_Kim_Ji_HyeonDoc.h"
#include "ImagePro_Kim_Ji_HyeonView.h"
#include "CFormulaResultDialog.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TWO_IMAGES	1
#define THREE_IMAGES	2
#define MORPHING		3
#define VIDEO_FILE		4
#define CAMERA			5
#define VIEW_ONLY		1
#define SHARPENING		2
#define SUBTRACT		3
#define SAVE_START		4
#define SAVE_END		5
#define QRCODE_RECOGNITION	10
#define FACE_DETECTION		11
#define HUMAN_SEGMENTATION	12
#define HUMAN_PARSING		13
#define OBJECT_TRACKING		14
#define DEBLURRING			15
#define DIGITS_RECOGNITION	16
#define POSE_RECOGNITION	17
#define ENGLISH_WORD_RECOGNITION	18
#define FACE_SWAP			19
#define LANE_DETECTION		20
#define WARPING_MOUSE		6
#define FACE_TRACKING		9

// CImageProKimJiHyeonView

IMPLEMENT_DYNCREATE(CImageProKimJiHyeonView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProKimJiHyeonView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProKimJiHyeonView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(32771, &CImageProKimJiHyeonView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProKimJiHyeonView::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_MINUS, &CImageProKimJiHyeonView::OnPixelMinus)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProKimJiHyeonView::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProKimJiHyeonView::OnPixelDiv)
	ON_COMMAND(ID_MY_SAVE, &CImageProKimJiHyeonView::OnMySave)
	ON_COMMAND(32780, &CImageProKimJiHyeonView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProKimJiHyeonView::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CImageProKimJiHyeonView::OnPixelContrastStretching)
	ON_COMMAND(ID_DRAW_HISTOGRAM_ONOFF, &CImageProKimJiHyeonView::OnDrawHistogramOnoff)
	ON_COMMAND(ID_PIXEL_BINARIZATION_H_RANGE, &CImageProKimJiHyeonView::OnPixelBinarizationHRange)
	ON_COMMAND(ID_PIXEL_INVERT, &CImageProKimJiHyeonView::OnPixelInvert)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProKimJiHyeonView::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_BINARIZATION_AUTO_THRESH, &CImageProKimJiHyeonView::OnPixelBinarizationAutoThresh)
	ON_COMMAND(ID_PIXEL_QUANTIZATION, &CImageProKimJiHyeonView::OnPixelQuantization)
	ON_COMMAND(ID_PIXEL_RANGE_HIGHLIGHTING, &CImageProKimJiHyeonView::OnPixelRangeHighlighting)
	ON_COMMAND(ID_PIXEL_GAMMA_CORRECTION, &CImageProKimJiHyeonView::OnPixelGammaCorrection)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_ADD, &CImageProKimJiHyeonView::OnPixelTwoImagesAdd)
	ON_COMMAND(ID_PIXEL_BINARIZATION_ADAPTIVE_THRESH, &CImageProKimJiHyeonView::OnPixelBinarizationAdaptiveThresh)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_ADD_LOGO, &CImageProKimJiHyeonView::OnPixelTwoImagesAddLogo)
	ON_COMMAND(32798, &CImageProKimJiHyeonView::OnPixelTwoImagesMinus)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_MINUS, &CImageProKimJiHyeonView::OnPixelTwoImagesMinus)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_AND, &CImageProKimJiHyeonView::OnPixelTwoImagesAnd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_OR, &CImageProKimJiHyeonView::OnPixelTwoImagesOr)
	ON_COMMAND(ID_PIXEL_TWO_IMAGES_XOR, &CImageProKimJiHyeonView::OnPixelTwoImagesXor)
	ON_COMMAND(ID_PIXEL_BINARY_SLIDER, &CImageProKimJiHyeonView::OnPixelBinarySlider)
	ON_COMMAND(ID_PIXEL_BINARY_SLIDER2, &CImageProKimJiHyeonView::OnPixelBinarySlider2)
	ON_COMMAND(ID_PIXEL_GAMMA_CORRECTION_SLIDER, &CImageProKimJiHyeonView::OnPixelGammaCorrectionSlider)
	ON_COMMAND(32815, &CImageProKimJiHyeonView::OnPixelQuantizationSlider)
	ON_COMMAND(ID_PIXEL_QUANTIZATION_SLIDER, &CImageProKimJiHyeonView::OnPixelQuantizationSlider)
	ON_COMMAND(ID_REGION_BLURRING, &CImageProKimJiHyeonView::OnRegionBlurring)
	ON_COMMAND(ID_REGION_BLURRING_GAUSSIAN, &CImageProKimJiHyeonView::OnRegionBlurringGaussian)
	ON_COMMAND(ID_REGION_BLURRING_MEDIAN, &CImageProKimJiHyeonView::OnRegionBlurringMedian)
	ON_COMMAND(ID_REGION_BLURRING_BILATERAL, &CImageProKimJiHyeonView::OnRegionBlurringBilateral)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProKimJiHyeonView::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProKimJiHyeonView::OnRegionSobel)
	ON_COMMAND(ID_REGION_CANNY, &CImageProKimJiHyeonView::OnRegionCanny)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProKimJiHyeonView::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProKimJiHyeonView::OnRegionRoberts)
	ON_COMMAND(ID_REGION_LAPLACIAN, &CImageProKimJiHyeonView::OnRegionLaplacian)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProKimJiHyeonView::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_WATERCOLOR, &CImageProKimJiHyeonView::OnRegionWatercolor)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CImageProKimJiHyeonView::OnMorphologyErosion)
	ON_COMMAND(ID_MORPHOLOGY_DILATION, &CImageProKimJiHyeonView::OnMorphologyDilation)
	ON_COMMAND(ID_MORPHOLOGY_OPENING, &CImageProKimJiHyeonView::OnMorphologyOpening)
	ON_COMMAND(ID_MORPHOLOGY_CLOSING, &CImageProKimJiHyeonView::OnMorphologyClosing)
	ON_COMMAND(ID_MORPHOLOGY_GRADIENT, &CImageProKimJiHyeonView::OnMorphologyGradient)
	ON_COMMAND(ID_MORPHOLOGY_TOP_HAT, &CImageProKimJiHyeonView::OnMorphologyTopHat)
	ON_COMMAND(ID_MORPHOLOGY_BLACK_HAT, &CImageProKimJiHyeonView::OnMorphologyBlackHat)
	ON_COMMAND(ID_MORPHOLOGY_HIT_OR_MISS, &CImageProKimJiHyeonView::OnMorphologyHitOrMiss)
	ON_COMMAND(ID_MORPHOLOGY_LINE_DETECTION, &CImageProKimJiHyeonView::OnMorphologyLineDetection)
	ON_COMMAND(ID_MORPHOLOGY_COUNT_CELL, &CImageProKimJiHyeonView::OnMorphologyCountCell)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProKimJiHyeonView::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_INTERPOLATION, &CImageProKimJiHyeonView::OnGeometryZoominInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProKimJiHyeonView::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG, &CImageProKimJiHyeonView::OnGeometryZoomoutAvg)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CImageProKimJiHyeonView::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_FLIP_VERTICAL, &CImageProKimJiHyeonView::OnGeometryFlipVertical)
	ON_COMMAND(ID_GEOMETRY_FLIP_HORIZONTAL, &CImageProKimJiHyeonView::OnGeometryFlipHorizontal)
	ON_COMMAND(ID_GEOMETRY_FLIP_BOTH, &CImageProKimJiHyeonView::OnGeometryFlipBoth)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProKimJiHyeonView::OnGeometryWarping)
	ON_COMMAND(ID_GEOMETRY_MORPHING, &CImageProKimJiHyeonView::OnGeometryMorphing)
	ON_COMMAND(ID_VIDEO_SHARPENING, &CImageProKimJiHyeonView::OnVideoSharpening)
	ON_COMMAND(ID_CAMERA_VIEW, &CImageProKimJiHyeonView::OnCameraView)
	ON_COMMAND(ID_CAMERA_SHARPENING, &CImageProKimJiHyeonView::OnCameraSharpening)
	ON_COMMAND(ID_CAMERA_SUBTRACT, &CImageProKimJiHyeonView::OnCameraSubtract)
	ON_COMMAND(ID_CAMERA_SAVE_START, &CImageProKimJiHyeonView::OnCameraSaveStart)
	ON_COMMAND(ID_CAMERA_SAVE_END, &CImageProKimJiHyeonView::OnCameraSaveEnd)
	ON_COMMAND(ID_DNN_IMAGE_CLASSIFICATION, &CImageProKimJiHyeonView::OnDnnImageClassification)
	ON_COMMAND(ID_DNN_MOSAIC, &CImageProKimJiHyeonView::OnDnnMosaic)
	ON_COMMAND(ID_DNN_FACIAL_EXPRESSION_RECOGNITION, &CImageProKimJiHyeonView::OnDnnFacialExpressionRecognition)
	ON_COMMAND(ID_DNN_HUMAN_SEGMENTATION, &CImageProKimJiHyeonView::OnDnnHumanSegmentation)
	ON_COMMAND(ID_DNN_OBJECT_TRACKING, &CImageProKimJiHyeonView::OnDnnObjectTracking)
	ON_COMMAND(ID_DNN_QR_CODE_RECOGNITION, &CImageProKimJiHyeonView::OnDnnQrcodeRecognition)
	ON_COMMAND(ID_DNN_DEBLURRING, &CImageProKimJiHyeonView::OnDnnDeblurring)
	ON_COMMAND(ID_DNN_FACE_DETECTION, &CImageProKimJiHyeonView::OnDnnFaceDetection)
	ON_COMMAND(ID_DNN_FACE_MATCHING, &CImageProKimJiHyeonView::OnDnnFaceMatching)
	ON_COMMAND(ID_DNN_AGE_GENDER_RECOGNITION, &CImageProKimJiHyeonView::OnDnnAgeAndGenderRecognition)
	ON_COMMAND(ID_DNN_BODY_PART_SEGMENTATION, &CImageProKimJiHyeonView::OnDnnHumanParsing)
	ON_COMMAND(ID_DNN_IMAGE_SEGMENTATION, &CImageProKimJiHyeonView::OnDnnImageSegmentation)
	ON_COMMAND(ID_DNN_OBJECT_DETECTION, &CImageProKimJiHyeonView::OnDnnObjectDetection)
	ON_COMMAND(ID_DNN_POSE_RECOGNITION, &CImageProKimJiHyeonView::OnDnnPoseRecognition)
	ON_COMMAND(ID_DNN_DIGITS_RECOGNITION, &CImageProKimJiHyeonView::OnDnnDigitsRecognition)
	ON_COMMAND(ID_DNN_ENGLISH_WORD_RECOGNITION, &CImageProKimJiHyeonView::OnDnnEnglishWordRecognition)
	ON_COMMAND(ID_DNN_COLORIZATION, &CImageProKimJiHyeonView::OnDnnColorization)
	ON_COMMAND(ID_DNN_FACE_SWAP, &CImageProKimJiHyeonView::OnDnnFaceSwapVideo)
	ON_COMMAND(ID_DNN_LANE_DETECTION, &CImageProKimJiHyeonView::OnDnnLaneDetectionVideo)
	ON_COMMAND(ID_DNN_FORMULA_RECOGNITION, &CImageProKimJiHyeonView::OnDnnFormulaRecognition)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CImageProKimJiHyeonView 생성/소멸

CImageProKimJiHyeonView::CImageProKimJiHyeonView() noexcept
{
	mouse_input_started = FALSE;
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProKimJiHyeonView::~CImageProKimJiHyeonView()
{
}

BOOL CImageProKimJiHyeonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProKimJiHyeonView 그리기

void CImageProKimJiHyeonView::OnDraw(CDC* pDC)
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (viewMode == VIDEO_FILE) {
		return;
	}
	else if (viewMode == CAMERA) {
		return;
	}

	drawImage(pDC, pDoc->inputImg, 0, 0);
	if (viewMode == THREE_IMAGES) {
		drawImage(pDC, pDoc->inputImg2, pDoc->inputImg.cols + 30, 0);
		drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + pDoc->inputImg2.cols + 60, 0);
	}
	else if (viewMode == TWO_IMAGES)
		drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
	else if (viewMode == MORPHING) {
		drawImage(pDC, pDoc->inputImg2, pDoc->inputImg.cols + 10, 0);
		for (int i = 0; i < 10; i++) {
			drawImage(pDC, pDoc->morphedImg[i],
				pDoc->inputImg.cols * 2 + 20, 0);
		}
	}

	if (mouse_input_started == TRUE) {
		CPen Pen;
		Pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		pDC->SelectObject(&Pen);
		pDC->MoveTo(Ax, Ay);
		pDC->LineTo(Ax, By);
		pDC->LineTo(Bx, By);
		pDC->LineTo(Bx, Ay);
		pDC->LineTo(Ax, Ay);
		Pen.DeleteObject();
	}
}

void CImageProKimJiHyeonView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 5000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProKimJiHyeonView 인쇄


void CImageProKimJiHyeonView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProKimJiHyeonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProKimJiHyeonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProKimJiHyeonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProKimJiHyeonView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProKimJiHyeonView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProKimJiHyeonView 진단

#ifdef _DEBUG
void CImageProKimJiHyeonView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProKimJiHyeonView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProKimJiHyeonDoc* CImageProKimJiHyeonView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProKimJiHyeonDoc)));
	return (CImageProKimJiHyeonDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProKimJiHyeonView 메시지 처리기

void CImageProKimJiHyeonView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelAdd();
	viewMode = TWO_IMAGES;

	Invalidate(TRUE);

}

void CImageProKimJiHyeonView::drawImage(CDC* pDC, Mat img, int offset_x, int offset_y)
{
	// TODO: 여기에 구현 코드 추가.
	if (img.empty()) return;
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			if (img.channels() == 1)
				pDC->SetPixel(x + offset_x, y + offset_y,
					RGB(img.at<BYTE>(y, x), img.at<BYTE>(y, x),
						img.at<BYTE>(y, x)));
			else if (img.channels() == 3)
				pDC->SetPixel(x + offset_x, y + offset_y,
					RGB(img.at<Vec3b>(y, x)[2], img.at<Vec3b>(y, x)[1],
						img.at<Vec3b>(y, x)[0]));
	if (drawHist) {
		int hist[256];
		int pixel;

		for (int i = 0; i < 256; i++) hist[i] = 0;  // 히스토그램 초기화

		// 영상에서 0에서 255까지 각각의 값이 몇번  나타나는지 카운트 
		for (int y = 0; y < img.rows; y++)
			for (int x = 0; x < img.cols; x++) {
				if (img.channels() == 1) pixel = img.at<BYTE>(y, x);
				else if (img.channels() == 3)
					pixel = (img.at<Vec3b>(y, x)[0] + img.at<Vec3b>(y, x)[1] +
						img.at<Vec3b>(y, x)[0]) / 3;
				hist[pixel]++;
			}
		float max = 0;
		for (int i = 0; i < 256; i++)
			if (hist[i] > max) max = hist[i];  // 제일 큰 빈도수를 찾음

		// 제일 큰 빈도수에 상대적인 크기를 구하여 세로선을 그림
		//        제일 큰 빈도수 = 1000인경우
		//               제일 큰 빈도수를 갖는 명암값에 대해 길이가 256인 세로선을 그림
		//               빈도수가 500인 명암값에 대해 길이가 128인 세로선을 그림
		//               빈도수가 250인 명암값에 대해 길이가 64인 세로선을 그림
		for (int x = 0; x < 256; x++)
			for (int y = 0; y < hist[x] / max * 256; y++)
				pDC->SetPixel(x + offset_x, 255 - y + img.rows + 30 + offset_y, RGB(0, 0, 0));
	}
}

void CImageProKimJiHyeonView::OnPixelMinus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelMINUS();
	viewMode = TWO_IMAGES;

	Invalidate(TRUE);

}

void CImageProKimJiHyeonView::OnPixelMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelMUL();

	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelDIV();

	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMySave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->resultImg.empty()) return;
	pDoc->MySave();
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelHistoEq();  // CImageProDoc 클래스의 PixelHistoEq() 호출 
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelContrastStretching()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelContrastStretching();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.   

}

void CImageProKimJiHyeonView::OnDrawHistogramOnoff()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (drawHist == false) drawHist = true;
	else drawHist = false;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelBinarizationHRange()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->PixelBinarizationHRange();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CImageProKimJiHyeonView::OnPixelInvert()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelInvert();  // CImageProDoc 클래스의 PixelInvert() 호출 
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->PixelBinarization();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신
}

void CImageProKimJiHyeonView::OnPixelBinarizationAutoThresh()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->PixelBinarizationAutoThresh();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.   

}

void CImageProKimJiHyeonView::OnPixelQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelQuantization();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.   

}

void CImageProKimJiHyeonView::OnPixelRangeHighlighting()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelRangeHighligthing();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.  
}

void CImageProKimJiHyeonView::OnPixelGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->PixelGammaCorrection();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.   

}

void CImageProKimJiHyeonView::OnPixelTwoImagesAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesAdd();

	viewMode = THREE_IMAGES;

	Invalidate(TRUE);

}

void CImageProKimJiHyeonView::OnPixelBinarizationAdaptiveThresh()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->PixelBinarizationAdaptiveTresh();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);      //화면 갱신.   
}
void CImageProKimJiHyeonView::OnPixelTwoImagesAddLogo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesAddLogo();
	viewMode = THREE_IMAGES;
	Invalidate(TRUE);

}

void CImageProKimJiHyeonView::OnPixelTwoImagesMinus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesMinus();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);

}

void CImageProKimJiHyeonView::OnPixelTwoImagesAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesAnd();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelTwoImagesOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesOr();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnPixelTwoImagesXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->PixelTwoImagesXOr();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}
#include "CSlideerDialog.h"

void CImageProKimJiHyeonView::OnPixelBinarizationHRangeSlider()
{
	// TODO: 여기에 구현 코드 추가.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	viewMode = TWO_IMAGES;
	CSlideerDialog sliderDialog;   // 대화상자 인스턴스 생성
	sliderDialog.num_of_sliders = 2;
	sliderDialog.operation = PIXEL_BINARIZATION_H_RANGE;
	sliderDialog.SetValue("H 최소값", 0, 180, 15, "H 최대값", 0, 180, 30);
	sliderDialog.DoModal();
}

void CImageProKimJiHyeonView::OnPixelGammaCorrectionSlider()
{
	// TODO: 여기에 구현 코드 추가.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	viewMode = TWO_IMAGES;
	CSlideerDialog sliderDialog;   // 대화상자 인스턴스 생성
	sliderDialog.num_of_sliders = 1;
	sliderDialog.operation = PIXEL_GAMMA_CORRECTION;
	sliderDialog.SetValue2("감마값", 0.0f, 10.0f, 0.4f, "", 0, 0, 0);
	sliderDialog.DoModal();   // 대화상자가 나타나도록 함

}

void CImageProKimJiHyeonView::OnPixelBinarySlider()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	viewMode = TWO_IMAGES;
	CSlideerDialog sliderDialog;   // 대화상자 인스턴스 생성
	sliderDialog.num_of_sliders = 1;
	sliderDialog.operation = PIXEL_BINARY;
	sliderDialog.SetValue2("임계값", 0.0f, 255.0f, 128.0f, "", 0,0,0);
	sliderDialog.DoModal();
}

void CImageProKimJiHyeonView::OnPixelBinarySlider2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	viewMode = TWO_IMAGES;
	CSlideerDialog sliderDialog;   // 대화상자 인스턴스 생성
	sliderDialog.num_of_sliders = 2;
	sliderDialog.operation = PIXEL_BINARIZATION_H_RANGE;
	sliderDialog.SetValue2("H 최소값", 0, 180, 15, "H 최대값", 0, 180, 30);
	sliderDialog.DoModal();   // 대화상자가 나타나도록 함
}


void CImageProKimJiHyeonView::OnPixelQuantizationSlider()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	viewMode = TWO_IMAGES;
	CSlideerDialog sliderDialog;   // 대화상자 인스턴스 생성
	sliderDialog.num_of_sliders = 1;
	sliderDialog.operation = PIXEL_QUANTIZATION;
	sliderDialog.SetValue2("임계값", 0.0f, 64.0f, 4.0f, "", 0, 0, 0);
	sliderDialog.DoModal();
}

void CImageProKimJiHyeonView::OnRegionBlurring()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionBlurring();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionBlurringGaussian()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionBlurringGaussian();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionBlurringMedian()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionBlurringMedian();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionBlurringBilateral()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionBlurringBilateral();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionSharpening()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionSharpening();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionSobel()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionSobel();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionCanny()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionCanny();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionPrewitt()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionPrewitt();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionRoberts()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionRoberts();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionLaplacian()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionLaplacian();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionEmbossing()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionEmbossing();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnRegionWatercolor()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->RegionWatercolor();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyErosion()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyErosion();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyDilation()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyDilation();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyOpening()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyOpening();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyClosing()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyClosing();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyGradient()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyGradient();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyTopHat()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyTopHat();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyBlackHat()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyBlackHat();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyHitOrMiss()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyHitOrMiss();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyLineDetection()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyLineDetection();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnMorphologyCountCell()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->MorphologyCountCell();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryZoominPixelCopy()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryZoominPixelCopy();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryZoominInterpolation()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryZoominInterpolation();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryZoomoutSubsampling()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryZoomoutSubsampling();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryZoomoutAvg()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryZoomoutAvg();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryRotate()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryRotate();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryFlipVertical()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryFlipVertical();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryFlipHorizontal()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryFlipHorizontal();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryFlipBoth()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryFlipBoth();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryWarping()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->GeometryWarping();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnGeometryMorphing()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->GeometryMorphing();
	viewMode = MORPHING;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnVideoSharpening()
{
	if (vcap.isOpened() == true) {
		vcap.release();
		Invalidate(TRUE);
	}
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		viewMode = VIDEO_FILE;
		operation = SHARPENING;
		vcap.open(dlg.GetPathName().GetString());
		SetTimer(1, 33, 0);
	}
}

void CImageProKimJiHyeonView::OnCameraView()
{
	if (vcap.isOpened() == true) { // 다른 파일이나 카메라가 열려있으면
		vcap.release();            // 닫음
		Invalidate(TRUE);          // 화면을 다시 그림
	}
	operation = VIEW_ONLY;
	viewMode = CAMERA;
	vcap.open(0); // 기본 카메라 열기
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0); // 타이머 콜백 함수에 동영상은 1번, 카메라는 2번을 전달
}

void CImageProKimJiHyeonView::OnCameraSharpening()
{
	// 동영상 파일의 경우에는 영상처리 메뉴를 선택할 때마다 새로운 파일을 열어야 함
	// 하지만 카메라의 경우에는 카메라를 여는데 시간이 많이 걸리고 카메라 영상은 계속 스트리밍됨
	// 따라서 카메라 영상의 경우에는 카메라는 계속 열어두고 영상처리 메뉴(operation)만 변경함
	operation = SHARPENING;
	viewMode = CAMERA;
}

void CImageProKimJiHyeonView::OnCameraSubtract()
{
	operation = SUBTRACT;
	viewMode = CAMERA;
}

void CImageProKimJiHyeonView::OnCameraSaveStart()
{
	operation = SAVE_START;
	viewMode = CAMERA;
}

void CImageProKimJiHyeonView::OnCameraSaveEnd()
{
	operation = SAVE_END;
	viewMode = CAMERA;
}

void CImageProKimJiHyeonView::OnDnnImageClassification()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->inputImg.empty()) return;
	pDoc->DnnImageClassification();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnMosaic()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnMosaic();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnFacialExpressionRecognition()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnFacialExpressionRecognition();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnHumanSegmentation()
{
	operation = HUMAN_SEGMENTATION;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnObjectTracking()
{
	operation = OBJECT_TRACKING;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnQrcodeRecognition()
{
	operation = QRCODE_RECOGNITION;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnDeblurring()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnDeblurring();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnFaceDetection()
{
	operation = FACE_DETECTION;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnFaceMatching()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->DnnFaceMatching();
	viewMode = THREE_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnAgeAndGenderRecognition()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnAgeAndGenderRecognition();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnHumanParsing()
{
	operation = HUMAN_PARSING;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnImageSegmentation()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnImageSegmentation();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnObjectDetection()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnObjectDetection();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnPoseRecognition()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnPoseRecognition();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnDigitsRecognition()
{
	operation = DIGITS_RECOGNITION;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnEnglishWordRecognition()
{
	operation = ENGLISH_WORD_RECOGNITION;
	viewMode = CAMERA;

	vcap.open(0);
	if (!vcap.isOpened())
	{
		AfxMessageBox("Can not open camera");
		return;
	}
	SetTimer(2, 33, 0);
}

void CImageProKimJiHyeonView::OnDnnColorization()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;
	pDoc->DnnColorization();
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnDnnFaceSwapVideo()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFileDialog dlg(TRUE); // 파일 선택 대화상자 객체 선언
	if (vcap.isOpened() == true) {
		vcap.release();
		KillTimer(1);
		Invalidate(TRUE);
	}

	AfxMessageBox("교체에 사용할 얼굴 영상을 선택하시오");
	if (dlg.DoModal() == IDOK) { // 파일 선택 대화 상자 실행
		String fname = dlg.GetPathName();
		pDoc->inputImg = imread(fname); // 파일 닫기
		pDoc->new_swap_image_loaded = true;
	}

	AfxMessageBox("얼굴을 교체할 동영상을 선택하시오");
	if (dlg.DoModal() == IDOK) {
		VideoFileName = dlg.GetPathName();
		viewMode = VIDEO_FILE;
		operation = FACE_SWAP;
		Invalidate(TRUE);
		vcap.open(VideoFileName);
		SetTimer(1, 33, 0);
	}
}

void CImageProKimJiHyeonView::OnDnnLaneDetectionVideo()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFileDialog dlg(TRUE); // 파일 선택 대화상자 객체 선언

	if (vcap.isOpened() == true) {
		vcap.release();
		KillTimer(1);
		Invalidate(TRUE);
	}

	if (dlg.DoModal() == IDOK) {
		VideoFileName = dlg.GetPathName();
		viewMode = VIDEO_FILE;
		operation = LANE_DETECTION;
		vcap.open(VideoFileName);
		SetTimer(1, 33, 0);
	}
}

void CImageProKimJiHyeonView::OnDnnFormulaRecognition()
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) {
		AfxMessageBox(_T("이미지를 먼저 로드하세요."));
		return;
	}
	
	// 고급 수식 인식 함수 호출
	FormulaRecognitionResult result = pDoc->DnnFormulaRecognitionAdvanced();
	
	// 결과가 비어있으면 에러 메시지
	if (result.original_text.empty()) {
		AfxMessageBox(_T("수식을 인식할 수 없습니다."));
		return;
	}
	
	// 다이얼로그 표시
	CFormulaResultDialog dlg;
	dlg.SetResult(result);
	dlg.DoModal();
	
	// 결과 이미지 업데이트
	viewMode = TWO_IMAGES;
	Invalidate(TRUE);
}

void CImageProKimJiHyeonView::OnTimer(UINT_PTR nIDEvent)
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Mat frame;

	vcap >> frame;
	if (frame.empty()) {
		vcap.release();
		KillTimer(nIDEvent); // 타이머 해제
		if (nIDEvent == 1 && operation == FACE_SWAP) {
			pDoc->writer.release(); // 비디오 저장 완료 후 비디오 라이터 해제
			AfxMessageBox("비디오 저장 완료: out.mp4 생성됨");
		}
		return;
	}

	CDC* pDC = GetDC();
	if (nIDEvent == 1) {
		if (operation == SHARPENING) {
			frame.copyTo(pDoc->inputImg);
			pDoc->RegionSharpening();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
		}
		else if (operation == VIEW_ONLY) {
			drawImage(pDC, frame, 0, 0);
		}
		else if (operation == FACE_SWAP) {
			frame.copyTo(pDoc->inputImg2);
			pDoc->DnnFaceSwap();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
			drawImage(pDC, pDoc->faceSwapImg, 0, frame.rows + 30);
		}
		else if (operation == LANE_DETECTION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnLaneDetection();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			vcap.release();
			KillTimer(1);
			Invalidate(TRUE);
		}
	}
	else if (nIDEvent == 2) {
		static Mat image1, image2;
		static int frameNo = 1;
		static int file_opened = false;
		static VideoWriter writer;
		static time_t start_time;

		if (operation == SHARPENING) {
			frame.copyTo(pDoc->inputImg);
			pDoc->RegionSharpening();
			drawImage(pDC, pDoc->inputImg, 0, 0);
			drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
		}
		else if (operation == SAVE_START) {
			if (file_opened == false) {
				int codec = VideoWriter::fourcc('X', '2', '6', '4'); // H.264
				double fps = 25.0;
				char filename[26];
				start_time = time(NULL); // 1970/1/1 0시(UTC)부터 현재까지 흐른 초시간
				struct tm local_time; // 년, 월, 일, 시, 분, 초 등을 포함하는 구조체
				localtime_s(&local_time, &start_time); // 앞의 초 시간을 년, 월, 일, 시, 분, 초로 변환
				// 20250717_153030.mp4와 같이 년, 월, 일, 시, 분, 초로 파일 이름 생성
				strftime(filename, sizeof(filename), "%Y%m%d_%H%M%S.mp4", &local_time);
				writer.open(filename, codec, fps, frame.size(), true);
				file_opened = true;
			}
			writer.write(frame);
			time_t now = time(NULL);
			string label = format("Recording ... : %d Second", now - start_time);
			putText(frame, label, Point(100, frame.rows - 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
			drawImage(pDC, frame, 0, 0);
		}
		else if (operation == SAVE_END) {
			writer.release();
			file_opened = false;
			operation = VIEW_ONLY;
		}
		else if (operation == VIEW_ONLY) {
			drawImage(pDC, frame, 0, 0);
		}
		else if (operation == HUMAN_SEGMENTATION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnHumanSegmentation();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
		}
		else if (operation == HUMAN_PARSING) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnHumanParsing();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
		}
		else if (operation == DIGITS_RECOGNITION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnDigitsRecognition();
			drawImage(pDC, pDoc->inputImg, 0, 0);
			drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
		}
		else if (operation == ENGLISH_WORD_RECOGNITION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnEnglishWordRecognition();
			drawImage(pDC, pDoc->inputImg, 0, 0);
			drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
		}
		else if (operation == OBJECT_TRACKING) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnObjectTracking(-1, -1, -1, -1);
			drawImage(pDC, pDoc->inputImg, 0, 0);
			drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
		}
		else if (operation == QRCODE_RECOGNITION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnQrcodeRecognition();
			drawImage(pDC, frame, 0, 0);
			drawImage(pDC, pDoc->resultImg, frame.cols + 30, 0);
		}
		else if (operation == FACE_DETECTION) {
			frame.copyTo(pDoc->inputImg);
			pDoc->DnnFaceDetection();
			drawImage(pDC, pDoc->inputImg, 0, 0);
			drawImage(pDC, pDoc->resultImg, pDoc->inputImg.cols + 30, 0);
		}
		else if (operation == SUBTRACT) {
			// static : 함수가 계속 다시 호출되어도 변수값 유지
			// 이전 프레임과의 차이를 계산해야 하므로 이전 프레임 영상을 유지해야 함
			// image1, image2, frameNo는 이미 위에서 static으로 선언됨

			if (frameNo == 1) {
				frame.copyTo(image1);
			}
			else if (frameNo == 2) {
				frame.copyTo(image2);
			}
			else {
				image2.copyTo(image1);
				frame.copyTo(image2);
			}

			if (frameNo >= 2) {
				if (frame.channels() == 1) {
					for (int y = 0; y < frame.rows; y++) {
						for (int x = 0; x < frame.cols; x++) {
							BYTE p1 = image1.at<BYTE>(y, x);
							BYTE p2 = image2.at<BYTE>(y, x);
							// 두 프레임의 각 픽셀 간에 명암도 차이가 20보다 크면 흰색
							if (fabs((double)p1 - (double)p2) > 20.0) {
								frame.at<BYTE>(y, x) = 255;
							}
							else {
								frame.at<BYTE>(y, x) = 0;
							}
						}
					}
				}
				else if (frame.channels() == 3) {
					for (int y = 0; y < frame.rows; y++) {
						for (int x = 0; x < frame.cols; x++) {
							Vec3b p1 = image1.at<Vec3b>(y, x);
							Vec3b p2 = image2.at<Vec3b>(y, x);
							// 두 프레임의 각 픽셀 간에 명암도 차이가 20보다 크면 흰색
							if (fabs((p1[0] + p1[1] + p1[2]) / 3 - (p2[0] + p2[1] + p2[2]) / 3) > 20.0) {
								frame.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
							}
							else {
								frame.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
							}
						}
					}
				}
				drawImage(pDC, image2, 0, 0);
				drawImage(pDC, frame, image2.cols + 30, 0);
			}
			frameNo++;
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			vcap.release();
			KillTimer(2);
			Invalidate(TRUE);
		}
	}
	ReleaseDC(pDC);
	CScrollView::OnTimer(nIDEvent);
}

void CImageProKimJiHyeonView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (operation == WARPING_MOUSE || operation == FACE_TRACKING || operation == OBJECT_TRACKING) {
		Ax = point.x; // 시작 위치를 (Ax, Ay)로 설정
		Ay = point.y;
		Bx = point.x;
		By = point.y;
		mouse_input_started = TRUE; // 마우스 입력 시작 설정
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CImageProKimJiHyeonView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CImageProKimJiHyeonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->inputImg.empty()) return;

	if (operation == WARPING_MOUSE && mouse_input_started == TRUE) {
		Bx = point.x; // 현재 위치 저장
		By = point.y;
		mouse_input_started = FALSE; // 마우스 입력 종료
		pDoc->GeometryWarpingMouse(Ax, Ay, Bx, By); // 워핑 함수 호출
		Invalidate(FALSE);
	}
	else if (operation == FACE_TRACKING && mouse_input_started == TRUE) {
		Bx = point.x; // 현재 위치 저장
		By = point.y;
		mouse_input_started = FALSE; // 마우스 입력 종료
		pDoc->FaceTracking(Ax, Ay, Bx, By);
	}
	else if (operation == OBJECT_TRACKING && mouse_input_started == TRUE) {
		Bx = point.x; // 현재 위치 저장
		By = point.y;
		mouse_input_started = FALSE; // 마우스 입력 종료
		pDoc->DnnObjectTracking(Ax, Ay, Bx, By);
		Invalidate(FALSE);
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CImageProKimJiHyeonView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((operation == WARPING_MOUSE || operation == FACE_TRACKING || operation == OBJECT_TRACKING) && mouse_input_started == TRUE) {
		Bx = point.x; // 현재 위치를 (Bx, By)로 설정
		By = point.y; // (Ax, Ay)에서 (Bx,By)로 직선을 그림
		Invalidate(FALSE); // 화면을 새로 그림
	}
	CScrollView::OnMouseMove(nFlags, point);
}