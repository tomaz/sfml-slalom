cmake_minimum_required(VERSION 3.28)
project(slalom LANGUAGES CXX)

# Project variables
set(BINARY_NAME slalom)
set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(ASSETS_DIR assets)
set(ASSETS_SRC_DIR ${CMAKE_SOURCE_DIR}/${ASSETS_DIR})
set(ASSETS_DST_DIR ${BINARY_DIR}/${ASSETS_DIR})
set(SRC_DIR src)

# Tools
set(ASEPRITE $ENV{HOME}/Applications/Aseprite.app/Contents/MacOS/aseprite)

# Prepare various module flags
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)	# FetchContent should use caches when offline

# Prepare all source and header files
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${SRC_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE ASSETS CONFIGURE_DEPENDS "${ASSETS_DIR}/*.aseprite")

# Recursively find all header files and prepare their unique paths
set(INCLUDE_PATHS "")
foreach (HEADER_FILE ${HEADERS})
	get_filename_component(HEADER_DIR ${HEADER_FILE} PATH)
	list(APPEND INCLUDE_PATHS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_PATHS)

# Converting aseprite images
file(MAKE_DIRECTORY ${ASSETS_DST_DIR})

foreach(image ${ASSETS})
	get_filename_component(file ${image} NAME_WLE)	# just the name, without path and extension
	message(STATUS "Converting ${file}.aseprite")
	set(dst_file ${ASSETS_DST_DIR}/${file}.png)
	add_custom_command(
		OUTPUT ${dst_file}
		DEPENDS ${image}
		COMMAND ${ASEPRITE} --batch --sheet ${dst_file} ${image} > ${ASSETS_DST_DIR}/${file}.json
	)
	list(APPEND ASSETS_OUTPUTS ${dst_file})
endforeach()

add_custom_target(assets ALL
	DEPENDS ${ASSETS_OUTPUTS}
)

# Adjust build settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML library
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Setup build
add_executable(${BINARY_NAME} ${SOURCES})
add_dependencies(${BINARY_NAME} assets)
target_include_directories(${BINARY_NAME} PRIVATE ${INCLUDE_PATHS})
target_compile_features(${BINARY_NAME} PRIVATE cxx_std_23)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::System)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::Graphics)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::Audio)
