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
    int translationLocation{-1};
    int baseColorLocation{-1};
    glm::vec3 translation{-0.5f, 0.0f, 0.0f};
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
    vbo.fill(positionData, sizeof(positionData));

    auto attributeLocation = program.attributeLocation("position");
    vao.setAttributeArray(attributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(attributeLocation);

    translationLocation = program.uniformLocation("translation");
    baseColorLocation = program.uniformLocation("baseColor");
}

void Window::draw() {
    translation.x += 0.01f;
    if (translation.x > 1.2f) {
        translation.x = -1.2f;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    program.use();
    vao.bind();
    program.setUniformValue(translationLocation, translation);
    program.setUniformValue(baseColorLocation, {1.0f, 0.0f, 0.0f});
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN