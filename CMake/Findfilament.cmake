find_path(
    filament_ROOT
    NAMES include/filament/Engine.h
)

if(NOT filament_FOUND AND filament_ROOT)
    set(filament_lib filament bluegl bluevk filabridge filaflat utils smol-v)

    add_library(filament::filament INTERFACE IMPORTED)

    foreach(lib IN LISTS filament_lib)
        add_library(${lib} STATIC IMPORTED)
        find_library(lib_path ${lib} PATHS "$ENV{filament_ROOT}/lib/x86_64")
        message("${lib} ${lib_path}")
        set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION "${lib_path}")
        target_link_libraries(filament::filament INTERFACE ${lib})
    endforeach()

    set_target_properties(filament PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "$ENV{filament_ROOT}/include")

    add_executable(filament::matc IMPORTED)
    if(WIN32)
        set_property(TARGET filament::matc PROPERTY IMPORTED_LOCATION "${filament_ROOT}/bin/matc.exe")
    elseif(UNIX)
        set_property(TARGET filament::matc PROPERTY IMPORTED_LOCATION "${filament_ROOT}/bin/matc")
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(filament
    FOUND_VAR filament_FOUND
    REQUIRED_VARS
    filament_ROOT
)
