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
    tinygl::Buffer vboTriangle{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::Buffer vboSquare{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vaoTriangle;
    tinygl::VertexArrayObject vaoSquare;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_2_3.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_2_3.frag");
    program.link();

    glLineWidth(4.0f);

    // Triangle
    vaoTriangle.bind();

    const GLfloat positionDataTriangle[] = {
        -0.5f, 0.8f, 0.0f,
        -0.2f, 0.2f, 0.0f,
        -0.8f, 0.2f, 0.0f
    };
    vboTriangle.bind();
    vboTriangle.fill(positionDataTriangle, sizeof(positionDataTriangle));

    vaoTriangle.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vaoTriangle.enableAttributeArray(0);

    // Square
    vaoSquare.bind();

    const GLfloat positionDataSquare[] = {
        0.8f, 0.8f, 0.0f,
        0.8f, 0.2f, 0.0f,
        0.2f, 0.2f, 0.0f,
        0.2f, 0.8f, 0.0f
    };
    vboSquare.bind();
    vboSquare.fill(positionDataSquare, sizeof(positionDataSquare));

    vaoSquare.setAttributeArray(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vaoSquare.enableAttributeArray(0);
}

void Window::draw() {
    program.use();

    vaoTriangle.bind();
    glDrawArrays(GL_LINE_LOOP, 0, 3);

    vaoSquare.bind();
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

MAIN
