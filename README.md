# DNN AI - 이미지에서 수식 인식 및 계산

## 프로젝트 개요

이미지에서 수학 수식을 인식하고 자동으로 계산 결과를 제공하는 DNN 기반 AI 모델 프로젝트입니다.

## 주요 기능

- **수식 이미지 입력**: 사진, 스크린샷, 손글씨 등 다양한 형태의 수식 이미지 처리
- **OCR 기반 텍스트 추출**: 딥러닝 OCR 모델을 활용한 수식 텍스트 인식
- **수식 파싱 및 계산**: 인식된 수식을 파싱하여 자동 계산
- **결과 시각화**: 원본 이미지에 인식된 수식과 계산 결과를 함께 표시

## 작동 원리

```
[수식 이미지 입력]
    ↓
[이미지 전처리] - 노이즈 제거, 이진화, 크기 조정
    ↓
[OCR - 수식 텍스트 추출] - Text Detection + Text Recognition
    ↓
[수식 정규화] - 특수 문자 변환 (× → *, ÷ → /, ² → ^2)
    ↓
[수식 파싱] - 토큰화 및 표현식 트리 생성
    ↓
[계산 수행] - 수식 평가 및 결과 계산
    ↓
[결과 시각화] - 원본 이미지 + 수식 + 계산 결과 표시
```

## 기술 스택

- **프레임워크**: OpenCV DNN
- **OCR 모델**: 
  - Text Detection: DBNet (PPOCRv3)
  - Text Recognition: CRNN
- **언어**: C++ (MFC)
- **개발 환경**: Visual Studio 2022

## 지원 수식 유형

### Phase 1 (기본 구현)
- 기본 연산: `2 + 3`, `10 - 5`, `4 * 6`, `8 / 2`
- 복합 연산: `2 + 3 * 4`, `(2 + 3) * 4`
- 소수점 연산: `3.5 + 2.7`
- 우선순위 처리: 곱셈/나눗셈이 덧셈/뺄셈보다 우선

### Phase 2 (확장 예정)
- 거듭제곱: `2^3`, `x^2`
- 삼각함수: `sin(30)`, `cos(45)`, `tan(60)`
- 복잡한 괄호: `(2 + 3) * (4 - 1) / 2`
- 변수 포함 수식: `x + 5 = 10` (미래 확장)

## 시스템 아키텍처

```
┌─────────────────────────────────────────┐
│         Image Input (Mat)               │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 1: Image Preprocessing        │
│  - Grayscale conversion                 │
│  - Noise removal (Gaussian Blur)        │
│  - Binarization (OTSU)                  │
│  - Resize (736x736 for OCR)             │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 2: OCR (Text Extraction)     │
│  - Text Detection (DB Net)              │
│  - Text Recognition (CRNN)              │
│  - Formula text: "2 + 3 × 4"           │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 3: Formula Normalization     │
│  - × → *                                 │
│  - ÷ → /                                 │
│  - ² → ^2                                │
│  - 공백 제거                             │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 4: Formula Parsing           │
│  - Tokenize: ["2", "+", "3", "*", "4"] │
│  - Build Expression Tree                │
│  - Handle operator precedence           │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 5: Expression Evaluation      │
│  - Evaluate expression tree             │
│  - Result: 14                           │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 6: Result Visualization       │
│  - Draw original image                   │
│  - Display formula text                  │
│  - Display calculation result           │
└─────────────────────────────────────────┘
```

## 구현 설계

### 주요 함수 구조

```cpp
// 메인 함수
void DnnFormulaRecognition();

// 내부 헬퍼 함수들
string extractFormulaText(const Mat& img);      // OCR 수행
string normalizeFormula(const string& formula);  // 수식 정규화
vector<string> tokenizeFormula(const string& formula); // 토큰화
double evaluateExpression(const string& formula); // 계산 수행
Mat preprocessImage(const Mat& input);          // 이미지 전처리
```

### 데이터 구조

```cpp
enum TokenType {
    NUMBER,
    OPERATOR_ADD,      // +
    OPERATOR_SUB,      // -
    OPERATOR_MUL,      // ×, *
    OPERATOR_DIV,      // ÷, /
    OPERATOR_POW,      // ^
    PARENTHESIS_OPEN,  // (
    PARENTHESIS_CLOSE, // )
    FUNCTION,          // sin, cos, etc.
    UNKNOWN
};

struct FormulaToken {
    string value;
    TokenType type;
};
```

## 예상 구현 시간

- 이미지 전처리: 1시간
- OCR 통합: 2시간 (기존 코드 활용)
- 수식 파싱: 3-4시간
- 계산 로직: 2-3시간
- 시각화 및 통합: 2시간
- 테스트 및 디버깅: 2-3시간

**총 예상 시간: 1~2일**

## 시각화 예시

```
원본 이미지:
┌─────────────────────┐
│                     │
│     2 + 3 × 4       │
│                     │
└─────────────────────┘

결과 이미지:
┌─────────────────────┐
│ Formula: 2 + 3 × 4  │
│ Result: 14.00        │
│                     │
│     2 + 3 × 4       │
│                     │
└─────────────────────┘
```

## 활용 사례

1. **학습 자료 분석**: 문제집, 교과서의 수식 자동 검증
2. **수식 검증**: 손으로 쓴 수식의 계산 결과 확인
3. **자동 채점**: 수학 문제 답안 검증
4. **접근성 향상**: 시각 장애인을 위한 수식 읽기 보조

## 예외 처리

- OCR 실패 시: 에러 메시지 표시
- 수식 파싱 실패 시: "Parsing Error" 표시
- 계산 오류 시: "Calculation Error" 표시 (예: 0으로 나누기)
- 빈 이미지 입력 시: 경고 메시지

## 향후 개선 사항

- [ ] 손글씨 수식 인식 정확도 향상
- [ ] 복잡한 수학 함수 지원 (삼각함수, 로그 등)
- [ ] 변수 포함 수식 처리
- [ ] 다중 수식 인식 (한 이미지에 여러 수식)
- [ ] 단계별 계산 과정 표시

## 참고 자료

- OpenCV DNN: https://docs.opencv.org/4.x/d6/d0f/group__dnn.html
- PPOCR: https://github.com/PaddlePaddle/PaddleOCR
- CRNN: https://github.com/bgshih/crnn

## 라이선스

이 프로젝트는 교육 목적으로 개발되었습니다.
