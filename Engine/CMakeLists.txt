cmake_minimum_required(VERSION 3.0.0)
project(OpenGL_LearningIMGUI)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Find packages
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Bullet REQUIRED)
find_package(GLM REQUIRED)
find_package(Assimp REQUIRED)

# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${BULLET_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

# Add your source files
set(SOURCES
    Graphics/Main.cpp   
    Graphics/Screen.cpp
    Graphics/Input.cpp
    vendors/glad/glad.c
    Graphics/Shader.cpp
    Graphics/Entity/Quad.cpp
    Graphics/Buffer.cpp
    Graphics/Entity/Camera.cpp
    Graphics/Texture.cpp
    Graphics/Entity/Light.cpp
    Graphics/Entity/Cube.cpp
    Graphics/Utilities/Utility.cpp
    Graphics/Entity/Model.cpp
    Graphics/Material.cpp
    Graphics/Entity/Grid.cpp
    Graphics/Entity/EmptyObject.cpp
    Graphics/Transform.cpp
    Graphics/Entity/World.cpp
    Graphics/Entity/PerspectiveGrid.cpp
    Graphics/Utilities/Timer.cpp
    vendors/imgui/imgui_demo.cpp
    vendors/imgui/imgui_draw.cpp
    vendors/imgui/imgui_tables.cpp
    vendors/imgui/imgui_widgets.cpp
    vendors/imgui/imgui.cpp
    vendors/imgui/backends/imgui_impl_opengl3.cpp
    vendors/imgui/backends/imgui_impl_sdl2.cpp
    vendors/imgui/backends/imgui_impl_sdlrenderer2.cpp
    Graphics/Entity/AssMesh.cpp
    Graphics/Entity/AssModel.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against libraries
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib
    /opt/homebrew/Cellar/sdl2_image/2.6.3_1/lib/libSDL2_image-2.0.0.dylib
    ${GLM_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_image
    OpenGL::GL     
)

# Copy resources if needed (e.g., shaders, textures)
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Add a custom target to run the binary
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running ${PROJECT_NAME}"
)

# set(CMAKE_CXX_FLAGS
#     "-framework OpenGL 
# 	-framework Cocoa 
# 	-framework IOKit 
# 	-framework CoreVideo 
# 	-framework CoreFoundation 
# 	-framework GLUT "
# )


