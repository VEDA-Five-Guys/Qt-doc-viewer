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
    include/pdf_viewer_widget.h
    include/file_item_widget.h

)

set(SOURCES
    source/main_window.cpp
    source/pdf_viewer_widget.cpp
    source/file_item_widget.cpp
)

set(UI
    ui/main_window.ui
    ui/file_item_widget.ui
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
