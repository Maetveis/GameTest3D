#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include "Scene.h"

#include "Render/Renderer/ObjectRenderer.hpp"
#include "Render/Renderer/RenderStore.hpp"
#include "Render/Scene/Scene.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class InGameScene : public Scene {
public:
    InGameScene()
        : scene()
        , store(10000000, 10000000)
        , renderer(scene, store)
    {
    }

    virtual bool Begin();

    virtual void End();

    virtual void Pause();

    virtual void PrepareRender();
    virtual void Render();

    virtual void Update(double);

    virtual void OnKeyboard(SDL_KeyboardEvent& event);

    virtual void OnWindow(SDL_WindowEvent& event);

    virtual void OnQuit(SDL_QuitEvent& event);

    void Quit();

protected:
private:
    bool LoadData();
    bool LoadShaders();

    Render::Scene scene;
    Render::RenderStore store;
    Render::ObjectRenderer renderer;
};

#endif //IN_GAME_SCENE_H
