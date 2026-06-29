cmake_minimum_required(VERSION 3.25)
project(luengine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DEPENDENCIES: RAYLIB ---
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/raylib EXCLUDE_FROM_ALL)

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
        srceng/glua/math.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# --- INCLUDES ---
target_include_directories(${PROJECT_NAME} PRIVATE
        "srceng"
        "thirdparty/sol2/include"
        "thirdparty/luajit/src"
        "thirdparty/raylib/src"
)

# --- DEFINITIONS & LIBRARIES ---
target_compile_definitions(${PROJECT_NAME} PRIVATE
        SOL_USING_LUAJIT=1
        SOL_ALL_SAFETIES_ON=1
        LUA_BUILD_AS_DLL=1
        _CRT_SECURE_NO_WARNINGS
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/luajit/src/lua51.lib"
        raylib
)

# --- AUTO-COPY RAYLIB DLL ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:raylib>"
        "${CMAKE_CURRENT_SOURCE_DIR}/$<TARGET_FILE_NAME:raylib>"
)

# --- AUTO-COPY LUAJIT DLL ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/luajit/src/lua51.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/lua51.dll"
)

# --- A DUMP OF MSVC SYSTEM DLLs FOR USERS ---
if(MSVC)
    # Find the location of the compiler binaries folder
    get_filename_component(COMPILER_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    # runtime-libs Microsoft, which can be modified
    set(MSVC_DLLS
            "vcruntime140.dll"
            "msvcp140.dll"
            "vcruntime140_1.dll"
    )

    # Copy in PROJECT root
    foreach(DLL_NAME ${MSVC_DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${COMPILER_DIR}/${DLL_NAME}"
                "${CMAKE_CURRENT_SOURCE_DIR}/${DLL_NAME}"
        )
    endforeach()
endif()
