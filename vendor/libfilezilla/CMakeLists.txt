cmake_minimum_required(VERSION 3.10)


configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libfilezilla/version.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libfilezilla/version.hpp"
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/version.rc.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/version.rc"
)

file(GLOB SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)
file(GLOB SRC_LIBFILEZILLA_WINDOWS ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/*.cpp)

list(APPEND SRC_LIBFILEZILLA ${SRC_LIBFILEZILLA_WINDOWS})
list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/aio.cpp)
list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/reader.cpp)
list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/writer.cpp)

#list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libfilezilla.rc)

add_library(fz SHARED ${SRC_LIBFILEZILLA})
target_link_libraries(fz PRIVATE gnutls Iphlpapi wsock32 ws2_32 nettle gmp hogweed sqlite3)
#add_library(fz STATIC ${SRC_LIBFILEZILLA})

