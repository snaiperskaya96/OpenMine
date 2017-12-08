//
// Created by verrignij on 07/12/2017.
//

#ifndef OPENMINE_INPUTHANDLER_H
#define OPENMINE_INPUTHANDLER_H

#include "Entity/Entity.h"
#include "GLFW/glfw3.h"
#include <cstdint>
#include <functional>
#include <utility>

typedef std::function<void()> InputCallback;
typedef std::function<void(float, float)> MousePositionCallback;

enum class InputAction
{
    KEY_PRESSED = 1,
    KEY_REPEATED = 2,
    KEY_RELEASED = 0,
    KEY_UNKNOWN_ACTION = -1
};

enum class InputMode
{
    CURSOR = 0x00033001,
    STICKY_KEYS = 0x00033002,
    STICKY_MOUSE_BUTTONS = 0x00033003,
};

enum class InputModeValue
{
    CURSOR_NORMAL = 0x00034001,
    CURSOR_HIDDEN = 0x00034002,
    CURSOR_DISABLED = 0x00034003,
    STICKY_KEYS_ENABLED = -1,
    STICKY_KEYS_DISABLED = -2,
    STICKY_MOUSE_BUTTONS_ENABLED = -3,
    STICKY_MOUSE_BUTTONS_DISABLED = -4,
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

    template<typename CallerType, typename _BoundArgs>
    static inline void OnMouseMove(_BoundArgs Caller, CallerType&& FunctionPointer)
    {
        MousePositionCallback CallBack = std::bind(FunctionPointer, Caller, std::placeholders::_1, std::placeholders::_2);
        MouseBindings.push_back(CallBack);
    };

    template<typename CallerType>
    static inline void OnMouseMove(std::nullptr_t, CallerType&& FunctionPointer)
    {
        MousePositionCallback CallBack = std::bind(FunctionPointer, std::placeholders::_1, std::placeholders::_2);
        MouseBindings.push_back(CallBack);
    };

    static void SetInputMode(InputMode Mode, InputModeValue Value);
protected:
    static void GlfwKeyCallback(GLFWwindow *Window, int Key, int ScanCode, int Action, int Mods);
    static void GlfwMouseCallback(GLFWwindow* Window, double XPosition, double YPosition);
private:
protected:
    static std::vector<Action> InputBindings;
    static std::vector<MousePositionCallback> MouseBindings;
};


#endif //OPENMINE_INPUTHANDLER_H
