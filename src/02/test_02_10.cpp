#include "main.h"
#include <tinygl/tinygl.h>
#include <spdlog/spdlog.h>
#include <iostream>

class Window final : public tinygl::Window
{
public:
    using tinygl::Window::Window;
    void init() override;
    void processInput() override;
};

void Window::init()
{
    spdlog::info("[Window] Initializing...");
    setKeyCallback([this](tinygl::Key key, int /*scancode*/, tinygl::KeyAction action, tinygl::Modifier /*mods*/) {
        if (key == tinygl::Key::Space && action == tinygl::KeyAction::Press) {
            spdlog::info("The 'space' key was just pressed down.");
        }
        if (key == tinygl::Key::A && action == tinygl::KeyAction::Release) {
            spdlog::info("The 'A' key was just released.");
        }
    });
}

void Window::processInput()
{
    if (getKey(tinygl::Key::Right) == tinygl::KeyState::Press) {
        spdlog::info("The 'right arrow' key is currently pressed.");
    }
}

MAIN
