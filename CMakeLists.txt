cmake_minimum_required(VERSION 3.10)
project(wxFileMan)

# set(CMAKE_CXX_STANDARD 14)

include(CPack)

if(WIN32)
    message(WARNING ${CMAKE_BINARY_DIR}=${CMAKE_GENERATOR_PLATFORM})
    message(WARNING ${CMAKE_HOST_SYSTEM_NAME}=${CMAKE_HOST_SYSTEM_VERSION})
    #message(FATAL_ERROR ${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()

#set vRelease
string(TIMESTAMP vRelease "%y.%m.%d")
string(REPLACE ".0" "." vRelease ${vRelease})
add_compile_definitions(RELEASE="${vRelease}")

if(NOT CMAKE_CONFIGURATION_TYPES)
    get_property(HAVE_MULTI_CONFIG_GENERATOR GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(HAVE_MULTI_CONFIG_GENERATOR)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo")
    endif()
endif()

# https://blog.kitware.com/cmake-and-the-default-build-type/
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type "Debug")
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include_directories("D:/code/vcpkg/installed/x64-mingw-static/include")
link_directories("D:/code/vcpkg/installed/x64-mingw-static/lib")

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/libfilezilla/lib)

add_subdirectory(vendor)
add_subdirectory(src)




add_executable(wxMain wxMain.cpp)
