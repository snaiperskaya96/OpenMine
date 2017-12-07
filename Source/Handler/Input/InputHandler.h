//
// Created by verrignij on 07/12/2017.
//

#ifndef OPENMINE_INPUTHANDLER_H
#define OPENMINE_INPUTHANDLER_H

#include "Entity/Entity.h"
#include "GLFW/glfw3.h"
#include <cstdint>
#include <functional>

typedef std::function<void()> InputCallback;

enum class InputAction
{
    KEY_PRESSED = 1,
    KEY_REPEATED = 2,
    KEY_RELEASED = 0,
    KEY_UNKNOWN_ACTION = -1
};

struct Action
{
    int KeyCode;
    InputAction KeyAction;
    void* Caller;
    InputCallback CallBack;
};

class InputHandler
{
public:
    static void Init(GLFWwindow* Window);

    template<typename CallerType, typename _BoundArgs>
    static inline void OnKeyPress(int KeyCode, InputAction Action, _BoundArgs Caller, CallerType&& FunctionPointer)
    {
        InputCallback CallBack = std::bind(FunctionPointer, Caller);
        InputBindings.push_back({KeyCode, Action, Caller, CallBack});
    };

    template<typename CallerType>
    static inline void OnKeyPress(int KeyCode, InputAction Action, std::nullptr_t, CallerType&& FunctionPointer)
    {
        InputCallback CallBack = std::bind(FunctionPointer);
        InputBindings.push_back({KeyCode, Action, nullptr, CallBack});
    };
protected:
    static void GlfwKeyCallback(GLFWwindow *Window, int Key, int Scancode, int Action, int Mods);
private:
protected:
    static std::vector<Action> InputBindings;
};


#endif //OPENMINE_INPUTHANDLER_H
