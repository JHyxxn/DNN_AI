# 이미지에서 수식 인식 및 계산 - 상세 설계 문서

## 1. 전체 개요

### 1.1 목표
이미지에서 수학 수식을 인식하고 자동으로 계산 결과를 제공하는 DNN 기반 시스템

### 1.2 입력/출력
- **입력**: 수식이 포함된 이미지 (예: "2 + 3 × 4", "x² + 5x + 6")
- **출력**: 인식된 수식 텍스트 + 계산 결과

### 1.3 활용 사례
- 학습 자료 분석: 문제집, 교과서 수식 검증
- 수식 검증: 손으로 쓴 수식 계산 확인
- 자동 채점: 수학 문제 답안 검증

## 2. 작동 원리

```
[수식 이미지 입력]
    ↓
[전처리] - 노이즈 제거, 이진화, 크기 조정
    ↓
[OCR - 수식 텍스트 추출]
    ↓
[수식 파싱] - 텍스트를 수식 구조로 변환
    ↓
[계산 수행] - 수식 평가
    ↓
[결과 시각화] - 원본 이미지 + 수식 + 결과 표시
```

## 3. 상세 설계

### 3.1 이미지 전처리

**목적**: OCR 정확도 향상을 위한 이미지 품질 개선

**처리 단계**:
1. 그레이스케일 변환 (컬러 → 흑백)
2. 노이즈 제거 (Gaussian Blur)
3. 이진화 (OTSU 임계값)
4. 크기 조정 (OCR 모델 입력 크기에 맞춤: 736x736)

**구현**:
```cpp
Mat preprocessImage(const Mat& input)
{
    Mat processed;
    
    // 1. 그레이스케일 변환
    if (input.channels() == 3)
        cvtColor(input, processed, COLOR_BGR2GRAY);
    else
        processed = input.clone();
    
    // 2. 노이즈 제거
    GaussianBlur(processed, processed, Size(3, 3), 0);
    
    // 3. 이진화
    threshold(processed, processed, 0, 255, 
              THRESH_BINARY + THRESH_OTSU);
    
    // 4. 크기 조정
    resize(processed, processed, Size(736, 736));
    
    return processed;
}
```

### 3.2 OCR (텍스트 추출)

**목적**: 이미지에서 수식 텍스트 추출

**사용 모델**:
- Text Detection: DBNet (PPOCRv3) - `text_detection_en_ppocrv3_2023may.onnx`
- Text Recognition: CRNN - `text_recognition_CRNN_CH_2021sep.onnx`

**처리 단계**:
1. 텍스트 영역 검출 (DBNet)
2. 각 영역에서 텍스트 인식 (CRNN)
3. 인식된 텍스트 결합

**구현**:
```cpp
string extractFormulaText(const Mat& img)
{
    // 1. Text Detection
    Mat detections;
    td_model.detect(img, detections);
    
    // 2. Text Recognition
    string formula_text = "";
    for (int i = 0; i < detections.rows; i++) {
        Mat text_roi = extractROI(img, detections, i);
        string text = recognizeText(text_roi, tr_model);
        formula_text += text + " ";
    }
    
    return formula_text;
}
```

### 3.3 수식 정규화

**목적**: OCR 결과를 계산 가능한 형식으로 변환

**변환 규칙**:
- `×` → `*`
- `÷` → `/`
- `²` → `^2`
- `³` → `^3`
- 공백 제거

**구현**:
```cpp
string normalizeFormula(const string& formula)
{
    string normalized = formula;
    
    // 공백 제거
    normalized.erase(remove(normalized.begin(), normalized.end(), ' '), 
                     normalized.end());
    
    // 특수 문자 변환
    replace(normalized.begin(), normalized.end(), '×', '*');
    replace(normalized.begin(), normalized.end(), '÷', '/');
    replace(normalized.begin(), normalized.end(), '²', '^');
    
    return normalized;
}
```

### 3.4 수식 토큰화

**목적**: 수식을 의미 있는 단위로 분리

**토큰 타입**:
- NUMBER: 숫자 (정수, 소수)
- OPERATOR: 연산자 (+, -, *, /, ^)
- PARENTHESIS: 괄호 ((, ))
- FUNCTION: 함수 (sin, cos, tan)

**구현**:
```cpp
vector<string> tokenizeFormula(const string& formula)
{
    vector<string> tokens;
    string current_token = "";
    
    for (char c : formula) {
        if (isdigit(c) || c == '.') {
            current_token += c;  // 숫자 누적
        }
        else if (isOperator(c)) {
            if (!current_token.empty()) {
                tokens.push_back(current_token);
                current_token = "";
            }
            tokens.push_back(string(1, c));  // 연산자 추가
        }
        // ... 기타 처리
    }
    
    return tokens;
}
```

### 3.5 수식 계산

**목적**: 토큰화된 수식을 계산하여 결과 도출

**계산 방법**: 스택 기반 계산기 (Shunting Yard 알고리즘)

**연산자 우선순위**:
1. 괄호: `()`
2. 거듭제곱: `^`
3. 곱셈/나눗셈: `*`, `/`
4. 덧셈/뺄셈: `+`, `-`

**구현**:
```cpp
double evaluateExpression(const string& formula)
{
    // 1. 정규화
    string normalized = normalizeFormula(formula);
    
    // 2. 토큰화
    vector<string> tokens = tokenizeFormula(normalized);
    
    // 3. 스택 기반 계산
    stack<double> numbers;
    stack<char> operators;
    
    for (const string& token : tokens) {
        if (isNumber(token)) {
            numbers.push(stod(token));
        }
        else if (isOperator(token[0])) {
            // 우선순위 처리
            while (!operators.empty() && 
                   precedence(operators.top()) >= precedence(token[0])) {
                evaluateTop(numbers, operators);
            }
            operators.push(token[0]);
        }
        // ... 괄호 처리
    }
    
    return numbers.top();
}
```

### 3.6 결과 시각화

**목적**: 원본 이미지에 인식된 수식과 계산 결과 표시

**표시 내용**:
- 인식된 수식 텍스트
- 계산 결과
- 에러 메시지 (오류 발생 시)

**구현**:
```cpp
void DnnFormulaRecognition()
{
    // ... 전처리 및 OCR ...
    
    // 결과 시각화
    resultImg = inputImg.clone();
    
    // 수식 표시
    string display_text = "Formula: " + formula_text;
    putText(resultImg, display_text, Point(10, 30),
            FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    
    // 계산 결과 표시
    if (calculation_success) {
        string result_text = format("Result: %.2f", result);
        putText(resultImg, result_text, Point(10, 60),
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
    }
}
```

## 4. 예외 처리

### 4.1 OCR 실패
- **상황**: 수식을 인식하지 못함
- **처리**: "수식을 인식할 수 없습니다" 메시지 표시

### 4.2 수식 파싱 실패
- **상황**: 인식된 텍스트가 유효한 수식이 아님
- **처리**: "Parsing Error" 메시지 표시

### 4.3 계산 오류
- **상황**: 0으로 나누기, 잘못된 연산 등
- **처리**: "Calculation Error" 메시지 표시

### 4.4 빈 이미지
- **상황**: 입력 이미지가 없음
- **처리**: "이미지를 먼저 로드하세요" 경고

## 5. 지원 수식 예시

### Phase 1 (기본)
- `2 + 3` → 5
- `10 - 5` → 5
- `4 * 6` → 24
- `8 / 2` → 4
- `2 + 3 * 4` → 14
- `(2 + 3) * 4` → 20
- `3.5 + 2.7` → 6.2

### Phase 2 (확장 예정)
- `2^3` → 8
- `sin(30)` → 0.5
- `(2 + 3) * (4 - 1) / 2` → 7.5

## 6. 구현 순서

1. ✅ 이미지 전처리 함수 작성
2. ✅ OCR 함수 작성 (기존 코드 활용)
3. ✅ 수식 정규화 함수 작성
4. ✅ 간단한 계산기 구현 (기본 연산)
5. ✅ 메인 함수 통합
6. ✅ 시각화 추가
7. ✅ 예외 처리 추가
8. ⏳ 테스트 및 디버깅

## 7. 파일 구조

```
ImagePro_Kim_Ji_Hyeon/
├── ImagePro_Kim_Ji_HyeonDoc.h
│   └── void DnnFormulaRecognition();
├── ImagePro_Kim_Ji_HyeonDoc.cpp
│   ├── void DnnFormulaRecognition()      // 메인 함수
│   ├── string extractFormulaText()       // OCR
│   ├── string normalizeFormula()         // 정규화
│   ├── vector<string> tokenizeFormula()   // 토큰화
│   ├── double evaluateExpression()        // 계산
│   └── Mat preprocessImage()             // 전처리
└── README.md
```

## 8. 테스트 케이스

### 테스트 1: 기본 연산
- 입력: `2 + 3` 이미지
- 예상 출력: "Formula: 2 + 3, Result: 5.00"

### 테스트 2: 복합 연산
- 입력: `2 + 3 * 4` 이미지
- 예상 출력: "Formula: 2 + 3 * 4, Result: 14.00"

### 테스트 3: 괄호 포함
- 입력: `(2 + 3) * 4` 이미지
- 예상 출력: "Formula: (2 + 3) * 4, Result: 20.00"

### 테스트 4: 소수점
- 입력: `3.5 + 2.7` 이미지
- 예상 출력: "Formula: 3.5 + 2.7, Result: 6.20"

## 9. 향후 개선 사항

- [ ] 손글씨 수식 인식 정확도 향상
- [ ] 복잡한 수학 함수 지원
- [ ] 변수 포함 수식 처리
- [ ] 다중 수식 인식
- [ ] 단계별 계산 과정 표시
- [ ] 실시간 카메라 입력 지원

