cmake_minimum_required(VERSION 3.16)
project(Mario)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set download and extraction directories
set(DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/zip_files")
set(EXTRACT_DIR "${CMAKE_SOURCE_DIR}/lib")

# URLs for dependencies
set(RAYLIB_URL "https://github.com/raysan5/raylib/archive/refs/heads/master.zip")

# Download paths
set(RAYLIB_ZIP "${DOWNLOAD_DIR}/raylib.zip")

# Extraction paths
set(RAYLIB_SRC "${EXTRACT_DIR}/raylib")

# Ensure directories exist
file(MAKE_DIRECTORY ${DOWNLOAD_DIR})
file(MAKE_DIRECTORY ${EXTRACT_DIR})

# Download raylib if not already present
if(NOT EXISTS ${RAYLIB_ZIP})
    message(STATUS "Downloading raylib...")
    file(DOWNLOAD ${RAYLIB_URL} ${RAYLIB_ZIP} SHOW_PROGRESS STATUS download_status)
    list(GET download_status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download raylib")
    endif()
endif()

# Extract raylib if not already extracted
if(NOT EXISTS ${RAYLIB_SRC})
    message(STATUS "Extracting raylib...")
    file(ARCHIVE_EXTRACT INPUT ${RAYLIB_ZIP} DESTINATION ${EXTRACT_DIR})
    # Rename extracted folder if necessary
    file(GLOB raylib_folder "${EXTRACT_DIR}/raylib-*")
    file(RENAME ${raylib_folder} ${RAYLIB_SRC})
endif()

# Add raylib as subdirectory
add_subdirectory(${RAYLIB_SRC} ${RAYLIB_SRC}/build)

# Gather sources
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/include/*.hpp")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory.")
endif()

add_executable(Mario ${SOURCES})

# --- Collect all include/ subdirectories recursively ---
file(GLOB_RECURSE INCLUDE_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/*)
set(ALL_INCLUDE_DIRS "")
foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/include/${dir})
        list(APPEND ALL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include/${dir})
    endif()
endforeach()

# --- Collect all src/ subdirectories recursively ---
file(GLOB_RECURSE SRC_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/*)
set(ALL_SRC_DIRS "")
foreach(dir ${SRC_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/src/${dir})
        list(APPEND ALL_SRC_DIRS ${CMAKE_SOURCE_DIR}/src/${dir})
    endif()
endforeach()

# --- Add root folders and all subfolders to the target include paths ---
target_include_directories(Mario PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${ALL_SRC_DIRS}
    ${RAYLIB_SRC}/src
)

target_link_libraries(Mario PRIVATE raylib)

# Optionally copy assets to build directory
add_custom_command(TARGET Mario POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Mario>/assets
    COMMENT "Copying assets to output directory"
)


if (MSVC)
    add_compile_options(/permissive-)
endif()
