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
    setKeyCallback([this](tinygl::keyboard::Key key, int /*scancode*/, tinygl::input::Action action, tinygl::input::Modifier /*mods*/) {
        if (key == tinygl::keyboard::Key::Space && action == tinygl::input::Action::Press) {
            spdlog::info("The 'space' key was just pressed down.");
        }
        if (key == tinygl::keyboard::Key::A && action == tinygl::input::Action::Release) {
            spdlog::info("The 'A' key was just released.");
        }
    });
}

void Window::processInput()
{
    if (getKey(tinygl::keyboard::Key::Right) == tinygl::keyboard::KeyState::Press) {
        spdlog::info("The 'right arrow' key is currently pressed.");
    }
}

MAIN
