project(image_editor)

add_definitions(-Wall -pedantic -O2)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(SOURCES
    main.cpp
    EditorWindow.cpp
    ImageScene.cpp
    Processing.cpp
    FilterDialog.cpp
    Filter.cpp
    RotateDialog.cpp
    ScaleDialog.cpp
    WavesDialog.cpp
    ImageShowArea.cpp
    UnsharpDialog.cpp
)
set(MOC_HEADERS
    EditorWindow.hpp
    ImageScene.hpp
    FilterDialog.hpp
    RotateDialog.hpp
    ScaleDialog.hpp
    WavesDialog.hpp
    ImageShowArea.hpp
    UnsharpDialog.hpp
)
set(FORMS
    EditorWindow.ui
    FilterDialog.ui
    RotateDialog.ui
    ScaleDialog.ui
    WavesDialog.ui
    UnsharpDialog.ui
)

QT4_WRAP_CPP(HEADERS ${MOC_HEADERS})
QT4_WRAP_UI(FORMS_HEADERS ${FORMS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

MESSAGE("--------------------")
MESSAGE("Headers: " ${HEADERS})
MESSAGE("Forms:   " ${FORMS_HEADERS})
MESSAGE("--------------------")

add_executable(editor ${SOURCES} ${HEADERS} ${FORMS_HEADERS})
target_link_libraries(editor ${QT_LIBRARIES})

