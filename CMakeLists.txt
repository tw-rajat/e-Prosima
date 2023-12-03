cmake_minimum_required(VERSION 3.12.4)
if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()

# project(ClsImplem VERSION 1.0.0 LANGUAGES CXX)
# project(MainImplem VERSION 1.0.0 LANGUAGES CXX)
# project(MainReader VERSION 1.0.0 LANGUAGES CXX)
project(MainWriter VERSION 1.0.0 LANGUAGES CXX)
# project(MainListener VERSION 1.0.0 LANGUAGES CXX)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

set(fastdds_dir /usr/local/include/)

include_directories( ${fastdds_dir}
                     ${fastdds_dir}/fastcdr
                     ${fastdds_dir}/fastdds
                     ${fastdds_dir}/fastrtps
                     ${CMAKE_CURRENT_SOURCE_DIR}/generated
                     ${CMAKE_CURRENT_SOURCE_DIR}/
                     )

file(GLOB HW_SOURCES_CXX "**/**.cxx")

add_executable( ${PROJECT_NAME} 
                # ${CMAKE_CURRENT_SOURCE_DIR}/ClassImplementation.cxx 
                # ${CMAKE_CURRENT_SOURCE_DIR}/MainImplementation.cxx 
                # ${CMAKE_CURRENT_SOURCE_DIR}/MainReader.cxx
                ${CMAKE_CURRENT_SOURCE_DIR}/MainWriter.cxx
                # ${CMAKE_CURRENT_SOURCE_DIR}/MainListener.cxx
                ${HW_SOURCES_CXX})
target_link_libraries(${PROJECT_NAME} fastrtps fastcdr)
