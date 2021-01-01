cmake_minimum_required(VERSION 3.10)
#set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")
#set(CMAKE_C_COMPILER  "/usr/bin/clang")
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME ft_vox)

project(${PROJECT_NAME})
add_compile_options(
    # -Werror
	-g
#    -Wall
#        -Wextra
    # -Wpedantic

    # -Wcast-align
    # -Wcast-qual
    # -Wconversion
    # -Wctor-dtor-privacy
    # -Wenum-compare
    # -Wfloat-equal
    # -Wnon-virtual-dtor
    # -Wold-style-cast
    # -Woverloaded-virtual
    # -Wredundant-decls
    # -Wsign-conversion
    # -Wsign-promo
)
# target_compile_features(${PROJECT_NAME} cxx_std_17)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#add_subdirectory(./libs/glfw/)
 add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(INCLUDES
    src/VertexBuffer/
    include/
    libs/glad/include/glad/
        libs/glad/include/
    libs/glfw/include/
    libs/stb_image/
    libs/imgui/backends
    libs/imgui/
    libs/glm/  src/
    src/Debug/ src/World/ src/PerlinNoise/ src/Utils/ libs/FastNoise/Cpp/)
set(SOURCEFILES
    src/main.cpp
    libs/glad/src/glad.c libs/stb_image/stb_image.h libs/stb_image/stb_image_helper.cpp src/camera.cpp
    libs/imgui/imgui.cpp libs/imgui/imgui_draw.cpp libs/imgui/imgui_widgets.cpp libs/imgui/backends/imgui_impl_opengl3.cpp libs/imgui/backends/imgui_impl_glfw.cpp
        libs/imgui/imgui_tables.cpp
    src/engine.cpp src/Entity.cpp src/Events.cpp src/Model.cpp src/Render.cpp src/Shader.cpp src/skybox.cpp src/sandbox.cpp src/scene.cpp
    src/Animator.cpp src/Animator.h src/Animation.cpp src/Animation.h src/AnimationKey.cpp src/AnimationKey.h src/VertexBuffer/VertexBuffer.cpp
    src/VertexBuffer/VertexBuffer.h src/VertexBuffer/VertexArray.cpp src/VertexBuffer/VertexArray.h src/VertexBuffer/VertexBuffersLayout.cpp
    src/VertexBuffer/VertexBuffersLayout.h src/VertexBuffer/Vertex.cpp src/VertexBuffer/Vertex.h src/Mesh.cpp src/Mesh.h src/Debug/DebugGl.cpp
    src/Debug/DebugGl.h  src/World/Chunk.cpp src/World/Chunk.h src/World/Block.cpp src/World/Block.h
    src/World/Quad.cpp src/World/Quad.h src/PerlinNoise/PerlinNoise.cpp
    src/Utils/AtlasSlicer.cpp src/Utils/AtlasSlicer.h)
include_directories(${INCLUDES})
add_executable(${PROJECT_NAME} ${SOURCEFILES})
link_directories(${INCLUDES}
    //${CMAKE_CURRENT_SOURCE_DIR}/libs/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/src
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/win/)

#find_package(GLM REQUIRED)
#message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#find_package(ASSIMP REQUIRED)
#message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw )
elseif(APPLE)
    find_library(COCOA_Framework Cocoa)
    find_library(OpenGL_Framework OpenGL)
    find_library(IOKit_Framework IOKit)
    find_library(CoreVideo_Framework CoreVideo)

    target_link_libraries(${PROJECT_NAME}
            glfw 
            ${COCOA_Framework} ${OpenGL_Framework}
            ${IOKit_Framework} ${CoreVideo_Framework})
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}
            glfw 
            GL X11 pthread dl)
endif()