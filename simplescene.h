#ifndef SIMPLESCENE_H
#define SIMPLESCENE_H

#include "scene.h"
#include "glslprogram.h"

#include <GL3/gl3w.h>

class SimpleScene : public Scene
{
private:
    int width, height;
    GLuint vboHandles[3];
    GLuint vaoHandle;
    GLSLProgram shader;
    int activeBuffer;

public:
    SimpleScene();

    void initScene();
    void update(float t);
    void render();
    void resize(int, int);
    void changeScene(int);
};

#endif
