#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
class SceneManager  {
public:
	
	SceneManager();
	~SceneManager();
	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void HandleEvents();
	
	
private:
	enum class SCENE_NUMBER {
		SCENE0g = 0,
		SCENE0p,
		SCENE1g,
		SCENE2g,
		SCENE3g,
		SCENE4g,
		SCENE5g,
		SCENE6g
	};

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	bool BuildNewScene(SCENE_NUMBER scene_);
};


#endif // SCENEMANAGER_H