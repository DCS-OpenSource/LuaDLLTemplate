cmake_minimum_required(VERSION 3.20)

include(FetchContent)

# === CONFIGURATION ===
set(PROJECT_NAME "DLL_Template")
set(TARGET_NAME "LuaPlugin")
set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

project(${PROJECT_NAME} DESCRIPTION "Lua plugin for doing C++ stuff in lua")

# === SOURCE FILES ===
file(GLOB_RECURSE SOURCE_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

# === TARGET ===
add_library(${TARGET_NAME} SHARED ${SOURCE_LIST})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 23)
endif()

set_target_properties(${TARGET_NAME} PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# === DEFINITIONS ===>
target_compile_definitions(${TARGET_NAME} PRIVATE LUA_BUILD_AS_DLL)

# === DEPENDENCIES ===
target_link_libraries(${TARGET_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/dcs-lua/lua.lib"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/dcs-lua/lua.lib"
)

target_include_directories(${TARGET_NAME}
    INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/dcs-lua/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/ext/dcs-lua/include"
)

# === OPTIONAL: Post-build copy ===
if (DEFINED LuaPlugin_BIN_PATH)
    message(STATUS "Copying ${TARGET_NAME}.dll to ${LuaPlugin_BIN_PATH}")
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:${TARGET_NAME}>"
            "${LuaPlugin_BIN_PATH}/$<TARGET_FILE_NAME:${TARGET_NAME}>"
        COMMENT "Copying ${TARGET_NAME} to bin"
    )
endif()
