@echo off
REM ============================================================================
REM HesWidgetsDesign 项目构建脚本
REM ============================================================================

setlocal EnableDelayedExpansion

echo ==========================================================
echo HesWidgetsDesign 项目构建脚本
echo ==========================================================

REM 设置变量
set BUILD_DIR=build
set BUILD_TYPE=Release
set QT_SDK_DIR=D:/Qt/6.5.3/msvc2019_64

REM 解析命令行参数
:parse_args
if "%~1"=="" goto :done_args
if "%~1"=="--debug" (
    set BUILD_TYPE=Debug
    shift
    goto :parse_args
)
if "%~1"=="--clean" (
    set CLEAN_BUILD=true
    shift
    goto :parse_args
)
if "%~1"=="--qt-dir" (
    set QT_SDK_DIR=%~2
    shift
    shift
    goto :parse_args
)
if "%~1"=="--help" (
    goto :show_help
)
shift
goto :parse_args
:done_args

echo 构建类型: %BUILD_TYPE%
echo Qt SDK 目录: %QT_SDK_DIR%
echo 构建目录: %BUILD_DIR%
echo.

REM 清理构建目录（如果需要）
if defined CLEAN_BUILD (
    echo 清理构建目录...
    if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%
)

REM 创建构建目录
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

REM 进入构建目录
cd %BUILD_DIR%

REM 运行 CMake 配置
echo 正在配置项目...
cmake .. ^
    -G "Visual Studio 16 2019" ^
    -A x64 ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DQT_SDK_DIR="%QT_SDK_DIR%" ^
    -DCMAKE_INSTALL_PREFIX="../Install"

if errorlevel 1 (
    echo 配置失败！
    goto :error
)

REM 构建项目
echo 正在构建项目...
cmake --build . --config %BUILD_TYPE% --parallel

if errorlevel 1 (
    echo 构建失败！
    goto :error
)

REM 安装项目
echo 正在安装项目...
cmake --install . --config %BUILD_TYPE%

if errorlevel 1 (
    echo 安装失败！
    goto :error
)

echo.
echo ==========================================================
echo 构建成功完成！
echo 构建类型: %BUILD_TYPE%
echo 输出目录: %BUILD_DIR%/bin
echo 安装目录: ../Install
echo ==========================================================

cd ..
goto :end

:show_help
echo 用法: build.bat [选项]
echo.
echo 选项:
echo   --debug          构建调试版本 (默认: Release)
echo   --clean          清理构建目录
echo   --qt-dir PATH    指定 Qt SDK 目录
echo   --help           显示此帮助信息
echo.
echo 示例:
echo   build.bat                                    # 构建 Release 版本
echo   build.bat --debug                           # 构建 Debug 版本
echo   build.bat --clean --debug                   # 清理并构建 Debug 版本
echo   build.bat --qt-dir "C:/Qt/6.5.3/msvc2019_64"  # 指定 Qt 目录
goto :end

:error
echo.
echo ==========================================================
echo 构建失败！请检查错误信息。
echo ==========================================================
cd ..
exit /b 1

:end
endlocal
