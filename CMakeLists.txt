cmake_minimum_required(VERSION 4.0)

project(tevi
    VERSION 0.2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS videoio imgproc)

add_executable(tevi
    src/main.cpp
    src/args.cpp
    src/print.cpp
    src/render.cpp
    src/util/data.cpp
    src/util/camera.cpp
    src/render/pixel.cpp
)

target_include_directories(tevi
    PRIVATE src
)

target_link_libraries(tevi PRIVATE
    opencv_core
    opencv_imgproc
    opencv_highgui
)

# version string
target_compile_definitions(tevi PRIVATE
    TEVI_VERSION="${PROJECT_VERSION}"
)
