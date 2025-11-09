
// ImagePro_Kim_Ji_HyeonDoc.h: CImageProKimJiHyeonDoc 클래스의 인터페이스
//

#pragma once

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/wechat_qrcode.hpp>
#include <math.h>
#include <fstream>
using namespace cv;
using namespace std;
using namespace dnn;

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
} control_line;

// 수식 인식 결과 구조체
struct FormulaRecognitionResult {
	string original_text;      // 원본 인식 텍스트
	string asciimath;          // AsciiMath 형식
	string latex;              // LaTeX 형식
	double calculation_result;  // 계산 결과
	double confidence;          // OCR 신뢰도 (0.0 ~ 1.0)
	double confidence_rate;     // 전체 신뢰도
	bool calculation_success;  // 계산 성공 여부
	vector<string> detected_texts; // 인식된 텍스트 영역들
	vector<float> text_confidences; // 각 텍스트 영역의 신뢰도
};

class CImageProKimJiHyeonDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProKimJiHyeonDoc() noexcept;
	DECLARE_DYNCREATE(CImageProKimJiHyeonDoc)

// 특성입니다.
public:
	Mat inputImg;
	Mat inputImg2;
	Mat resultImg;
	Mat morphedImg[10]; // 모핑 결과 저장을 위해 새로이 추가되는 코드
	Mat faceSwapImg; // 교체 얼굴 이미지
	VideoWriter writer; // 출력 동영상 파일
	int new_swap_image_loaded = false; // 교체 얼굴 이미지 로드 여부
	

// 작업입니다.
public:
	int m_nThreshold = 128;

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProKimJiHyeonDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void PixelAdd();
	void PixelMINUS();
	void PixelMUL();
	void PixelDIV();
	void MySave();
	void PixelHistoEq();
	void PixelBinarization();
	void PixelContrastStretching();
	void PixelBinarizationHRange();
	void PixelInvert();
	void PixelBinarizationAutoTresh();
	void PixelQuantization();
	void PixelBinarizationAutoThresh();
	void PixelRangeHighligthing();
	void PixelGammaCorrection();
	void PixelTwoImagesAdd();
	void LoadTwoImages();
	void PixelBinarizationAdaptiveTresh();
	void PixelTwoImagesAddLogo();
	void PixelTwoImagesMinus();
	void PixelTwoImagesAnd();
	void PixelTwoImagesOr();
	void PixelTwoImagesXOr();
	void PixelBinarizationHRangeSlider(int min, int max);
	void PixelGammaCorrectionSlider(float gamma);
	void PixelBinarySlider(int threshold);
	void PixelGammaCorrectionSlider2(float gamma);
	void PixelQuantizations(int levels);
	void RegionBlurring();
	void RegionBlurringGaussian();
	void RegionBlurringMedian();
	void RegionBlurringBilateral();
	void RegionSharpening();
	void RegionSobel();
	void RegionCanny();
	void RegionPrewitt();
	void RegionRoberts();
	void RegionLaplacian();
	void RegionEmbossing();
	void RegionWatercolor();
	void MorphologyErosion();
	void MorphologyDilation();
	void MorphologyOpening();
	void MorphologyClosing();
	void MorphologyGradient();
	void MorphologyTopHat();
	void MorphologyBlackHat();
	void MorphologyHitOrMiss();
	void MorphologyLineDetection();
	void MorphologyCountCell();
	void GeometryZoominPixelCopy();
	void GeometryZoominInterpolation();
	void GeometryZoomoutSubsampling();
	void GeometryZoomoutAvg();
	void GeometryRotate();
	void GeometryFlipVertical();
	void GeometryFlipHorizontal();
	void GeometryFlipBoth();
	void GeometryWarping();
	void GeometryWarpingMouse(int Ax, int Ay, int Bx, int By);
	void GeometryMorphing();
	void FaceTracking(int Ax, int Ay, int Bx, int By);
	void DnnImageClassification();
	void DnnMosaic();
	void DnnFacialExpressionRecognition();
	void DnnHumanSegmentation();
	void DnnObjectTracking(int Ax, int Ay, int Bx, int By);
	void DnnQrcodeRecognition();
	void DnnDeblurring();
	void DnnFaceDetection();
	void DnnFaceMatching();
	void DnnAgeAndGenderRecognition();
	void DnnHumanParsing();
	void DnnImageSegmentation();
	void DnnObjectDetection();
	void DnnPoseRecognition();
	void DnnDigitsRecognition();
	void DnnEnglishWordRecognition();
	void DnnColorization();
	void DnnFaceSwap();
	bool detect_face_and_landmarks(Mat& image, Rect& out_box, vector<Point2f>& out_landmarks);
	Mat align_face(Mat& image, vector<Point2f>& src_pts, Mat& mat, int output_size);
	void DnnLaneDetection();
	void DnnFormulaRecognition();
	FormulaRecognitionResult DnnFormulaRecognitionAdvanced();
	double evaluateSimpleExpression(const string& formula);
	string preprocessSquareRoot(const string& formula);
	string preprocessAbsoluteValue(const string& formula);
	string normalizeFunctionNames(const string& formula);
	string preprocessFunctions(const string& formula);
	string preprocessFractions(const string& formula);
	string preprocessVariables(const string& formula);
	double evaluateWithExponent(const string& formula);
	
	// 새로운 변환 함수들
	string convertToAsciiMath(const string& formula);
	string convertToLaTeX(const string& formula);
	string generateHTMLOutput(const FormulaRecognitionResult& result);
	string generateJSONOutput(const FormulaRecognitionResult& result);
	double calculateConfidence(const vector<float>& confidences);
	string escapeJSON(const string& str);
	string escapeHTML(const string& str);
};
