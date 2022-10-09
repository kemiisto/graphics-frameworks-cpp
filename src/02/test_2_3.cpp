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
    tinygl::Buffer vbo{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vao;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_2_3.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_2_3.frag");
    program.link();

    glLineWidth(4.0f);

    vao.bind();

    const GLfloat positionData[] = {
         0.8f,  0.0f, 0.0f,
         0.4f,  0.6f, 0.0f,
        -0.4f,  0.6f, 0.0f,
        -0.8f,  0.0f, 0.0f,
        -0.4f, -0.6f, 0.0f,
         0.4f, -0.6f, 0.0f
    };
    vbo.bind();
    vbo.fill(positionData, sizeof(positionData));

    vao.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(0);
}

void Window::draw() {
    program.use();
    glDrawArrays(GL_LINE_LOOP, 0, 6);
}

MAIN
