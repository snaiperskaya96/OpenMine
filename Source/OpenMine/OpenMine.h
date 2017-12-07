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
    static struct GLFWwindow* GetWindow() { return Window; }
protected:
	static void GlDebugMessage(GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam);
	static void GlfwErrorCallback(int Error, const char* Description);
	static void GlfwKeyCallback(struct GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
	static void InitializeOpenGl();
	static void SetupWindow();
protected:
	static struct GLFWwindow* Window;

};


#endif //OPENMINE_OPENMINE_H
