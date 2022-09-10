cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
#project(FileZilla CXX)



if(MSVC)
endif()

function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

include(CMake/Utils.cmake)

include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

add_subdirectory(commonui)
add_subdirectory(engine)
add_subdirectory(interface)
add_subdirectory(pugixml)

