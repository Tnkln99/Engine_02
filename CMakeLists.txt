cmake_minimum_required(VERSION 3.15)

project(Engine_02 VERSION 1.0.0 DESCRIPTION "Engine_02 game on openGl" LANGUAGES CXX)

find_package(Git)

if(GIT_FOUND)
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
        message(STATUS "Initializing git repository...")
        execute_process(COMMAND ${GIT_EXECUTABLE} init WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_INIT_RESULT)

        if(NOT GIT_INIT_RESULT EQUAL "0")
            message(FATAL_ERROR "Unable to initialize git repository.")
        endif()
    endif()

    message(STATUS "Retrieving git submodules...")

    set(SUBMODULES lib/stb;lib/glad;lib/glfw;lib/glm;lib/imgui;)
    set(REPOSITORIES https://github.com/nothings/stb.git;https://github.com/Dav1dde/glad.git;https://github.com/glfw/glfw.git;https://github.com/g-truc/glm.git;https://github.com/ocornut/imgui.git;)
    set(RELEASES master;master;3.2.1;0.9.9.8;docking;)

    foreach(UPD_SUB IN LISTS SUBMODULES)
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote -- ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)

        list(FIND SUBMODULES ${UPD_SUB} SUB_INDEX)
        list(GET REPOSITORIES ${SUB_INDEX} SUB_URL)
        list(GET RELEASES ${SUB_INDEX} SUB_RELEASE)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule add ${SUB_URL} ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)

            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "Unable to retrieve submodule ${UPD_SUB}")
            endif()
        endif()

        execute_process(COMMAND ${GIT_EXECUTABLE} checkout ${SUB_RELEASE} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/${UPD_SUB} RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(SEND_ERROR "Unable to checkout branch ${SUB_RELEASE} of repository ${UPD_SUB}")
        endif()
    endforeach()
else()
    message(FATAL_ERROR "Git not found.")
endif()

set(LIB_STB ON)
set(LIB_GLAD ON)
set(LIB_GLFW ON)
set(LIB_GLM ON)
set(LIB_IMGUI ON)

add_compile_definitions(LIB_STB)
add_compile_definitions(LIB_GLAD)
add_compile_definitions(LIB_GLFW)
add_compile_definitions(LIB_GLM)
add_compile_definitions(LIB_IMGUI)

if(UNIX)
    add_compile_definitions(UNIX)
elseif(WIN32)
    add_compile_definitions(WINDOWS)
else()
    message(FATAL_ERROR "Detected platform is not supported!")
endif()

if(LIB_GLEW)
    message(FATAL_ERROR "GLAD is not compatible with GLEW.")
endif()

if(NOT (LIB_GLFW OR LIB_SDL))
    message(FATAL_ERROR "GLAD requires GLFW or SDL.")
endif()

add_subdirectory(lib/glad)
include_directories(${CMAKE_BINARY_DIR}lib/glad/include)
if(LIB_SDL)
    message(FATAL_ERROR "GLFW is not compatible with SDL.")
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)
include_directories(lib/glm/glm)
include_directories(lib/stb)
if(NOT (LIB_GLEW OR LIB_GLAD))
    message(FATAL_ERROR "Imgui requires GLEW or GLAD.")
endif()

if(NOT (LIB_GLFW OR LIB_SDL))
    message(FATAL_ERROR "Imgui requires GLFW or SDL.")
endif()

include_directories(lib/imgui lib/imgui/backends)

if(LIB_GLFW)
    file(GLOB IMGUI_FILES "./lib/imgui/*.h" "./lib/imgui/*.cpp" "./lib/imgui/backends/*glfw*" "./lib/imgui/backends/*opengl3*")
elseif(LIB_SDL)
    file(GLOB IMGUI_FILES "./lib/imgui/*.h" "./lib/imgui/*.cpp" "./lib/imgui/backends/*sdl*" "./lib/imgui/backends/*opengl3*")
endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/res/)
    message(STATUS "Copying resources...")
    file(COPY ${PROJECT_SOURCE_DIR}/res/ DESTINATION ${CMAKE_BINARY_DIR}/res/)
endif()

message(STATUS "Setting up build options...")
file(GLOB_RECURSE SRC_FILES "./scr/*.h" "./scr/*.cpp")
add_executable(Engine_02 ${SRC_FILES} ${IMGUI_FILES})

if(LIB_GLAD AND UNIX)
    target_compile_options(Engine_02 -DIMGUI_IMPL_OPENGL_LOADER_GLAD)
endif()

message(STATUS "Linking...")
find_package(OpenGL REQUIRED)
target_link_libraries(Engine_02 ${OPENGL_LIBRARIES})
target_link_libraries(Engine_02 glad ${CMAKE_DL_LIBS})
add_subdirectory( lib/maths )
target_link_libraries(Engine_02 glfw maths)

if(UNIX)
    target_link_libraries(Engine_02 X11)
endif()
