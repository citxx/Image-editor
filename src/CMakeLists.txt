project(image_editor)

add_definitions(-Wall -pedantic -O2)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(SOURCES main.cpp EditorWindow.cpp ImageScene.cpp Processing.cpp)
set(MOC_HEADERS EditorWindow.hpp ImageScene.hpp Processing.hpp)
set(FORMS EditorWindow.ui)

QT4_WRAP_CPP(HEADERS ${MOC_HEADERS})
QT4_WRAP_UI(FORMS_HEADERS ${FORMS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

MESSAGE("--------------------")
MESSAGE("Headers: " ${HEADERS})
MESSAGE("Forms:   " ${FORMS_HEADERS})
MESSAGE("--------------------")

add_executable(editor ${SOURCES} ${HEADERS} ${FORMS_HEADERS})
target_link_libraries(editor ${QT_LIBRARIES})

