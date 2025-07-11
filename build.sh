#!/bin/bash
# ============================================================================
# HesWidgetsDesign 项目构建脚本 (Linux/macOS)
# ============================================================================

set -e  # 遇到错误时退出

echo "=========================================================="
echo "HesWidgetsDesign 项目构建脚本"
echo "=========================================================="

# 默认设置
BUILD_DIR="build"
BUILD_TYPE="Release"
QT_SDK_DIR=""
CLEAN_BUILD=false
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 检测操作系统并设置默认 Qt 路径
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    QT_SDK_DIR="/opt/Qt/6.5.3/gcc_64"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    QT_SDK_DIR="/opt/Qt/6.5.3/macos"
else
    echo "不支持的操作系统: $OSTYPE"
    exit 1
fi

# 显示帮助信息
show_help() {
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  --debug          构建调试版本 (默认: Release)"
    echo "  --clean          清理构建目录"
    echo "  --qt-dir PATH    指定 Qt SDK 目录"
    echo "  --jobs N         并行构建任务数 (默认: $JOBS)"
    echo "  --help           显示此帮助信息"
    echo ""
    echo "示例:"
    echo "  $0                                    # 构建 Release 版本"
    echo "  $0 --debug                           # 构建 Debug 版本"
    echo "  $0 --clean --debug                   # 清理并构建 Debug 版本"
    echo "  $0 --qt-dir \"/opt/Qt/6.5.3/gcc_64\"   # 指定 Qt 目录"
    exit 0
}

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        --qt-dir)
            QT_SDK_DIR="$2"
            shift 2
            ;;
        --jobs)
            JOBS="$2"
            shift 2
            ;;
        --help)
            show_help
            ;;
        *)
            echo "未知选项: $1"
            show_help
            ;;
    esac
done

echo "构建类型: $BUILD_TYPE"
echo "Qt SDK 目录: $QT_SDK_DIR"
echo "构建目录: $BUILD_DIR"
echo "并行任务数: $JOBS"
echo ""

# 检查 Qt 目录是否存在
if [[ ! -d "$QT_SDK_DIR" ]]; then
    echo "错误: Qt SDK 目录不存在: $QT_SDK_DIR"
    echo "请使用 --qt-dir 指定正确的 Qt SDK 路径"
    exit 1
fi

# 清理构建目录（如果需要）
if [[ "$CLEAN_BUILD" == "true" ]]; then
    echo "清理构建目录..."
    rm -rf "$BUILD_DIR"
fi

# 创建构建目录
mkdir -p "$BUILD_DIR"

# 进入构建目录
cd "$BUILD_DIR"

# 检测生成器
if command -v ninja >/dev/null 2>&1; then
    GENERATOR="Ninja"
else
    GENERATOR="Unix Makefiles"
fi

echo "使用生成器: $GENERATOR"

# 运行 CMake 配置
echo "正在配置项目..."
cmake .. \
    -G "$GENERATOR" \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DQT_SDK_DIR="$QT_SDK_DIR" \
    -DCMAKE_INSTALL_PREFIX="../Install"

# 构建项目
echo "正在构建项目..."
cmake --build . --config "$BUILD_TYPE" --parallel "$JOBS"

# 安装项目
echo "正在安装项目..."
cmake --install . --config "$BUILD_TYPE"

echo ""
echo "=========================================================="
echo "构建成功完成！"
echo "构建类型: $BUILD_TYPE"
echo "输出目录: $BUILD_DIR/bin"
echo "安装目录: ../Install"
echo "=========================================================="

cd ..
