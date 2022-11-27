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
    tinygl::Mat4 modelMatrix{};
    tinygl::Mat4 projectionMatrix{};
    float moveSpeed{0.5f};              // movement speed, units per second
    float turnSpeed{90.0f};             // rotation speed, degrees per second
    int modelMatrixLocation{-1};
    int projectionMatrixLocation{-1};
};

void Window::init()
{
    program.addShaderFromSourceFile(tinygl::Shader::Type::Vertex, "test_03_02.vert");
    program.addShaderFromSourceFile(tinygl::Shader::Type::Fragment, "test_03_02.frag");
    program.link();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    vao.bind();

    const GLfloat positionData[] = {
         0.0f,  0.2f, 0.0f,
         0.1f, -0.2f, 0.0f,
        -0.1f, -0.2f, 0.0f
    };
    vbo.bind();
    vbo.create(sizeof(positionData), positionData);

    auto attributeLocation = program.attributeLocation("position");
    vao.setAttributeArray(attributeLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    vao.enableAttributeArray(attributeLocation);

    modelMatrix.postTranslate(tinygl::Vec3{0.0f, 0.0f, -1.0f});
    modelMatrixLocation = program.uniformLocation("modelMatrix");

    projectionMatrix = tinygl::Mat4::perspective(60.0f, 1.0f, 0.1f, 1000.0f);
    projectionMatrixLocation = program.uniformLocation("projectionMatrix");
}

void Window::processInput()
{
    auto moveAmount = moveSpeed * deltaTime();
    auto turnAmount = turnSpeed * deltaTime();

    if (getKey(tinygl::keyboard::Key::W) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{0.0f, moveAmount, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::S) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{0.0f, -moveAmount, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::A) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{-moveAmount, 0.0f, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::D) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{moveAmount, 0.0f, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::Z) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{0.0f, 0.0f, moveAmount});
    }

    if (getKey(tinygl::keyboard::Key::X) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preTranslate(tinygl::Vec3{0.0f, 0.0f, -moveAmount});
    }

    // global rotation
    if (getKey(tinygl::keyboard::Key::Q) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preRotate(turnAmount, tinygl::Vec3{0.0f, 0.0f, 1.0f});
    }

    if (getKey(tinygl::keyboard::Key::E) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.preRotate(-turnAmount, tinygl::Vec3{0.0f, 0.0f, 1.0f});
    }

    // local translation
    if (getKey(tinygl::keyboard::Key::I) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postTranslate(tinygl::Vec3{0.0f, moveAmount, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::K) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postTranslate(tinygl::Vec3{0.0f, -moveAmount, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::J) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postTranslate(tinygl::Vec3{-moveAmount, 0.0f, 0.0f});
    }

    if (getKey(tinygl::keyboard::Key::L) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postTranslate(tinygl::Vec3{moveAmount, 0.0f, 0.0f});
    }

    // local rotation
    if (getKey(tinygl::keyboard::Key::U) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postRotate(turnAmount, tinygl::Vec3{0.0f, 0.0f, 1.0f});
    }

    if (getKey(tinygl::keyboard::Key::O) == tinygl::keyboard::KeyState::Press) {
        modelMatrix.postRotate(-turnAmount, tinygl::Vec3{0.0f, 0.0f, 1.0f});
    }
}

void Window::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.use();
    vao.bind();
    program.setUniformValue(modelMatrixLocation, modelMatrix);
    program.setUniformValue(projectionMatrixLocation, projectionMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

MAIN
