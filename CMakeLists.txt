cmake_minimum_required(VERSION 3.16)
project(TDD_detection)
MESSAGE (STATUS "PROJECT_NAME: " ${PROJECT_NAME})
set(CMAKE_C_COMPILER gcc)
set(SOURCE_EXE main.cpp)


#set Path

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Configure a header file to pass some of the CMake settings
# to the source code

configure_file (
    "${PROJECT_SOURCE_DIR}/devmem.hpp"
    "${PROJECT_BINARY_DIR}/dmac.hpp"
    "${PROJECT_BINARY_DIR}/tch.hpp"
)

set(SOURCE_LIB create_mark.cpp
FFT_TRANS.cpp
freq_shift.cpp
funk.cpp
logger.cpp
plis_configure.cpp
NRS_GEN.cpp
PSS_corr.cpp
RS_proc.cpp
SSS_PROC.cpp
TDD_detection.cpp
               

                
                
                
                
                        )

add_library(lib STATIC ${SOURCE_LIB})
add_library(tch SHARED IMPORTED)
add_library(dmac SHARED IMPORTED)
add_library(devmem SHARED IMPORTED)

set_property(TARGET tch PROPERTY IMPORTED_LOCATION "/home/qwerty/Изображения/TDD_detection4/libtch.so")
set_property(TARGET dmac PROPERTY IMPORTED_LOCATION "/home/qwerty/Изображения/TDD_detection4/libdmac.so")
set_property(TARGET devmem PROPERTY IMPORTED_LOCATION "/home/qwerty/Изображения/TDD_detection4/libdevmem.so")




add_executable(TDD_DETECTION ${SOURCE_EXE})

target_link_libraries(TDD_DETECTION lib fftw3 tch)