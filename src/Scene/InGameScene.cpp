#include "InGameScene.h"

#include <Game/Game.h>

#include <Render/Model/ModelLoader.hpp>
#include <Render/ProgramInterface/ProgramInterface.hpp>

#include <Render/Model/AssimpImportFile.hpp>

#include <Render/Material/ColorFormat.hpp>
#include <Render/Material/LoadTexture.hpp>
#include <Render/Material/Param/Texture2DParam.hpp>

#include <Library/GL/Texture/Texture2D.hpp>
#include <Library/GL/UniformBinding.hpp>


#include <Library/Logger/Logger.hpp>

#include <Library/IO/BinaryFileWriter.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include <cmath>

bool InGameScene::Begin()
{
    if (!LoadShaders()) {
        Logger::Error() << "Failed to load Shaders" << '\n';
        return false;
    }

    if (!LoadData()) {
        Logger::Error() << "Loading data failed" << '\n';
        return false;
    }

    Logger::Info() << "RenderManager.Init() finished succesfully" << '\n'; //std::endl;

    return true;
}

bool InGameScene::LoadData()
{
    GL::Program program0;
    program0.VsFsProgram("../shaders/project.glsl", "../shaders/albedo.glsl");
    auto programId = store.AddProgram(Render::ProgramInterface(std::move(program0)));

    Render::Material material0(programId);

    GL::Texture2D texture;
    Render::LoadImageDataFile("../assets/Textures/rock.jpg", texture);
    texture.SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    texture.SetMagFilter(GL_LINEAR);
    texture.GenerateMipmap();
    Logger::Info() << "GL_MAX_TEXTURE_MAX_ANISOTROPY: " << GL::Texture::GetMaxAnisotropy() << '\n';
    texture.SetAnisotropy(16.0);
    material0.AddParam(std::make_unique<Render::Texture2DParam>("diffuseText", *store.GetProgram(0), std::move(texture)));

    store.AddMaterial(std::move(material0));

    IO::BinaryFileReader reader("../assets/alfa.bin");
    Render::ProtoModel protoModel = Render::AssimpImportFile("../assets/t-34.obj");
    //reader >> protoModel;

    auto modelID = store.UploadModel(protoModel);

    scene.AddObject(Render::Object(modelID, glm::rotate(0.f, glm::vec3(1.f, 0.f, 0.f))));

    return true;
}

bool InGameScene::LoadShaders()
{
    scene.SetProj(glm::perspective(45.0f, 1000 / 1000.0f, 0.01f, 500.0f));
    //scene.SetView(glm::lookAt(glm::vec3(0.f, 1.f, 6.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    scene.AddLight(Render::Light(glm::vec3(0.f, 0.f, -20.f), glm::vec3(.8f, 0.f, 0.f), 10.f));
    scene.AddLight(Render::Light(glm::vec3(30.f, 0.f, 0.f), glm::vec3(0.f, .8f, 0.f), 10.f));
    scene.AddLight(Render::Light(glm::vec3(-10.f, 10.f, 10.f), glm::vec3(0.f, 0.f, .8f), 5.f));
    scene.AddLight(Render::Light(glm::vec3(0.f, -20.f, 20.f), glm::vec3(.8f, 0.8f, .8f), 20.f));

    return true;
}

static double Time = 0;

void InGameScene::Update(double deltaTime)
{
    Time += deltaTime;

	cameraControls.Update(scene.GetCamera(), deltaTime);
    //scene.SetView(glm::lookAt(glm::vec3(10.f * glm::sin(Time), 4.f, 10.f * glm::cos(Time)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
}

void InGameScene::End()
{
}

void InGameScene::Pause()
{
}

void InGameScene::PrepareRender()
{
}

void InGameScene::Render()
{
    renderer.Render();
}

void InGameScene::OnQuit(SDL_QuitEvent& event)
{
    Quit();
}

void InGameScene::OnWindow(SDL_WindowEvent& event)
{
    switch (event.event) {
    case SDL_WINDOWEVENT_RESIZED:
        renderer.ResizeViewPort(event.data1, event.data2);
        scene.SetProj(glm::perspective(45.0f, event.data1 / static_cast<float>(event.data2), 0.01f, 500.0f));
    default:
        break;
    }
}

void InGameScene::Quit()
{
    Logger::Debug() << "Exit" << '\n';
    game->running = false;
}

void InGameScene::OnKeyboard(SDL_KeyboardEvent& event)
{
	if(event.state == SDL_PRESSED)
	{
		switch (event.keysym.sym) {
		case SDLK_ESCAPE:
		    Quit();
		    break;
		case 'w':
		case 'a':
		case 's':
		case 'd':
			cameraControls.OnKeyPressed(event.keysym.sym);
			break;
		default:
		    Logger::Debug() << "Pressed key with code: " << event.keysym.sym << '\n';
		    break;
		}
	} else {
		switch (event.keysym.sym) {
		case 'w':
		case 'a':
		case 's':
		case 'd':
			cameraControls.OnKeyReleased(event.keysym.sym);
			break;
		}
	}
}

void InGameScene::OnMouseMotion(SDL_MouseMotionEvent& event)
{
	cameraControls.OnMouseMove(event.xrel, event.yrel, event.state == SDL_PRESSED);
}

void InGameScene::OnMouseButton(SDL_MouseButtonEvent& event)
{
}
