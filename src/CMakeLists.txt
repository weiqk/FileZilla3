cmake_minimum_required(VERSION 3.10)


#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")



add_subdirectory(commonui)
add_subdirectory(dbus)
add_subdirectory(engine)
#include_directories(src/engine/ftp)
#include_directories(src/engine/http)
#include_directories(src/engine/sftp)
#include_directories(src/engine/storj)
add_subdirectory(fzshellext)


#include_directories(src/interface/settings)
#include_directories(src/interface/wxext)
add_subdirectory(pugixml)
add_subdirectory(putty)

add_subdirectory(storj)

file(GLOB SRC_WXFILEMAN_COMMONUI ${CMAKE_CURRENT_SOURCE_DIR}/commonui/*.cpp)
file(GLOB SRC_WXFILEMAN ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp)
#file(GLOB SRC_WXFILEMAN_INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/interface/*.cpp)

add_subdirectory(interface)
#list(APPEND ${SRC_WXFILEMAN} ${SRC_WXFILEMAN_INTERFACE})

# windows
add_executable(wxFileMan WIN32 ${SRC_WXFILEMAN_COMMONUI} ${SRC_WXFILEMAN} )

# 编译和链接选项
if(MSVC)
elseif(MINGW)
    # 编译选项

    # Link Options
    target_link_options(wxFileMan PRIVATE "-Wl,--enable-auto-import")
    target_link_options(wxFileMan PRIVATE "-Wl,--no-undefined")
    target_include_directories(wxFileMan PRIVATE "D:/tools/dev/codeblocks/installed/x64-mingw-static/include")
    target_link_directories(wxFileMan PRIVATE "${PROJECT_SOURCE_DIR}/3rdparty/exchndl/win64/lib")
endif()

# include directory
target_include_directories(wxFileMan PRIVATE "${PROJECT_SOURCE_DIR}")
target_include_directories(wxFileMan PRIVATE "${PROJECT_SOURCE_DIR}/include/scripting/include")

# define 宏定义
target_compile_definitions(wxFileMan PRIVATE BUILDING_PLUGIN)


# 链接目录

# 链接库文件
#target_link_libraries(wxFileMan PRIVATE liteblocks txml squirrel wx)
target_link_libraries(wxFileMan PRIVATE pugixml Comctl32)

set_target_properties(wxFileMan PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Dependencies
add_dependencies(wxFileMan pugixml)

set_target_properties(wxFileMan PROPERTIES OUTPUT_NAME "wxFileMan")
#set_target_properties(wxFileMan PROPERTIES PREFIX "")
install(TARGETS wxFileMan DESTINATION /)


