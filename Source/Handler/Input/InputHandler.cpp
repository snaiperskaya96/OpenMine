//
// Created by verrignij on 07/12/2017.
//

#include "InputHandler.h"

std::vector<Action> InputHandler::InputBindings;

/*void InputHandler::OnKeyPress(int KeyCode, InputAction Action, Entity *Caller, void* Callback)
{
    InputBindings.push_back({KeyCode, Action, Caller, Callback});
}
 */

void InputHandler::GlfwKeyCallback(struct GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    for (auto& Binding : InputBindings) {
        if (Binding.KeyCode == Key && (int)Binding.KeyAction == Action) {
            Binding.CallBack();
        }
    }

    if (Key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(Window, true);
    }
}

void InputHandler::Init(GLFWwindow* Window)
{
    glfwSetKeyCallback(Window, &InputHandler::GlfwKeyCallback);
}
