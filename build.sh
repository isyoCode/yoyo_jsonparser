#!/bin/zsh

# 设置脚本退出时的行为：脚本遇到错误立即退出
set -e

# 默认设置
BUILD_DIR="build"                 # 构建文件的目录
BUILD_TYPE="Debug"                # 默认构建类型为 Debug
ENABLE_OPTIMIZATION="OFF"         # 默认不启用优化

# 打印帮助信息
function usage() {
    echo "Usage: $0 [options]"
    echo ""
    echo "Options:"
    echo "  -d <dir>         Specify the build directory (default: ${BUILD_DIR})"
    echo "  -t <type>        Specify the build type: Debug|Release (default: ${BUILD_TYPE})"
    echo "  -o               Enable optimization (-O2)"
    echo "  -h               Show this help message"
    echo ""
    exit 1
}

# 解析命令行参数
while getopts ":d:t:oh" opt; do
    case ${opt} in
        d) BUILD_DIR=${OPTARG} ;;
        t) BUILD_TYPE=${OPTARG} ;;
        o) ENABLE_OPTIMIZATION="ON" ;;
        h) usage ;;
        *) usage ;;
    esac
done

# 打印配置信息
echo "============================================================="
echo "Build Configuration:"
echo "  Build Directory    : ${BUILD_DIR}"
echo "  Build Type         : ${BUILD_TYPE}"
echo "  Enable Optimization: ${ENABLE_OPTIMIZATION}"
echo "============================================================="

# 创建构建目录
if [ ! -d "${BUILD_DIR}" ]; then
    echo "Creating build directory: ${BUILD_DIR}"
    mkdir -p "${BUILD_DIR}"
fi

# 进入构建目录
cd "${BUILD_DIR}"

# 运行 CMake 配置
echo "Running CMake configuration..."
cmake .. -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -DENABLE_OPTIMIZATION="${ENABLE_OPTIMIZATION}"

# 执行构建
echo "Building the project..."
cmake --build .

# 提示完成
echo "============================================================="
echo "Build completed successfully!"
echo "Generated binaries are located in the 'bin/' directory."
echo "============================================================="