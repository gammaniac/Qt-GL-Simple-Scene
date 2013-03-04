#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    // Loading of textures, initialize shaders, etc.
    virtual void initScene() = 0;

    // Updates every frame
    virtual void update( float t ) = 0;

    // Draw function
    virtual void render() = 0;

    // Resize window
    virtual void resize(int, int) = 0;

    // Change scene
    virtual void changeScene(int) = 0;
};

#endif // SCENE_H
