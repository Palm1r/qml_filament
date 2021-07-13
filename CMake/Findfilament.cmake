find_path(
    filament_ROOT
    NAMES include/filament/Engine.h
    )

if(NOT filament_FOUND AND filament_ROOT)
    add_library(filament::filament INTERFACE IMPORTED)

    find_library(backend_LIBRARY NAMES backend libbackend HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(bluegl_LIBRARY NAMES bluegl libbluegl HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(filabridge_LIBRARY NAMES filabridge libfilabridge HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(filaflat_LIBRARY NAMES filaflat libfilaflat HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(filament_LIBRARY NAMES filament libfilament HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(geometry_LIBRARY NAMES geometry libgeometry HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(ibl_LIBRARY NAMES ibl libibl HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(matdbg_LIBRARY NAMES matdbg libmatdbg HINTS ${filament_ROOT}/lib/x86_64/)
    find_library(utils_LIBRARY NAMES utils libutils HINTS ${filament_ROOT}/lib/x86_64/)

    set_property(TARGET filament::filament PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        "${filament_ROOT}/include"
        )

    set( FILAMENT_LIBRARIES ${backend_LIBRARY}
                            ${bluegl_LIBRARY}
                            ${filabridge_LIBRARY}
                            ${filaflat_LIBRARY}
                            ${filament_LIBRARY}
                            ${geometry_LIBRARY}
                            ${ibl_LIBRARY}
                            ${matdbg_LIBRARY}
                            ${utils_LIBRARY}
                            )
    target_link_libraries(filament::filament INTERFACE ${FILAMENT_LIBRARIES})

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
