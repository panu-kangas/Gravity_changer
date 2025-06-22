cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(gravity 
src/main.cpp 
src/GameHandler.cpp 
src/Player.cpp 
src/Map.cpp 
src/Collectible.cpp 
src/InfoScreen.cpp 
src/StartScreen.cpp 
src/EndScreen.cpp
src/collisionHandling.cpp)

target_link_libraries(gravity PRIVATE sfml-graphics)
target_compile_features(gravity PRIVATE cxx_std_17)
target_include_directories(gravity PRIVATE include)

if(WIN32)
    add_custom_command(
        TARGET gravity
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:gravity>
        VERBATIM)
endif()
