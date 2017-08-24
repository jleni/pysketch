# Distributed under the MIT software license, see the accompanying
# file LICENSE or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 2.6)
project(cppsketch)

option(INSTALL_PYTHON "Install python wrapper" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
set(SOURCE_FILES_LIB src/Sketch.h src/Sketch.cpp)
set(SOURCE_FILES_WRAPPER "pysketch/sketch_wrapper.h" "pysketch/sketch_wrapper.cpp")

add_executable(pysketchtest ${SOURCE_FILES} ${SOURCE_FILES_LIB})
add_library(pysketch SHARED ${SOURCE_FILES_LIB} ${SOURCE_FILES_WRAPPER} )

set_target_properties(pysketch PROPERTIES OUTPUT_NAME pysketch)
set_target_properties(pysketch PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pysketch)

target_link_libraries(pysketch ${LINK_LIBS})

if(INSTALL_PYTHON)
    add_custom_command(TARGET pysketch POST_BUILD
                       COMMAND pip install -v --upgrade ${CMAKE_CURRENT_SOURCE_DIR} )
endif()