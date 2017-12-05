//
// Created by snaiperskaya on 03/12/17.
//

#ifndef OPENMINE_OPENMINE_H
#define OPENMINE_OPENMINE_H

#include "glad/glad.h"

class OpenMine
{
public:
    static void Init();
protected:
	static void GlDebugMessage(GLenum source​, GLenum type​, GLuint id​, GLenum severity​, GLsizei length​, const GLchar* message​, const void* userParam​);
    static void GlfwErrorCallback(int Error, const char* Description);
    static void GlfwKeyCallback(struct GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
    static void InitializeOpenGl();
    static void SetupWindow();
protected:
    static struct GLFWwindow* Window;

};


#endif //OPENMINE_OPENMINE_H
