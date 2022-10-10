#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>

class Window final : public tinygl::Window
{
public:
    using tinygl::Window::Window;
    void init() override;
    void draw() override;
private:
    tinygl::ShaderProgram program;
    tinygl::VertexArrayObject vao;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_02_02.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_02_02.frag");
    program.link();

    vao.bind();

    glPointSize(10.0f);
}

void Window::draw() {
    program.use();
    glDrawArrays(GL_POINTS, 0, 1);
}


MAIN
