cmake_minimum_required(VERSION 3.17)

project(qml_filament VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-lc++abi")

#set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

find_package(Qt6 6.2 COMPONENTS Core Quick #[[LinguistTools]] REQUIRED)
find_package(Threads)
find_package(filament)

add_executable(appqml_filament
    main.cpp
#    qml.qrc
#    qfilament.h
#    qfilament.cpp
#    qsgfilamentnode.h
#    qsgfilamentnode.cpp
)

qt_add_qml_module(appqml_filament
    URI qmlfilament
    VERSION 1.0
    QML_FILES main.qml
#    SOURCES
#    qfilamentitem.h
#    qfilamentitem.cpp
)

target_compile_definitions(appqml_filament
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appqml_filament
    PRIVATE
    Qt6::Core
    Qt6::Quick
    filament::filament
    pthread
    c++
    dl
)

#set(filament_lib filament bluegl bluevk filabridge filaflat utils smol-v)

#foreach(lib IN LISTS filament_lib)
#        add_library(${lib} STATIC IMPORTED)
#        find_library(lib_path ${lib} PATHS "$ENV{filament_ROOT}/lib/x86_64")
#        message("${lib} ${lib_path}")
#        set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION "${lib_path}")
#        target_link_libraries(appqml_filament PRIVATE ${lib})
#endforeach()
#set_target_properties(filament PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "$ENV{filament_ROOT}/include")
