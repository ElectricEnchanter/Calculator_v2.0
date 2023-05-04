

cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_PREFIX_PATH "~/Qt/6.4.1/gcc_64")
# set(CMAKE_PREFIX_PATH "/Users/thedolaxom/Qt/6.4.1/macos/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_compile_definitions(QT_MACRO)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROJECT_ARCH_TARGET "amd64")    # x64
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PROJECT_ARCH_TARGET "i386")     # x86
else()
    message(FATAL_ERROR "Unkwnown architecture, CMake will exit.")
endif()

set(PROJECT_SOURCES
        calculator/main.cpp
        calculator/mainwindow.cpp
        calculator/mainwindow.h
        calculator/mainwindow.ui
        SmartCalc_v2.0.cc
        SmartCalc_v2.0.h
        calculator/graph.ui
        calculator/graph.h
        calculator/graph.cpp
        calculator/loancalc.ui
        calculator/loancalc.cpp
        calculator/loancalc.h
        calculator/depcalc.ui
        calculator/depcalc.cpp
        calculator/depcalc.h
        ../assets/icons/icons.qrc

)

# вернуть ../calculator/main.cpp

set(PROJECT_BUILD_OUTPUT ${CMAKE_SOURCE_DIR}/build/output/${PROJECT_ARCH_TARGET}/${CMAKE_BUILD_TYPE})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BUILD_OUTPUT}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/third_party)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/third_party)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BUILD_OUTPUT}/third_party)

#set(MACOSX_BUNDLE_ICON_FILE ../assets/icons/icon.icns)
#set(MACOSX_BUNDLE TRUE)
#set(app_icon_macos "../assets/icons/icon.icns")
#set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
 
#qt_add_executable(SmartCalc1 MACOSX_BUNDLE  ${app_icon_macos})

#set(MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
#set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc
        MANUAL_FINALIZATION
        MACOSX_BUNDLE
        ${app_icon_macos}
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(SmartCalc SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SmartCalc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartCalc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartCalc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE qcustomplot)

# Compile needed definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_USE_LIBRARY)

add_subdirectory(third_party)
