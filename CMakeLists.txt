cmake_minimum_required(VERSION 3.16)

project(Qt-doc-viewer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets PdfWidgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(HEADERS
    include/main_window.h
    include/toolbar.h
    include/file_item.h
    include/file_manager.h
    include/viewer.h
)

set(SOURCES
    source/main_window.cpp
    source/toolbar.cpp
    source/file_item.cpp
    source/file_manager.cpp
    source/viewer.cpp
)

set(UI
    ui/main_window.ui
    ui/file_item.ui
)

qt_add_executable(Qt-doc-viewer
    main.cpp
    ${HEADERS}
    ${SOURCES}
    ${UI}
)

target_link_libraries(Qt-doc-viewer
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::PdfWidgets
)
