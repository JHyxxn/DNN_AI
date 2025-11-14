# DNN AI - 이미지에서 수식 인식 및 계산

## 프로젝트 개요

이미지에서 수학 수식을 인식하고 자동으로 계산 결과를 제공하는 DNN 기반 AI 모델 프로젝트입니다.

## 주요 기능

- **수식 이미지 입력**: 사진, 스크린샷, 손글씨 등 다양한 형태의 수식 이미지 처리
- **고급 이미지 전처리**: CLAHE, 이진화 등 손글씨 인식 정확도 향상
- **OCR 기반 텍스트 추출**: 딥러닝 OCR 모델을 활용한 수식 텍스트 인식 (여러 줄 처리)
- **고급 수식 파싱**: 지수, 삼각함수, 로그, 제곱근, 절댓값, 분수, 등호 처리
- **자동 계산**: 스택 기반 계산기로 복잡한 수식 자동 계산
- **다양한 출력 형식**: AsciiMath, LaTeX, HTML, JSON 형식 지원
- **신뢰도 표시**: OCR 신뢰도 및 계산 성공 여부 표시
- **결과 시각화**: 탭 기반 다이얼로그로 결과 표시 (Text, HTML, Data)

## 작동 원리

```
[수식 이미지 입력]
    ↓
[이미지 전처리] - 그레이스케일, 노이즈 제거, CLAHE, 이진화, 크기 조정
    ↓
[OCR - 수식 텍스트 추출] - Text Detection + Text Recognition (줄별 처리)
    ↓
[수식 정규화] - 특수 문자 변환 (× → *, ÷ → /, ² → ^2, √ → sqrt)
    ↓
[고급 처리] - 함수 처리, 분수 처리, 절댓값 처리
    ↓
[형식 변환] - AsciiMath, LaTeX 변환
    ↓
[수식 계산] - 스택 기반 계산 (우선순위, 괄호, 지수, 함수)
    ↓
[신뢰도 계산] - OCR 신뢰도 + 계산 성공 여부
    ↓
[결과 출력] - Text/HTML/JSON 형식으로 표시
```

## 기술 스택

- **프레임워크**: OpenCV DNN
- **OCR 모델**: 
  - Text Detection: DBNet (PPOCRv3)
  - Text Recognition: CRNN
- **언어**: C++ (MFC)
- **개발 환경**: Visual Studio 2022

## 지원 수식 유형

### ✅ 기본 연산 (구현 완료)
- 기본 연산: `2 + 3`, `10 - 5`, `4 * 6`, `8 / 2`
- 복합 연산: `2 + 3 * 4`, `(2 + 3) * 4`
- 소수점 연산: `3.5 + 2.7`
- 우선순위 처리: 곱셈/나눗셈이 덧셈/뺄셈보다 우선

### ✅ 고급 연산 (구현 완료)
- **거듭제곱**: `2³`, `2^3`, `x²`
- **삼각함수**: `sin(30°)`, `cos(45°)`, `tan(60°)`, `sinh()`, `cosh()`, `tanh()`
- **로그 함수**: `log₁₀(100)`, `ln(e)`
- **제곱근**: `√16`, `sqrt(9)`
- **지수 함수**: `exp(2)`
- **절댓값**: `|x - 5|`
- **분수 계산**: `1/2 + 1/3`
- **등호 처리**: `2x + 3 = 11` (방정식)

### ✅ 출력 형식 (구현 완료)
- **AsciiMath**: 수식을 AsciiMath 형식으로 변환
- **LaTeX**: Mathpix 수준의 LaTeX 변환 (`\frac{}`, `\sqrt{}`, `\sin()` 등)
- **HTML**: 웹에서 사용 가능한 HTML 형식
- **JSON**: 구조화된 데이터 형식
- **신뢰도 표시**: OCR 신뢰도 및 계산 성공 여부

### 🔄 향후 확장
- 변수 포함 수식: `x + 5 = 10` (변수 해결)
- 행렬 연산
- 적분/미분 기호

## 시스템 아키텍처

```
┌───────────────────────────────────────┐
│         Image Input (Mat)             │
└──────────────┬────────────────────────┘
                │
                ↓
┌───────────────────────────────────────┐
│      Step 1: Image Preprocessing      │
│  - Grayscale conversion               │
│  - Noise removal (Gaussian Blur)      │
│  - Binarization (OTSU)                │
│  - Resize (736x736 for OCR)           │
└──────────────┬────────────────────────┘
                │
                ↓
┌───────────────────────────────────────┐
│      Step 2: OCR (Text Extraction)    │
│  - Text Detection (DB Net)            │
│  - Text Recognition (CRNN)            │
│  - Formula text: "2 + 3 × 4"          │
└──────────────┬────────────────────────┘
                │
                ↓
┌───────────────────────────────────────┐
│      Step 3: Formula Normalization    │
│  - × → *                              │
│  - ÷ → /                              │
│  - ² → ^2                             │
│  - 공백 제거                           │
└──────────────┬────────────────────────┘
                │
                ↓
┌────────────────────────────────────────┐
│      Step 4: Formula Parsing           │
│  - Tokenize: ["2", "+", "3", "*", "4"] │
│  - Build Expression Tree               │
│  - Handle operator precedence          │
└──────────────┬─────────────────────────┘
                │
                ↓
┌───────────────────────────────────────┐
│      Step 5: Expression Evaluation    │
│  - Evaluate expression tree           │
│  - Result: 14                         │
└──────────────┬────────────────────────┘
                │
                ↓
┌─────────────────────────────────────────┐
│      Step 6: Result Visualization       │
│  - Draw original image                  │
│  - Display formula text                 │
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
│ Result: 14.00       │
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

## 구현 완료 사항

- ✅ 손글씨 수식 인식 (이미지 전처리 강화: CLAHE, 이진화)
- ✅ 복잡한 수학 함수 지원 (삼각함수, 로그, 제곱근, 지수, 절댓값)
- ✅ 여러 줄 수식 처리 (Y 좌표 정렬)
- ✅ 등호 처리 및 방정식 계산
- ✅ LaTeX 변환 (Mathpix 수준)
- ✅ 신뢰도 계산 및 표시
- ✅ 다양한 출력 형식 (Text, HTML, JSON)

## 향후 개선 사항

- [ ] 손글씨 인식 정확도 추가 향상
- [ ] 변수 포함 수식 처리 (변수 해결)
- [ ] 행렬 연산 지원
- [ ] 적분/미분 기호 처리
- [ ] 단계별 계산 과정 표시

## 참고 자료

- OpenCV DNN: https://docs.opencv.org/4.x/d6/d0f/group__dnn.html
- PPOCR: https://github.com/PaddlePaddle/PaddleOCR
- CRNN: https://github.com/bgshih/crnn

## 라이선스

이 프로젝트는 교육 목적으로 개발되었습니다.
