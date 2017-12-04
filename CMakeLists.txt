cmake_minimum_required(VERSION 3.9)
project(OpenMine)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if (WIN32)
    set(ZLIB_ROOT "C:\\Program Files\\zlib" CACHE STRING "" FORCE)
endif()

add_subdirectory(ThirdParty/glfw-3.2.1)
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/libpng)
add_subdirectory(ThirdParty/glm)

include_directories(ThirdParty/LinMath)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES Source/OpenMine/OpenMine.cpp Source/OpenMine/OpenMine.h
        ThirdParty/LinMath/linmath.h Source/Shader/Shader.cpp Source/Shader/Shader.h
        Source/Utils/FileSystem/File.cpp Source/Utils/FileSystem/File.h
        Source/Texture/Texture.cpp Source/Texture/Texture.h ThirdParty/stb/stb_image.h)

add_executable(OpenMine main.cpp ${SOURCE_FILES})

target_link_libraries(OpenMine glfw ${OPENGL_LIBRARIES} ${GLAD_LIBRARIES} png)
target_include_directories(OpenMine PUBLIC Source ${OPENGL_INCLUDE_DIR} ${GLAD_INCLUDE_DIRS} ThirdParty/libpng/
        ThirdParty/stb ThirdParty/glm)

#add_executable(testexec test.cpp ${SOURCE_FILES})
#target_link_libraries(testexec glfw ${OPENGL_LIBRARIES} ${GLAD_LIBRARIES} png glm)
#target_include_directories(testexec PUBLIC Source ${OPENGL_INCLUDE_DIR} ${GLAD_INCLUDE_DIRS} ThirdParty/libpng/
#        ThirdParty/stb ThirdParty/glm)

file(COPY ${CMAKE_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/Textures DESTINATION ${CMAKE_BINARY_DIR}/)