//
// Created by verrignij on 07/12/2017.
//

#include <OpenMine/OpenMine.h>
#include "InputHandler.h"

std::vector<Action> InputHandler::InputBindings;
std::vector<MousePositionCallback> InputHandler::MouseBindings;

void InputHandler::GlfwKeyCallback(struct GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
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
    glfwSetCursorPosCallback(Window, &InputHandler::GlfwMouseCallback);
}

void InputHandler::SetInputMode(InputMode Mode, InputModeValue Value)
{
    auto CastedValue = (int)Value;
    if ((int)Mode < 0) {
        if (Value == InputModeValue::STICKY_KEYS_DISABLED || Value == InputModeValue::STICKY_MOUSE_BUTTONS_DISABLED) {
            CastedValue = GL_FALSE;
        } else {
            CastedValue = GL_TRUE;
        }
    }

    glfwSetInputMode(OpenMine::GetWindow(), (int)Mode, CastedValue);
}

void InputHandler::GlfwMouseCallback(GLFWwindow *Window, double XPosition, double YPosition)
{
    for (auto& Binding : MouseBindings) {
        Binding((float)XPosition, (float)YPosition);
    }
}
