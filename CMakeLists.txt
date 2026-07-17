cmake_minimum_required(VERSION 3.25)
project(sl_engine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- DEPENDENCIES: GLFW (STATIC) ---
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw EXCLUDE_FROM_ALL)

# --- DEPENDENCIES: HTTPLIB ---
set(HTTPLIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/httplib/httplib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/httplib/httplib.h
)
add_library(httplib SHARED ${HTTPLIB_SOURCES})
target_compile_definitions(httplib PRIVATE HTTPLIB_COMPILE WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0A00)
target_include_directories(httplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/httplib)
if(WIN32)
    target_link_libraries(httplib PRIVATE ws2_32)
endif()

# --- SOURCES ---
file(GLOB_RECURSE ENGINE_SOURCES
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp"
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES}
        src/lua/lua_env.hpp
        src/console/console_wrapper.hpp
        src/utils/math_extension.hpp
        src/utils/file_sys.cpp
        src/utils/file_sys.h
        src/lua/init_lua_modules.cpp
        src/lua/api/console.cpp
        src/lua/api/console.h
        src/lua/init_lua_modules.h
        src/lua/utils/converters.cpp
        src/lua/utils/converters.h
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/glad.c
        # ImGUI
        thirdparty/imgui/imgui.cpp
        thirdparty/imgui/imgui_draw.cpp
        thirdparty/imgui/imgui_tables.cpp
        thirdparty/imgui/imgui_widgets.cpp
        thirdparty/imgui/imgui_demo.cpp
        thirdparty/imgui/backends/imgui_impl_glfw.cpp
        thirdparty/imgui/backends/imgui_impl_opengl3.cpp
        src/utils/text.cpp
        src/utils/text.h
        src/render/window_init.cpp
        src/render/window_init.h
        src/render/ui_init.cpp
        src/render/ui_init.h
        src/render/render_frame.cpp
        src/render/render_frame.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# --- INCLUDES ---
target_include_directories(${PROJECT_NAME} PRIVATE
        "src"
        "thirdparty/sol2/include"
        "thirdparty/luajit/src"
        # GLFW
        "thirdparty/glfw/include"
        "thirdparty/glad"
        # ImGUI
        "thirdparty/imgui"
        "thirdparty/imgui/backends"
        #
        "thirdparty/cgltf"
        "thirdparty/tinydir"
)

# --- DEFINITIONS & LIBRARIES ---
target_compile_definitions(${PROJECT_NAME} PRIVATE
        SOL_USING_LUAJIT=1
        SOL_ALL_SAFETIES_ON=1
        LUA_BUILD_AS_DLL=1
        _CRT_SECURE_NO_WARNINGS
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
        glfw
        httplib
        ${LUAJIT_LIB_NAME}
        opengl32
)
target_link_directories(${PROJECT_NAME} PRIVATE
        "thirdparty/luajit/src")

# --- AUTO-COPY ALL WINDOWS DLLs TO SOURCE ROOT ---
if(WIN32)
    set(DLL_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

    # LuaJIT
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${DLL_OUTPUT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/luajit/src/lua51.dll"
            "${DLL_OUTPUT_DIR}/lua51.dll"
    )

    # httplib
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${DLL_OUTPUT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:httplib>"
            "${DLL_OUTPUT_DIR}/$<TARGET_FILE_NAME:httplib>"
    )

    # SYSTEM
    if(NOT MSVC)
        get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

        set(MINGW_DLLS
                "libgcc_s_seh-1.dll"
                "libstdc++-6.dll"
                "libwinpthread-1.dll"
        )

        foreach(DLL_NAME ${MINGW_DLLS})
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory "${DLL_OUTPUT_DIR}"
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${MINGW_BIN_DIR}/${DLL_NAME}"
                    "${DLL_OUTPUT_DIR}/${DLL_NAME}"
            )
        endforeach()
    endif()
endif()
