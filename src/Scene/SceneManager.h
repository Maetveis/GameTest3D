#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <Game/GameComponent.h>

#include <memory>
#include <stack>

struct Scene;

class SceneManager :
	public GameComponent
{
public:
	void PushScene(std::unique_ptr<Scene> ptr);
	void PopScene();
	bool ChangeScene(std::unique_ptr<Scene> ptr);
	Scene* currentScene() const;

	Scene* operator->() const;

	~SceneManager();
protected:
private:
	std::stack< std::unique_ptr<Scene> > sceneStack;
};

#endif //SCENE_MANAGER_H
