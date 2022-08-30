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
#add_compile_definitions(RELEASE="${vRelease}")

set (PACKAGE_VERSION_MAJOR 1)
set (PACKAGE_VERSION_MINOR 0)
set (PACKAGE_VERSION_MICRO 0)
set (PACKAGE_VERSION_NANO 1)
string(TIMESTAMP vDateRelease "%Y%m%d%H%M")
set (PACKAGE_VERSION_SUFFIX "build ${vDateRelease}")
set (PACKAGE_VERSION "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}.${PACKAGE_VERSION_MICRO}.${PACKAGE_VERSION_NANO} ${PACKAGE_VERSION_SUFFIX}")

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

if(MSVC)
    add_compile_options(/w)
elseif(MINGW)
    #add_compile_options("-pipe")
    #add_compile_options("-mthreads")

    #add_compile_options("-fexceptions")
    #add_compile_options("-fno-strict-aliasing")
    #add_compile_options("-Wno-write-strings")
    add_compile_options("-w")

    #add_compile_options("-ffunction-sections")
    #add_compile_options("-fdata-sections")
    #add_compile_options("-Wl,--as-needed")
    #add_compile_options("-Wl,--gc-sections")

    #add_link_options("-static-libstdc++")
    #add_link_options("-static-libgcc")
    #add_link_options("-static")
    add_link_options("-m64")

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options("-O3")
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        add_compile_options("-O3")
        add_compile_options("-g")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_compile_options("-Os")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-pie -g3 -Og)
    endif()
endif()

include_directories("D:/tools/dev/codeblocks/installed/x64-mingw-dynamic/include")
link_directories("D:/tools/dev/codeblocks/installed/x64-mingw-dynamic/lib")

include_directories("D:/tools/dev/codeblocks/installed/x64-mingw-static/include")
link_directories("D:/tools/dev/codeblocks/installed/x64-mingw-static/lib")

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/libfilezilla/lib)

add_subdirectory(vendor)
add_subdirectory(src)




add_executable(wxMain wxMain.cpp)
