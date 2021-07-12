cmake_minimum_required(VERSION 3.14)

project(qml_filament LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(OpenGL REQUIRED)
find_package(filament REQUIRED)
find_package(Threads REQUIRED)

add_executable(qml_filament
    main.cpp
    qml.qrc
    qfilament.h
    qfilament.cpp
    qfilamentitem.h
    qfilamentitem.cpp
    qsgfilamentnode.h
    qsgfilamentnode.cpp
    )

#set(LIBS ${LIBS} -L${FILAMENT_ROOT}/lib/x86_64/md/ -lfilament -lbackend -lbluegl -lbluevk -lfilabridge -lfilaflat -lutils -lgeometry -lsmol-v -libl -lfilamat -ldl -lpthread)
#set(LIBS ${LIBS} -L${STDLIB_PATH})

target_compile_definitions(qml_filament
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qml_filament
    Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick filament::filament Threads::Threads)

set_target_properties(qml_filament PROPERTIES
    QT_QML_MODULE_VERSION 1.0
    QT_QML_MODULE_URI QFilament
    )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(qml_filament)
    qt_finalize_executable(qml_filament)
endif()

qt6_qml_type_registration(qml_filament)
