cmake_minimum_required(VERSION 3.7)
project(OpenMine)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

if (WIN32)
    set(ZLIB_ROOT "C:\\Program Files\\zlib" CACHE STRING "" FORCE)
endif()

add_subdirectory(ThirdParty/glfw-3.2.1)
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glm)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES Source/OpenMine/OpenMine.cpp Source/OpenMine/OpenMine.h
        Source/Shader/Shader.cpp Source/Shader/Shader.h
        Source/Utils/FileSystem/File.cpp Source/Utils/FileSystem/File.h
        Source/Texture/Texture.cpp Source/Texture/Texture.h ThirdParty/stb/stb_image.h
        Source/Utils/Misc/Misc.cpp Source/Utils/Misc/Misc.h Source/Utils/String/String.cpp
        Source/Utils/String/String.h ThirdParty/stb/stb_image_write.h Source/Entity/Entity.cpp
        Source/Entity/Entity.h Source/Cache/BaseCache.h Source/Pool/EntityPool.h
        Source/Pool/Pool.h Source/Camera/Camera.h Source/Camera/Camera.cpp Source/Pool/EntityPool.cpp
        Source/Pool/Pool.cpp Source/Entity/Cube/Cube.h Source/Entity/Triangle.h ThirdParty/OBJ-Loader/Source/OBJ_Loader.h
        Source/Component/Component.cpp Source/Component/Component.h Source/Component/MeshComponent.cpp
        Source/Component/MeshComponent.h Source/Handler/Input/InputHandler.cpp Source/Handler/Input/InputHandler.h
        Source/Cache/ObjLoaderCache.h Source/Math/Math.cpp Source/Math/Math.h
        Source/Entity/Chunk/Chunk.h Source/Utils/Thread/AsyncTask.cpp Source/Utils/Thread/AsyncTask.h Source/Utils/Thread/AsyncTask.h
        Source/Cache/TextureCache.h Source/Cache/ShaderCache.h Source/Handler/Terrain/TerrainHandler.cpp
        Source/Handler/Terrain/TerrainHandler.h Source/Entity/Chunk/Chunk.cpp Source/Renderer/Renderer.h
        Source/Renderer/Renderer.cpp Source/Renderer/Entity/MeshRenderer.cpp
        Source/Renderer/Entity/MeshRenderer.h Source/Renderer/Cube/CubeRenderer.cpp Source/Renderer/Cube/CubeRenderer.h
        Source/Utils/Loader/Obj/ObjLoader.h Source/Entity/Cube/Dirt.cpp Source/Entity/Cube/Dirt.h)

add_executable(OpenMine main.cpp ${SOURCE_FILES})

target_link_libraries(OpenMine glfw ${OPENGL_LIBRARIES} ${GLAD_LIBRARIES})
target_include_directories(OpenMine PUBLIC Source ${OPENGL_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIRS} ThirdParty/stb ThirdParty/glm ThirdParty/OBJ-Loader/Source/ ThirdParty/PerlinNoise)

file(COPY ${CMAKE_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/Textures DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/Objects DESTINATION ${CMAKE_BINARY_DIR}/)