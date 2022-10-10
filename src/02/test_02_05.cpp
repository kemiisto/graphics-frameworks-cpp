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
    tinygl::Buffer vboPosition{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::Buffer vboColor{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vao;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_02_05.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_02_05.frag");
    program.link();

    glPointSize(10.0f);
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
    vboPosition.bind();
    vboPosition.fill(positionData, sizeof(positionData));

    auto attributeLocation = program.attributeLocation("position");
    vao.setAttributeArray(attributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(attributeLocation);

    const GLfloat colorData[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 1.0f
    };
    vboColor.bind();
    vboColor.fill(colorData, sizeof(colorData));

    attributeLocation = program.attributeLocation("vertexColor");
    vao.setAttributeArray(attributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(attributeLocation);
}

void Window::draw() {
    program.use();
    vao.bind();
    glDrawArrays(GL_LINE_LOOP, 0, 6);
}

MAIN
