cmake_minimum_required(VERSION 2.6)
project(OnionRing)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(BUILD_STATIC TRUE CACHE BOOL "TRUE to build static libraries, FALSE to build shared libraries (preferred)")

set(GLFWDIR "" CACHE PATH "Path to glfw dir")
set(GLM_ROOT_DIR "" CACHE PATH "Path to glm dir")
set(GLEWDIR "" CACHE PATH "Path to glew dir")
set(GLDIR "" CACHE PATH "Path to openGL dir")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-extras/")

set(GLFWDIR "${PROJECT_SOURCE_DIR}/dependencies/glfw")
set(GLEWDIR "${PROJECT_SOURCE_DIR}/dependencies/glew")

ADD_SUBDIRECTORY(dependencies)
find_package(GL REQUIRED)
find_package(X11 REQUIRED)

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/OnionRing/ ${PROJECT_SOURCE_DIR}/dependencies/glfw/include/ ${gl_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/dependencies/glew/include/ ${PROJECT_SOURCE_DIR}/dependencies/lua/include/ ${PROJECT_SOURCE_DIR}/dependencies/z/ ${PROJECT_SOURCE_DIR}/dependencies/soil/)

ADD_DEFINITIONS(
    -std=c++11
)

add_subdirectory(${PROJECT_SOURCE_DIR}/OnionRing)
add_subdirectory(${PROJECT_SOURCE_DIR}/OnionLoader)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/OnionRing/src/" DESTINATION include/OnionRing FILES_MATCHING PATTERN "*.h")
