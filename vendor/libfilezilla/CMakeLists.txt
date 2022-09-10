cmake_minimum_required(VERSION 3.10)


configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libfilezilla/version.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libfilezilla/version.hpp"
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/version.rc.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/version.rc"
)

set(SRC_LIBFILEZILLA


        ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/aio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/reader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/aio/writer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/encode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/encryption.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/event_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/event_loop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/hash.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/hostname_lookup.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/impersonation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/invoker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/iputils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/json.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/jws.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/local_filesys.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/logger.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/mutex.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/nonowning_buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/process.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/rate_limiter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/rate_limited_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/recursive_remove.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/signature.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/socket.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/socket_errors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/string.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/thread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/thread_pool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/tls_info.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/tls_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/tls_layer_impl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/tls_system_trust_store.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/time.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/translate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/uri.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/util.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/version.cpp

)

if(WIN32)
    list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/dll.cpp)
    list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/poller.cpp)
    list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/registry.cpp)
    list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/security_descriptor_builder.cpp)
endif()


#list(APPEND SRC_LIBFILEZILLA ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/libfilezilla.rc)

add_library(fz SHARED ${SRC_LIBFILEZILLA})

target_link_libraries(fz PRIVATE gnutls Iphlpapi wsock32 ws2_32 nettle gmp hogweed sqlite3)
#add_library(fz STATIC ${SRC_LIBFILEZILLA})

