#include "main.h"
#include <tinygl/tinygl.h>
#include <iostream>

class Window final : public tinygl::Window
{
public:
    using tinygl::Window::Window;
    void init() override;
    void processInput() override;
    void draw() override;
private:
    tinygl::ShaderProgram program;
    tinygl::Buffer vbo{tinygl::Buffer::Type::VertexBuffer, tinygl::Buffer::UsagePattern::StaticDraw};
    tinygl::VertexArrayObject vao;
    int translationLocation{-1};
    int baseColorLocation{-1};
    tinygl::Vec3 translation{-0.5f, 0.0f, 0.0f};
    GLfloat speed = 0.5f;
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_02_06.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_02_06.frag");
    program.link();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    vao.bind();

    const GLfloat positionData[] = {
         0.0f,  0.2f, 0.0f,
         0.2f, -0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f
    };
    vbo.bind();
    vbo.create(sizeof(positionData), positionData);

    auto attributeLocation = program.attributeLocation("position");
    vao.setAttributeArray(attributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(attributeLocation);

    translationLocation = program.uniformLocation("translation");
    baseColorLocation = program.uniformLocation("baseColor");
}

void Window::processInput()
{
    auto distance = speed * deltaTime();
    if (getKey(tinygl::keyboard::Key::Left) == tinygl::keyboard::KeyState::Press)
        translation.x -= distance;
    if (getKey(tinygl::keyboard::Key::Right) == tinygl::keyboard::KeyState::Press)
        translation.x += distance;
    if (getKey(tinygl::keyboard::Key::Down) == tinygl::keyboard::KeyState::Press)
        translation.y -= distance;
    if (getKey(tinygl::keyboard::Key::Up) == tinygl::keyboard::KeyState::Press)
        translation.y += distance;
}

void Window::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    program.use();
    vao.bind();
    program.setUniformValue(translationLocation, translation);
    program.setUniformValue(baseColorLocation, tinygl::Vec3{1.0f, 0.0f, 0.0f});
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN
