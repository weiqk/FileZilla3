cmake_minimum_required(VERSION 3.10)


add_library( engine_storj STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/connect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/delete.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_transfer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/input_thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mkd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rmd.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/storjcontrolsocket.cpp
)


