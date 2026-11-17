@echo off
setlocal
cd /d "%~dp0.."
where cmake >nul 2>nul || (echo CMake not found. Install CMake 3.25+ and retry.& pause & exit /b 1)
where git >nul 2>nul || (echo Git not found. Install Git for Windows and retry.& pause & exit /b 1)
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
if errorlevel 1 (echo Configure failed. Keep this window open and share the full error.& pause & exit /b 1)
cmake --build build --config Release --target LernEffect
if errorlevel 1 (echo Build failed. Keep this window open and share the full error.& pause & exit /b 1)
echo Build completed. Search build for the LernEffect.vst3 bundle.
pause
