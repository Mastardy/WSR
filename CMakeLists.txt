﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.17)

include(FetchContent)

project ("WSR" VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

set(COMPONENTS "GLFW;GLAD;GLM" CACHE STRING "The components to import and build")

foreach (comp IN ITEMS ${COMPONENTS})
    set(IMPORT_${comp} ON)
endforeach ()

if (IMPORT_GLAD)
    option(GLAD_DOWNLOAD "If set to ON the glad gl loader will be generated and downloaded, if OFF the included version (gl4.5/core) will be used" ON)
    if (GLAD_DOWNLOAD)
        set(GLAD_GL_VERSION 4.6 CACHE STRING "The target gl version")
        option(GLAD_GL_CORE "The target gl profile. ON = core profile, OFF = compatibility profile" ON)
        if (GLAD_GL_CORE)
            set(GLAD_GL_PROFILE core)
        else ()
            set(GLAD_GL_PROFILE compatibility)
        endif ()
    else ()
        unset(GLAD_GL_VERSION CACHE)
        unset(GLAD_GL_CORE CACHE)
    endif ()
else ()
    unset(GLAD_DOWNLOAD CACHE)
    unset(GLAD_GL_VERSION CACHE)
    unset(GLAD_GL_CORE CACHE)
endif ()

if (IMPORT_GLFW)
    set(GLFW_TAG master CACHE STRING "Defines the glfw version (e.g. master, 3.3.8, 3.3.7, ...) ")
else ()
    unset(GLFW_TAG CACHE)
endif ()

if (IMPORT_GLM)
    set(GLM_TAG master CACHE STRING "Defines the glm version (e.g. master, 0.9.9.8, 0.9.9.7, ...")
else ()
    unset(GLM_TAG CACHE)
endif ()

if (IMPORT_GLAD)
    if (NOT GLAD_DOWNLOAD)
        message(STATUS "Using included version of glad loader (gl 4.5/core) ")
        set(glad_SOURCE_DIR thirdparty/glad)
    else ()
        if ("${glad_INSTALLED_VERSION}" STREQUAL "${GLAD_GL_VERSION}-${GLAD_GL_PROFILE}")
            message(STATUS "Avoiding repeated download of glad gl ${GLAD_GL_VERSION}/${GLAD_GL_PROFILE}")
            set(glad_SOURCE_DIR ${glad_LAST_SOURCE_DIR})
        else ()
            find_program(CURL NAMES curl curl.exe)
            if (NOT CURL)
                message(STATUS "Could not find curl, using included version of the glad loader (gl 4.5/core)")
                set(glad_SOURCE_DIR thirdparty/glad)
            else ()
                execute_process(COMMAND ${CURL} -s -D - -X POST -d generator=c&api=egl%3Dnone&api=gl%3D4.5&profile=gl%3Dcore&api=gles1%3Dnone&profile=gles1%3Dcommon&api=gles2%3Dnone&api=glsc2%3Dnone&api=glx%3Dnone&api=vulkan%3Dnone&api=wgl%3Dnone&options=LOADER https://gen.glad.sh/generate OUTPUT_VARIABLE res)
                string(REGEX MATCH "[Ll]ocation: ([A-Za-z0-9_\\:/\\.]+)" location ${res})
                set(location "${CMAKE_MATCH_1}")
                if (NOT location)
                    message(STATUS "Could not extract location from http response, using included version of the glad loader (gl 4.5/core)")
                    set(glad_SOURCE_DIR thirdparty/glad)
                else ()
                    string(REGEX REPLACE "/$" "" location ${location})
                    string(APPEND location "/glad.zip")
                    if (NOT ${location} MATCHES "^http")
                        string(PREPEND location "https://gen.glad.sh")
                    endif ()
                    message(STATUS "Downloading glad for gl ${GLAD_GL_VERSION}/${GLAD_GL_PROFILE} from ${location} ")
                    FetchContent_Declare(
                            glad
                            URL ${location}
                    )
                    FetchContent_MakeAvailable(glad)
                    set(glad_INSTALLED_VERSION ${GLAD_GL_VERSION}-${GLAD_GL_PROFILE} CACHE INTERNAL "")
                    set(glad_LAST_SOURCE_DIR ${glad_SOURCE_DIR} CACHE INTERNAL "")
                endif ()
            endif ()
        endif ()
    endif ()

    add_library(
            glad
            ${glad_SOURCE_DIR}/src/gl.c
            ${glad_SOURCE_DIR}/include/glad/gl.h
            ${glad_SOURCE_DIR}/include/KHR/khrplatform.h
    )
    target_include_directories(glad PUBLIC ${glad_SOURCE_DIR}/include)
endif ()

if (IMPORT_GLFW)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG ${GLFW_TAG}
    )
    list(APPEND components glfw)
endif ()

if (IMPORT_GLM)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG ${GLM_TAG}
    )
    list(APPEND components glm)
endif ()

if (components)
    FetchContent_MakeAvailable(${components})
endif ()

# Include sub-projects.
add_subdirectory ("WSR")
