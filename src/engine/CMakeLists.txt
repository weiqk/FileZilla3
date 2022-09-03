set(PROJECT_NAME engine)

################################################################################
# Source groups
################################################################################
set(Headers
    "../include/activity_logger.h"
    #${CMAKE_CURRENT_SOURCE_DIR}/../include/aio.h
    "../include/commands.h"
    "../include/directorylisting.h"
    "../include/engine_context.h"
    "../include/engine_options.h"
    "../include/externalipresolver.h"
    "../include/FileZillaEngine.h"
    "../include/httpheaders.h"
    "../include/libfilezilla_engine.h"
    "../include/local_path.h"
    "../include/logging.h"
    "../include/misc.h"
    "../include/notification.h"
    "../include/optionsbase.h"
    #${CMAKE_CURRENT_SOURCE_DIR}/../include/reader.h
    "../include/server.h"
    "../include/serverpath.h"
    "../include/sizeformatting_base.h"
        ../include/version.h
        #"../include/writer.h"
        "../include/xmlutils.h"
        "activity_logger_layer.h"
        "controlsocket.h"
        "directorycache.h"
        "directorylistingparser.h"
        "engineprivate.h"
        "filezilla.h"
        "ftp/chmod.h"
        "ftp/cwd.h"
        "ftp/delete.h"
        "ftp/filetransfer.h"
        "ftp/ftpcontrolsocket.h"
        "ftp/list.h"
        "ftp/logon.h"
        "ftp/mkd.h"
        "ftp/rawcommand.h"
        "ftp/rawtransfer.h"
        "ftp/rename.h"
        "ftp/rmd.h"
        "ftp/transfersocket.h"
        "http/connect.h"
        "http/digest.h"
        "http/filetransfer.h"
        "http/httpcontrolsocket.h"
        "http/internalconnect.h"
        "http/request.h"
        "logging_private.h"
        "lookup.h"
        "oplock_manager.h"
        "pathcache.h"
        "proxy.h"
        "rtt.h"
        "servercapabilities.h"

        #"string_reader.h"
    )


    add_library(engine STATIC
            "${CMAKE_CURRENT_SOURCE_DIR}/activity_logger.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/activity_logger_layer.cpp"
            #${CMAKE_CURRENT_SOURCE_DIR}/aio.cpp
            "${CMAKE_CURRENT_SOURCE_DIR}/commands.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/controlsocket.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/directorycache.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/directorylisting.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/directorylistingparser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/engine_context.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/engine_options.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/engineprivate.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/externalipresolver.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/FileZillaEngine.cpp"




            "${CMAKE_CURRENT_SOURCE_DIR}/http/digest.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/http/filetransfer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/http/httpcontrolsocket.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/http/internalconnect.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/http/request.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/local_path.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/lookup.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/misc.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/notification.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/oplock_manager.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/optionsbase.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/pathcache.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/proxy.cpp"
            #${CMAKE_CURRENT_SOURCE_DIR}/reader.cpp
            "${CMAKE_CURRENT_SOURCE_DIR}/rtt.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/server.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/servercapabilities.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/serverpath.cpp"




            "${CMAKE_CURRENT_SOURCE_DIR}/sizeformatting_base.cpp"


            #${CMAKE_CURRENT_SOURCE_DIR}/string_reader.cpp
            "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp"
            #${CMAKE_CURRENT_SOURCE_DIR}/writer.cpp
            "${CMAKE_CURRENT_SOURCE_DIR}/xmlutils.cpp"



            )

    target_include_directories(engine PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    )

    ################################################################################
    # Compile definitions
    ################################################################################
    target_compile_definitions(engine PRIVATE
        "UNICODE"
        "_UNICODE"
    )

add_dependencies(engine engine_storj engine_sftp engine_ftp)

if(MSVC)

endif()

add_subdirectory(storj)
add_subdirectory(sftp)
add_subdirectory(ftp)