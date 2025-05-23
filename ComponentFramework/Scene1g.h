#ifndef SCENE1G_H
#define SCENE1G_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;
class Camera;

class Scene1g : public Scene {
private:
	Camera* camera;
	Body* mario;
	Shader* shader;
	Mesh* earthMesh;
	Mesh* skullMesh;

	Texture* earthTexture;
	Texture* skullTexture;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

	Matrix4 earthModelMatrix;
	Matrix4 skullModelMatrix;

	bool drawInWireMode;
	Vec3 lightPos;

public:
	explicit Scene1g();
	virtual ~Scene1g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE1G_H