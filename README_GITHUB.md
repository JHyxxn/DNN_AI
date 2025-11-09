# GitHub 업로드 가이드

## 📁 포함된 파일들

### 소스 코드
- 모든 `.cpp`, `.h` 파일
- 프로젝트 파일 (`.sln`, `.vcxproj`, `.vcxproj.filters`)
- 리소스 파일 (`.rc`, `resource.h`)

### 문서
- `README.md` - 프로젝트 개요
- `DESIGN.md` - 상세 설계 문서

### 리소스
- `res/` 폴더 - 아이콘, 이미지 등

## 🚫 제외된 파일들 (용량 절약)

### 빌드 결과물
- `Debug/`, `x64/`, `Release/` 폴더
- `.obj`, `.pdb`, `.exe` 파일

### 테스트 파일
- `간단한_테스트_이미지_만들기.md`
- `발표용_테스트_수식.txt`
- `README_TEST_IMAGES.md`

### 대용량 파일
- DNN 모델 파일 (`.onnx`, `.pb`, `.caffemodel` 등)
- 백업 파일 (`*_backup.*`, `*_new.*`)

## 📝 GitHub 업로드 방법

```bash
cd c:\Users\yhKim\Desktop\DNN_AI

# Git 초기화 (처음만)
git init

# 파일 추가
git add .

# 커밋
git commit -m "Initial commit: 수식 인식 및 계산 기능"

# 원격 저장소 연결 (GitHub 저장소 URL)
git remote add origin https://github.com/사용자명/저장소명.git

# 업로드
git push -u origin main
```

## ⚠️ 주의사항

1. **모델 파일은 업로드하지 마세요**
   - `.onnx`, `.pb` 파일은 용량이 큽니다
   - 로컬에서만 사용하세요

2. **개인 정보 확인**
   - 코드에 개인 정보가 있는지 확인하세요
   - API 키, 비밀번호 등은 제거하세요

3. **.gitignore 확인**
   - `.gitignore` 파일이 제대로 작동하는지 확인하세요

