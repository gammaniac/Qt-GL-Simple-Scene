#include "simplescene.h"
#include <iostream>

SimpleScene::SimpleScene()
{
}

void SimpleScene::initScene()
{
    shader.compileShaderFromFile("vertex.glsl", GLSLShader::VERTEX);
    shader.compileShaderFromFile("fragment.glsl", GLSLShader::FRAGMENT);
    if(!shader.link())
    {
        std::cerr << "Shader failed to link\n";
        return;
    }

    shader.use();

    GLfloat vertices[] =
    {
          0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        // Top
        -0.2f, 0.8f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.2f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.8f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // Bottom
        -0.2f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.2f, -0.8f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, -0.8f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // Left
        -0.8f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.8f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // Right
        0.8f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.8f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0, 1.0f, 0.0f, 0.0f, 1.0
    };

    GLubyte indices[] =
    {
        // Top
        0, 1, 3,
        0, 3, 2,
        3, 1, 4,
        3, 4, 2,
        // Bottom
        0, 5, 7,
        0, 7, 6,
        7, 5, 8,
        7, 8, 6,
        // Left
        0, 9, 11,
        0, 11, 10,
        11, 9, 12,
        11, 12, 10,
        // Right
        0, 13, 15,
        0, 15, 14,
        15, 13, 16,
        15, 16, 14
    };

    GLubyte alternateIndices[] =
    {
        // Outer square border:
        3, 4, 16,
        3, 15, 16,
        15, 16, 8,
        15, 7, 8,
        7, 8, 12,
        7, 11, 12,
        11, 12, 4,
        11, 3, 4,

        // Inner square
        0, 11, 3,
        0, 3, 15,
        0, 15, 7,
        0, 7, 11
    };

    GLuint vertexSize = 8 * sizeof(GLfloat);
    GLuint rgbaOffset = 4 * sizeof(GLfloat);
    activeBuffer = 1;

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    glGenBuffers(1, &vboHandles[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandles[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &vboHandles[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandles[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vboHandles[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandles[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(alternateIndices), alternateIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);  // position
    glEnableVertexAttribArray(1);  // color
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexSize, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexSize, (GLubyte *)rgbaOffset);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandles[activeBuffer]);
    glBindVertexArray(0);
}

void SimpleScene::update(float t)
{
    static float angle = 0.0f;
    angle += t;
    shader.setUniform("twist", angle);
}

void SimpleScene::changeScene(int handle)
{
    activeBuffer = handle;
    glBindVertexArray(vaoHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboHandles[activeBuffer]);
    glBindVertexArray(0);
}

void SimpleScene::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vaoHandle);

    if(activeBuffer == 1)
        glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_BYTE, NULL);
    else
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);

    glBindVertexArray(0);
}

void SimpleScene::resize(int w, int h)
{
    glViewport(0,0,w,h);
}
