set(PROJECT_NAME commonui)

################################################################################
# Source groups
################################################################################
set(Headers
    "buildinfo.h"
    "cert_store.h"
    "chmod_data.h"
    "file_utils.h"
    "filter.h"
    "fz_paths.h"
    "ipcmutex.h"
    "local_recursive_operation.h"
    "login_manager.h"
    "options.h"
    "recursive_operation.h"
    "remote_recursive_operation.h"
    "site.h"
    "site_manager.h"
    "updater.h"
    "updater_cert.h"
    "visibility.h"
    "xml_cert_store.h"
    "xml_file.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
        auto_ascii_files.cpp
    "buildinfo.cpp"
    "cert_store.cpp"
    "chmod_data.cpp"
    "file_utils.cpp"
    "filter.cpp"
    "fz_paths.cpp"
    "ipcmutex.cpp"
    "local_recursive_operation.cpp"
    "login_manager.cpp"
    "options.cpp"
    "remote_recursive_operation.cpp"
    "site.cpp"
    "site_manager.cpp"
    "updater.cpp"
    "updater_cert.cpp"
    "xml_cert_store.cpp"
    xml_file.cpp
        misc.cpp
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################

#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
#use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "../Dependencies.cmake")

set(ROOT_NAMESPACE commonui)

add_library(commonui STATIC ${ALL_FILES})






if(MSVC)


endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(commonui
    engine
)

