cmake_minimum_required(VERSION 3.10)

add_library( engine_ftp STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/chmod.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cwd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/delete.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/filetransfer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ftpcontrolsocket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/logon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mkd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rawcommand.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rawtransfer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rename.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rmd.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/transfersocket.cpp
)

