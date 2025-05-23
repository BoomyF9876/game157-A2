#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <MMath.h>
#include "Scene1g.h"
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"
#include "Camera.h"

Scene1g::Scene1g() : mario(nullptr), shader(nullptr), earthMesh(nullptr),
drawInWireMode(false), earthTexture(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene1g::~Scene1g() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene1g::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	camera = new Camera();
	mario = new Body();
	mario->OnCreate();
	lightPos = Vec3(10.0f, 0.0f, 0.0f);

	earthMesh = new Mesh("meshes/Sphere.obj");
	earthMesh->OnCreate();

	skullMesh = new Mesh("meshes/Skull.obj");
	skullMesh->OnCreate();

	earthTexture = new Texture();
	earthTexture->LoadImage("textures/earthclouds.jpg");

	skullTexture = new Texture();
	skullTexture->LoadImage("textures/skull_texture.jpg");

	shader = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("view matrix");
	earthModelMatrix = MMath::toMatrix4(Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0)));
	skullModelMatrix = MMath::toMatrix4(Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0)));

	return true;
}

void Scene1g::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	mario->OnDestroy();
	delete mario;

	earthMesh->OnDestroy();
	delete earthMesh;

	shader->OnDestroy();
	delete shader;

	delete camera;
}

void Scene1g::HandleEvents(const SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.scancode) {
		case SDL_SCANCODE_W:
			drawInWireMode = !drawInWireMode;
			break;
		}
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Scene1g::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	earthModelMatrix =

		MMath::rotate(totalTime * 10.0f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

	skullModelMatrix =
		MMath::rotate(totalTime * 20.0f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::translate(Vec3(4.0f, 0.0f, 0.0f)) *
		//MMath::rotate(-90.0f,Vec3(0.0f,1.0f,0.0f)) *
		MMath::scale(0.25f, 0.25, 0.25f);
}

void Scene1g::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (drawInWireMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);


	glBindTexture(GL_TEXTURE_2D, skullTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skullModelMatrix);
	skullMesh->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, earthTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, earthModelMatrix);
	earthMesh->Render(GL_TRIANGLES);


	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}




