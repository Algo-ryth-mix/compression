# CMakeList.txt: CMake-Projekt für "test-jig". Schließen Sie die Quelle ein  und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)




add_library(zip "zip/miniz.h" "zip/zip.c" "zip/zip.h")


if(ZIP_T)
    add_definitions(-DTEST_ZIP_INSTEAD)
endif(ZIP_T)
# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (testjig
            "main.cpp" 

            "utility/common.hpp"

            "utility/benchmark.hpp"
            "utility/buffer_match.hpp"
            "utility/file.hpp"
            "utility/filesize.hpp"
            "utility/utility.hpp"

            "utility/compressor.hpp"
           
            "utility/common_xz.hpp"
            "utility/compress_xz.hpp"
            "utility/decompress_xz.hpp"
            "utility/xz_compressor.hpp"

            "utility/common_zip.hpp"
            "utility/compress_zip.hpp"
            "utility/decompress_zip.hpp"
            "utility/zip_compressor.hpp"

            
            )
set_target_properties(testjig PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            )
if(MSVC)
    target_link_directories(testjig PUBLIC ".")
    target_link_libraries(testjig "liblzma.lib")
    target_link_libraries(testjig zip)
endif(MSVC)

target_include_directories(testjig PUBLIC "../include")
