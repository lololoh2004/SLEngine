cmake_minimum_required(VERSION 3.25)
project(luengine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DEPENDENCIES: BGFX ---
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(BGFX_LIBRARY_TYPE "DYNAMIC_LIBRARY" CACHE STRING "" FORCE)
add_subdirectory(thirdparty/bgfx.cmake EXCLUDE_FROM_ALL)

# --- DEPENDENCIES: GLFW (STATIC) ---
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw EXCLUDE_FROM_ALL)

# --- SOURCES ---
file(GLOB_RECURSE ENGINE_SOURCES
        "srceng/*.cpp"
        "srceng/*.h"
        "srceng/*.hpp"
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES}
        srceng/glua/lua_env.hpp
        srceng/console/console_wrapper.hpp
        srceng/console/console_additions.cpp
        srceng/console/console_additions.h
        srceng/glua/math.hpp
        srceng/utils/file_sys.cpp
        srceng/utils/file_sys.h
        srceng/glua/base_api.hpp
        srceng/glua/console.cpp
        srceng/glua/console.h
        srceng/utils/other.cpp
        srceng/utils/other.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# --- INCLUDES ---
target_include_directories(${PROJECT_NAME} PRIVATE
        "srceng"
        "thirdparty/sol2/include"
        "thirdparty/luajit/src"
        # BGFX & BX & BIMG
        "thirdparty/bgfx.cmake/bgfx/include"
        "thirdparty/bgfx.cmake/bx/include"
        "thirdparty/bgfx.cmake/bimg/include"
        # GLFW
        "thirdparty/glfw/include"
)

# --- DEFINITIONS & LIBRARIES ---
target_compile_definitions(${PROJECT_NAME} PRIVATE
        SOL_USING_LUAJIT=1
        SOL_ALL_SAFETIES_ON=1
        LUA_BUILD_AS_DLL=1
        _CRT_SECURE_NO_WARNINGS
        BGFX_SHARED_LIB_API=1
)

if(WIN32)
    if(MSVC)
        set(LUAJIT_LIB_NAME "lua51.lib")
    else()
        set(LUAJIT_LIB_NAME "lua51")
    endif()
else()
    set(LUAJIT_LIB_NAME "luajit")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        bgfx
        glfw
        ${LUAJIT_LIB_NAME}
)
target_link_directories(${PROJECT_NAME} PRIVATE "thirdparty/luajit/src")

# --- AUTO-COPY BGFX DLL ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:bgfx>"
        "${CMAKE_CURRENT_SOURCE_DIR}/$<TARGET_FILE_NAME:bgfx>"
)

# --- AUTO-COPY LUAJIT DLL ---
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/luajit/src/lua51.dll"
            "${CMAKE_CURRENT_SOURCE_DIR}/lua51.dll"
    )
endif()

if(WIN32 AND NOT MSVC)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    set(MINGW_DLLS
            "libgcc_s_seh-1.dll"
            "libstdc++-6.dll"
            "libwinpthread-1.dll"
    )

    foreach(DLL_NAME ${MINGW_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/${DLL_NAME}"
                "${CMAKE_CURRENT_SOURCE_DIR}/${DLL_NAME}"
        )
    endforeach()
endif()
