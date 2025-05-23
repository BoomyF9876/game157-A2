#ifndef SCENE2G_H
#define SCENE2G_H
#include "Scene.h"
#include <Vector.h>
#include <Matrix.h>
#include "Trackball.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Body;
class Mesh;
class Shader;
class Texture;
class Camera;

class Scene2g : public Scene {
private:
	Trackball trackball;
	Camera* camera;
	Body* mario;
	Shader* shader;;
	Mesh* skullMesh;
	Mesh* eyeMesh;

	Texture* eyeTexture;
	Texture* skullTexture;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

	Matrix4 lEyeModelMatrix;
	Matrix4 rEyeModelMatrix;
	Matrix4 skullModelMatrix;

	bool drawInWireMode;
	Vec3 lightPos;

public:
	explicit Scene2g();
	virtual ~Scene2g();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE2G_H#pragma once
