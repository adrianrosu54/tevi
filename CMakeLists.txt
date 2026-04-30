cmake_minimum_required(VERSION 4.0)

project(text-sight
    VERSION 0.1.1
    LANGUAGES CXX
    DESCRIPTION "TUI visualizer application"
)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV CONFIG REQUIRED)
find_package(ftxui CONFIG REQUIRED)

# binary build setup
add_executable(textsight
    src/main.cpp
    src/app/app_controller.cpp
    src/services/camera.cpp
    src/services/command_registry.cpp
    src/ui/controller.cpp
    src/ui/image_canvas.cpp
    src/ui/view.cpp
)

target_include_directories(textsight
    PRIVATE src
)

target_link_libraries(textsight PRIVATE
    opencv_core
    opencv_imgproc
    opencv_highgui
    ftxui::screen
    ftxui::dom
    ftxui::component
)

# install and packaging setup
install(TARGETS textsight
    RUNTIME DESTINATION bin
)

if(UNIX AND NOT APPLE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

if(WIN32)
    install(CODE [[
        file(GET_RUNTIME_DEPENDENCIES
            EXECUTABLES
                "$<TARGET_FILE:textsight>"
            RESOLVED_DEPENDENCIES_VAR resolved_deps
            UNRESOLVED_DEPENDENCIES_VAR unresolved_deps
            DIRECTORIES
                $ENV{PATH}
            PRE_EXCLUDE_REGEXES
                "api-ms-win-.*"
                "ext-ms-win-.*"
            POST_EXCLUDE_REGEXES
                ".*system32.*"
                ".*windows.*"
        )

        foreach(dep IN LISTS resolved_deps)
            file(INSTALL
                DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
                TYPE SHARED_LIBRARY
                FOLLOW_SYMLINK_CHAIN
                FILES "${dep}"
            )
        endforeach()

        if(unresolved_deps)
            message(WARNING "Unresolved runtime dependencies: ${unresolved_deps}")
        endif()
    ]])
    install(FILES "${CMAKE_SOURCE_DIR}/installer/VC_redist.x64.exe"
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

# CPack
set(CPACK_PACKAGE_NAME "textsight")
set(CPACK_PACKAGE_VENDOR "Adrian Rosu")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Terminal based OpenCV webcam visualizer")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
