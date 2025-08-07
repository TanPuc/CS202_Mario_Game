cmake_minimum_required(VERSION 3.16)
project(Mario)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependency: Raylib ---
set(DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/zip_files")
set(EXTRACT_DIR "${CMAKE_SOURCE_DIR}/lib")
set(RAYLIB_URL "https://github.com/raysan5/raylib/archive/refs/heads/master.zip")
set(RAYLIB_ZIP "${DOWNLOAD_DIR}/raylib.zip")
set(RAYLIB_SRC "${EXTRACT_DIR}/raylib")

file(MAKE_DIRECTORY ${DOWNLOAD_DIR})
file(MAKE_DIRECTORY ${EXTRACT_DIR})

if(NOT EXISTS ${RAYLIB_ZIP})
    message(STATUS "Downloading raylib...")
    file(DOWNLOAD ${RAYLIB_URL} ${RAYLIB_ZIP} SHOW_PROGRESS STATUS download_status)
    list(GET download_status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download raylib")
    endif()
endif()

if(NOT EXISTS ${RAYLIB_SRC})
    message(STATUS "Extracting raylib...")
    file(ARCHIVE_EXTRACT INPUT ${RAYLIB_ZIP} DESTINATION ${EXTRACT_DIR})
    file(GLOB raylib_folder "${EXTRACT_DIR}/raylib-*")
    file(RENAME ${raylib_folder} ${RAYLIB_SRC})
endif()

add_subdirectory(${RAYLIB_SRC} ${RAYLIB_SRC}/build)

# --- Gather all source and header files recursively ---
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/include/*.hpp")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory.")
endif()

add_executable(Mario ${SOURCES} ${HEADERS})

# --- Include all subdirectories automatically ---
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
file(GLOB_RECURSE ALL_INCLUDE_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/*)
file(GLOB_RECURSE ALL_SRC_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/*)

foreach(dir ${ALL_INCLUDE_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/include/${dir})
        include_directories(${CMAKE_SOURCE_DIR}/include/${dir})
    endif()
endforeach()

foreach(dir ${ALL_SRC_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/${dir})
        include_directories(${CMAKE_SOURCE_DIR}/src/${dir})
    endif()
endforeach()

# --- Link Raylib ---
target_link_libraries(Mario PRIVATE raylib)

# --- Copy assets automatically after build ---
add_custom_command(TARGET Mario POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Mario>/assets
    COMMENT "Copying assets to output directory"
)
