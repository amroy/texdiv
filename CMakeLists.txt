cmake_minimum_required(VERSION 3.5)
project(texdiv)

set(CMAKE_CXX_STANDARD 14)

# Set major, minor and patch version for library and hence a convenience
# variable containing the version string.
set(TEXDIV_MAJOR_VERSION "1")
set(TEXDIV_MINOR_VERSION "0")
set(TEXDIV_PATCH_VERSION "0")
set(TEXDIV_VERSION
        "${TEXDIV_MAJOR_VERSION}.${TEXDIV_MINOR_VERSION}.${TEXDIV_PATCH_VERSION}")

find_package(Boost 1.58.0 COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
    message(STATUS "OpenGL_INCLUDE_DIRS: ${OPENGL_INCLUDE_DIR}")
    message(STATUS "OpenGL_LIBRARIES: ${OPENGL_LIBRARIES}")
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OPENGL_LIBRARIES})
endif()

find_package(GLEW 2.1 REQUIRED)
if (GLEW_FOUND)
    message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIR}")
    message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
    include_directories(${GLEW_INCLUDE_DIRS})
    #link_libraries(${GLEW_LIBRARIES})
    link_directories(/usr/lib64)
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    message(STATUS "GLUT_INCLUDE_DIRS: ${GLUT_INCLUDE_DIR}")
    message(STATUS "GLUT_LIBRARIES: ${GLUT_LIBRARY}")
    include_directories(${GLUT_INCLUDE_DIRS})
    link_libraries(${GLUT_LIBRARY})
endif()

find_package(OpenCL REQUIRED)
if(OpenCL_FOUND)
    message(STATUS "OpenCL_INCLUDE_DIRS: ${OpenCL_INCLUDE_DIRS}")
    message(STATUS "OpenCL_LIBRARY: ${OpenCL_LIBRARY}")
    message(STATUS "OpenCL_VERSION: ${OpenCL_VESRION}")
    include_directories(${OpenCL_INCLUDE_DIRS})
    link_directories(${OpenCL_LIBRARY})
endif()

# Local project include directory
include_directories( ${PROJECT_SOURCE_DIR}/include )

add_executable(${PROJECT_NAME} src/main.cpp
        include/texdiv.h
        include/gl_helper.h
        src/gl_helper.cpp
        include/kullack_leibller.h
        include/cauchy_schwarz.h
        src/kullback_leibller.cpp)

if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

if (OpenCL_FOUND)
    target_link_libraries (${PROJECT_NAME} ${OpenCL_LIBRARY})
endif ()

if (OpenGL_FOUND)
    target_link_libraries (${PROJECT_NAME} ${OPENGL_LIBRARIES} GLEW ${GLUT_LIBRARY})
endif ()