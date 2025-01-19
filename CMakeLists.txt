cmake_minimum_required(VERSION 3.14)
project(BlockKuzushi C)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FetchContent module is available since CMake 3.11
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.0.0 # You can specify the version you need
)

FetchContent_MakeAvailable(raylib)

# Add the executable
add_executable(${PROJECT_NAME} main.c)

# Link raylib and platform-specific libraries
if (WIN32)
  target_link_libraries(${PROJECT_NAME} raylib Winmm.lib opengl32.lib)
elseif (APPLE)
  target_link_libraries(${PROJECT_NAME} raylib "-framework IOKit" "-framework Cocoa" "-framework OpenGL" "-framework CoreVideo")
elseif (UNIX)
  target_link_libraries(${PROJECT_NAME} raylib m pthread dl GL GLU X11)
endif()

# Custom command to copy compile_commands.json to the project root
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/.vscode/compile_commands.json
  COMMENT "Copying compile_commands.json to project root"
)