//
// Created by verrignij on 04/12/2017.
//

// Include standard headers
#include <cstdio>
#define ONE_DEG_IN_RAD ( 2.0 * 3.14 ) / 360.0 // 0.017444444


// Include GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader/Shader.h>
#include <Texture/Texture.h>
#include <glm/vec3.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtx/rotate_normalized_axis.inl>

GLFWwindow* window;

// Include GLM
#include "linmath.h"

int main(  )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    Shader S({
                     {"base-texture", ShaderType::Vertex},
                     {"base-texture", ShaderType::Fragment}
             });

    // Get a handle for our "MVP" uniform
    GLint MatrixID = glGetUniformLocation(S.GetProgramId(), "MVP");

    // Load the texture using any two methods
    //GLuint Texture = loadBMP_custom("uvtemplate.bmp");
    auto Tex = Texture::FromName("texture.tga");

    // Get a handle for our "myTextureSampler" uniform
    GLint TextureID  = glGetUniformLocation(S.GetProgramId(), "Texture");

    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -0.75f,-0.75f,-0.75f,
            -0.75f,-0.75f, 0.75f,
            -0.75f, 0.75f, 0.75f,
            0.75f, 0.75f,-0.75f,
            -0.75f,-0.75f,-0.75f,
            -0.75f, 0.75f,-0.75f,
            0.75f,-0.75f, 0.75f,
            -0.75f,-0.75f,-0.75f,
            0.75f,-0.75f,-0.75f,
            0.75f, 0.75f,-0.75f,
            0.75f,-0.75f,-0.75f,
            -0.75f,-0.75f,-0.75f,
            -0.75f,-0.75f,-0.75f,
            -0.75f, 0.75f, 0.75f,
            -0.75f, 0.75f,-0.75f,
            0.75f,-0.75f, 0.75f,
            -0.75f,-0.75f, 0.75f,
            -0.75f,-0.75f,-0.75f,
            -0.75f, 0.75f, 0.75f,
            -0.75f,-0.75f, 0.75f,
            0.75f,-0.75f, 0.75f,
            0.75f, 0.75f, 0.75f,
            0.75f,-0.75f,-0.75f,
            0.75f, 0.75f,-0.75f,
            0.75f,-0.75f,-0.75f,
            0.75f, 0.75f, 0.75f,
            0.75f,-0.75f, 0.75f,
            0.75f, 0.75f, 0.75f,
            0.75f, 0.75f,-0.75f,
            -0.75f, 0.75f,-0.75f,
            0.75f, 0.75f, 0.75f,
            -0.75f, 0.75f,-0.75f,
            -0.75f, 0.75f, 0.75f,
            0.75f, 0.75f, 0.75f,
            -0.75f, 0.75f, 0.75f,
            0.75f,-0.75f, 0.75f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const GLfloat g_uv_buffer_data[] = {
            0.000059f, 1.0f-0.000004f,
            0.000103f, 1.0f-0.336048f,
            0.335973f, 1.0f-0.335903f,
            1.000023f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.336024f, 1.0f-0.671877f,
            0.667969f, 1.0f-0.671889f,
            1.000023f, 1.0f-0.000013f,
            0.668104f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.000059f, 1.0f-0.000004f,
            0.335973f, 1.0f-0.335903f,
            0.336098f, 1.0f-0.000071f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.336024f, 1.0f-0.671877f,
            1.000004f, 1.0f-0.671847f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.668104f, 1.0f-0.000013f,
            0.335973f, 1.0f-0.335903f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.668104f, 1.0f-0.000013f,
            0.336098f, 1.0f-0.000071f,
            0.000103f, 1.0f-0.336048f,
            0.000004f, 1.0f-0.671870f,
            0.336024f, 1.0f-0.671877f,
            0.000103f, 1.0f-0.336048f,
            0.336024f, 1.0f-0.671877f,
            0.335973f, 1.0f-0.335903f,
            0.667969f, 1.0f-0.671889f,
            1.000004f, 1.0f-0.671847f,
            0.667979f, 1.0f-0.335851f
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3{4,3,3}, // Camera is at (4,3,3), in World Space
            glm::vec3{0,0,0}, // and looks at the origin
            glm::vec3{0,1,0}  // Head is up (set to 0,-1,0 to look upside-down)
    );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4();

    do{

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(S.GetProgramId());

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 Mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &Mvp[0][0]);

        Tex->Bind();

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                2,                                // size : U+V => 2
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            Model = glm::translate(Model, glm::vec3{0.10f, 0.1f, 0.f});
            //Model = glm::rotate(Model, 10.f, glm::vec3{1.0f, 1.0f, 1.0f});
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(S.GetProgramId());

    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
