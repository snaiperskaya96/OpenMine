//
// Created by snaiperskaya on 03/12/17.
//

#ifndef OPENMINE_OPENMINE_H
#define OPENMINE_OPENMINE_H


class OpenMine
{
public:
    static void Init();
protected:
    static void GlfwErrorCallback(int Error, const char* Description);
    static void GlfwKeyCallback(struct GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
protected:
    static struct GLFWwindow* Window;
};


#endif //OPENMINE_OPENMINE_H
