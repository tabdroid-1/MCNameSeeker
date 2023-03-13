cmake_minimum_required(VERSION 3.20)
project(NameSeeker
        LANGUAGES C CXX
        )
        
set(CMAKE_CXX_STANDARD 17)

###################################################################
# Local variables
###################################################################
set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(PROJECT_VENDOR_DIR "${CMAKE_CURRENT_LIST_DIR}/vendor")


# Vendor/Libraries
if(APPLE)
    set(CURL "${PROJECT_VENDOR_DIR}/curl-osx")
    set(CURLLIB "${CURL}/lib/libcurl.dylib")
endif()
if(WIN32)
    set(CURL "${PROJECT_VENDOR_DIR}/curl-win")
    set(CURLLIB "${CURL}/lib/libcurl.a")
endif()

###################################################################
# Project Sources and add library
###################################################################
file(GLOB_RECURSE PROJECT_SOURCES
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"
        )

# Additional project sources (vendors, etc.)
list(APPEND PROJECT_SOURCES
        # Vendor sources --------------------------
        "${CURL}/include/curl/curl.h"
        # -----------------------------------------
        )

# Add library
add_executable(${PROJECT_NAME} "${PROJECT_SOURCES}")

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_VENDOR_DIR}"
        "${CURL}/include"
        )

###################################################################
# Libraries
###################################################################

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${CURLLIB}
        )
