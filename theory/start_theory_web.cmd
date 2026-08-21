@echo off
setlocal
chcp 65001 >nul
title BOJ Theory Map
cd /d "%~dp0"

where node >nul 2>&1
if errorlevel 1 (
    echo [오류] Node.js를 찾지 못했습니다.
    echo 이 PC에서는 node 명령으로 로컬 학습 웹을 실행합니다.
    echo.
    pause
    exit /b 1
)

node "%~dp0server.mjs"
set "THEORY_EXIT=%ERRORLEVEL%"

if not "%THEORY_EXIT%"=="0" (
    echo.
    echo 서버가 비정상 종료되었습니다. 위 오류를 확인해 주세요.
    pause
)

exit /b %THEORY_EXIT%
