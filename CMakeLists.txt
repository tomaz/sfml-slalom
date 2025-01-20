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

function(aseprite_spritesheet desc file)
	add_custom_command(
		TARGET ${BINARY_NAME}
		POST_BUILD
		DEPENDS ${ASSETS_SRC_DIR}/${file}.aseprite
		COMMENT ${desc}
		COMMAND ${ASEPRITE} --batch --sheet ${ASSETS_DST_DIR}/${file}.png ${ASSETS_SRC_DIR}/${file}.aseprite > ${ASSETS_DST_DIR}/${file}.json
	)
endfunction()

# Prepare various module flags
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)	# FetchContent should use caches when offline

# Prepare all source and header files
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${SRC_DIR}/*.hpp")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

# Recursively find all header files and prepare their unique paths
set(INCLUDE_PATHS "")
foreach (HEADER_FILE ${HEADERS})
	get_filename_component(HEADER_DIR ${HEADER_FILE} PATH)
	list(APPEND INCLUDE_PATHS ${HEADER_DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_PATHS)

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
target_include_directories(${BINARY_NAME} PRIVATE ${INCLUDE_PATHS})
target_compile_features(${BINARY_NAME} PRIVATE cxx_std_23)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::System)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::Graphics)
target_link_libraries(${BINARY_NAME} PRIVATE SFML::Audio)

# Convert Aseprite images
file(MAKE_DIRECTORY ${ASSETS_DST_DIR})
aseprite_spritesheet("Convert red flag image" flag-red)