cmake_minimum_required(VERSION 3.10)

file(GLOB SRC_FILES_C "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB SRC_FILES_WINDOWS_C "${CMAKE_CURRENT_SOURCE_DIR}/windows/*.c")

add_executable(fxputty WIN32 ${SRC_FILES_C} ${SRC_FILES_WINDOWS_C})

# 编译和链接选项
if(MSVC)
elseif(MINGW)
    # 编译选项

    # Link Options
    target_link_options(fxputty PRIVATE "-Wl,--enable-auto-import")
    target_link_options(fxputty PRIVATE "-Wl,--no-undefined")
    target_include_directories(fxputty PRIVATE "${PROJECT_SOURCE_DIR}/3rdparty/exchndl/win64/include")
    target_link_directories(fxputty PRIVATE "${PROJECT_SOURCE_DIR}/3rdparty/exchndl/win64/lib")
endif()

# include directory
target_include_directories(fxputty PRIVATE "${PROJECT_SOURCE_DIR}")
target_include_directories(fxputty PRIVATE "${PROJECT_SOURCE_DIR}/include/scripting/include")

# define 宏定义
target_compile_definitions(fxputty PRIVATE BUILDING_PLUGIN)




# 链接目录

# 链接库文件
target_link_libraries(fxputty PRIVATE liteblocks txml squirrel wx)
target_link_libraries(fxputty PRIVATE exchndl Comctl32)

#set_target_properties(fxputty PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DIR_TARGET})

# Dependencies
#add_dependencies(fxputty liteblocks txml squirrel)

set_target_properties(fxputty PROPERTIES OUTPUT_NAME "fxputty")
set_target_properties(fxputty PROPERTIES PREFIX "")
install(TARGETS fxputty DESTINATION /)