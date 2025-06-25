cmake_minimum_required(VERSION 3.16)
project(Mario)

set(CMAKE_CXX_STANDARD 17)

# Set download and extraction directories
set(DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/zip_files")
set(EXTRACT_DIR "${CMAKE_SOURCE_DIR}/lib")

# URLs for dependencies
set(RAYLIB_URL "https://github.com/raysan5/raylib/archive/refs/heads/master.zip")
set(BOX2D_URL "https://github.com/erincatto/box2d/archive/refs/heads/main.zip")

# Download paths
set(RAYLIB_ZIP "${DOWNLOAD_DIR}/raylib.zip")
set(BOX2D_ZIP "${DOWNLOAD_DIR}/box2d.zip")

# Extraction paths
set(RAYLIB_SRC "${EXTRACT_DIR}/raylib")
set(BOX2D_SRC "${EXTRACT_DIR}/box2d")

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

# Download box2d if not already present
if(NOT EXISTS ${BOX2D_ZIP})
    message(STATUS "Downloading box2d...")
    file(DOWNLOAD ${BOX2D_URL} ${BOX2D_ZIP} SHOW_PROGRESS STATUS download_status)
    list(GET download_status 0 status_code)
    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Failed to download box2d")
    endif()
endif()

# Extract box2d if not already extracted
if(NOT EXISTS ${BOX2D_SRC})
    message(STATUS "Extracting box2d...")
    file(ARCHIVE_EXTRACT INPUT ${BOX2D_ZIP} DESTINATION ${EXTRACT_DIR})
    file(GLOB box2d_folder "${EXTRACT_DIR}/box2d-*")
    file(RENAME ${box2d_folder} ${BOX2D_SRC})
endif()

# Add raylib and box2d as subdirectories
add_subdirectory(${RAYLIB_SRC} ${RAYLIB_SRC}/build)
add_subdirectory(${BOX2D_SRC} ${BOX2D_SRC}/build)

# Gather sources
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/include/*.hpp")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory.")
endif()

add_executable(Mario ${SOURCES} ${HEADERS})

target_include_directories(Mario PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${RAYLIB_SRC}/src
    ${BOX2D_SRC}/include
)

target_link_libraries(Mario PRIVATE raylib box2d)

# Optionally copy assets to build directory
add_custom_command(TARGET Mario POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Mario>/assets
    COMMENT "Copying assets to output directory"
)
