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

    virtual bool Begin() override;

    virtual void End() override;

    virtual void Pause() override;

    virtual void PrepareRender() override;
    virtual void Render() override;

    virtual void Update(double) override;

    virtual void OnKeyboard(SDL_KeyboardEvent& event) override;

	virtual void OnMouseMotion(SDL_MouseMotionEvent&) override;
	virtual void OnMouseButton(SDL_MouseButtonEvent&) override;

    virtual void OnWindow(SDL_WindowEvent& event) override;

    virtual void OnQuit(SDL_QuitEvent& event) override;

    void Quit();

protected:
private:
    bool LoadData();
    bool LoadShaders();

    Render::Scene scene;
    Render::RenderStore store;
    Render::ObjectRenderer renderer;
	Render::CameraControls cameraControls;
};

#endif //IN_GAME_SCENE_H
