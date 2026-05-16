cmake_minimum_required(VERSION 3.29)

project(tevi
    VERSION 1.1.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED COMPONENTS videoio imgproc)

add_executable(tevi
    src/args.cpp
    src/commands.cpp
    src/main.cpp
    src/render.cpp
    src/util/data.cpp
    src/util/fetcher.cpp
    src/util/logging.cpp
    src/util/pixel.cpp
)

target_include_directories(tevi
    PRIVATE src
)

target_link_libraries(tevi PRIVATE
    opencv_core
    opencv_imgproc
    opencv_videoio
)

# version string
target_compile_definitions(tevi PRIVATE
    TEVI_VERSION="${PROJECT_VERSION}"
)
