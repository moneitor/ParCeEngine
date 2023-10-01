cmake_minimum_required(VERSION 3.0.0)
project(ParCe)

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




set(SOURCES
    vendors/imgui/imgui.cpp
    vendors/imgui/backends/imgui_impl_opengl3.cpp
    vendors/imgui/backends/imgui_impl_sdl2.cpp
    vendors/imgui/backends/imgui_impl_sdlrenderer2.cpp
    vendors/imgui/imgui_demo.cpp
    vendors/imgui/imgui_draw.cpp
    vendors/imgui/imgui_tables.cpp
    vendors/imgui/imgui_widgets.cpp
    vendors/glad/glad.c


    ParCe.cpp
    main.cpp
    Graphics/Screen.cpp
    Graphics/Input.cpp
    Graphics/Shader.cpp
    Graphics/Entity/Quad.cpp
    Graphics/Buffer.cpp
    Graphics/Texture.cpp    
    Graphics/Material.cpp
    Graphics/Transform.cpp

    Graphics/Utilities/Utility.cpp
    Graphics/Utilities/Timer.cpp    
    
    Graphics/Entity/PCamera.cpp
    Graphics/Entity/Model.cpp
    Graphics/Entity/EmptyObject.cpp
    Graphics/Entity/World.cpp
    Graphics/Entity/PerspectiveGrid.cpp
    Graphics/Entity/AssMesh.cpp
    Graphics/Entity/AssModel.cpp
    Graphics/Entity/Light.cpp
    Graphics/Entity/Cube.cpp
    Graphics/Entity/Sphere.cpp

    # Physics/Maths/PVec2.cpp
    # Physics/Maths/PVec3.cpp
    # Physics/Maths/PVec4.cpp
    # Physics/Maths/PMat2.cpp
    # Physics/Maths/PMat3.cpp
    # Physics/Maths/PMat4.cpp
    # Physics/Maths/PQuat.cpp
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
    m
)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_image
    OpenGL::GL     
)

# Add a custom target to run the binary
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running ${PROJECT_NAME}"
)


# Copy all the resources so we can use relative paths in our code
add_custom_target(copy_shaders
    COMMAND ${CMAKE_COMMAND} 
    -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/Graphics/Shaders/ 
    ${CMAKE_CURRENT_BINARY_DIR}/Graphics/Shaders/
)

add_custom_target(copy_models
    COMMAND ${CMAKE_COMMAND} 
    -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/Graphics/Models/ 
    ${CMAKE_CURRENT_BINARY_DIR}/Graphics/Models/
)

add_custom_target(copy_textures
    COMMAND ${CMAKE_COMMAND} 
    -E copy_directory 
    ${CMAKE_CURRENT_LIST_DIR}/Graphics/Textures/ 
    ${CMAKE_CURRENT_BINARY_DIR}/Graphics/Textures/
)

add_dependencies(${PROJECT_NAME}
    copy_shaders
    copy_models
    copy_textures
)

