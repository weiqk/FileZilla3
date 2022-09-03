cmake_minimum_required(VERSION 3.10)

add_library(pugixml STATIC pugixml.cpp)

target_include_directories(pugixml PRIVATE
    ${PROJECT_SOURCE_DIR}/src/include
    ${PROJECT_SOURCE_DIR}/vendor/libfilezilla/lib
)

if(MSVC)

endif()

