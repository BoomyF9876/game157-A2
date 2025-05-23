#include <glew.h>
#include <iostream>
#include <SDL.h>
#include <MMath.h>
#include "Scene2g.h"
#include "Debug.h"
#include "Mesh.h"
#include "Shader.h"
#include "Body.h"
#include "Texture.h"
#include "Camera.h"

Scene2g::Scene2g() : mario(nullptr), shader(nullptr), eyeMesh(nullptr),
drawInWireMode(false), eyeTexture(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene2g::~Scene2g() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene2g::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	camera = new Camera();
	mario = new Body();
	mario->OnCreate();
	lightPos = Vec3(10.0f, 0.0f, 0.0f);

	eyeMesh = new Mesh("meshes/Sphere.obj");
	eyeMesh->OnCreate();

	skullMesh = new Mesh("meshes/Skull.obj");
	skullMesh->OnCreate();

	eyeTexture = new Texture();
	eyeTexture->LoadImage("textures/evilEye.jpg");

	skullTexture = new Texture();
	skullTexture->LoadImage("textures/skull_texture.jpg");

	shader = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (shader->OnCreate() == false) {
		std::cout << "Shader failed ... we have a problem\n";
	}

	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 5.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print("view matrix");
	rEyeModelMatrix = MMath::toMatrix4(Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0)));
	lEyeModelMatrix = MMath::toMatrix4(Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0)));
	skullModelMatrix = MMath::toMatrix4(Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0)));

	return true;
}

void Scene2g::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	mario->OnDestroy();
	delete mario;

	delete camera;

	eyeMesh->OnDestroy();
	delete eyeMesh;

	shader->OnDestroy();
	delete shader;


}

void Scene2g::HandleEvents(const SDL_Event& sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	skullModelMatrix = MMath::toMatrix4(trackball.getQuat());

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

void Scene2g::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;
	lEyeModelMatrix =
		MMath::translate(0.55f, 0.25f, 1.0f) *
		MMath::rotate(-90.f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(0.35f, 0.35f, 0.35f);
	rEyeModelMatrix =
		MMath::translate(-0.55f, 0.25f, 1.0f) *
		MMath::rotate(-90.f, Vec3(0.0f, 1.0f, 0.0f)) *
		MMath::scale(0.35f, 0.35f, 0.35f);
	
}

void Scene2g::Render() const {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Set the background color then clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (drawInWireMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	glBindTexture(GL_TEXTURE_2D, skullTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skullModelMatrix);
	skullMesh->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, eyeTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skullModelMatrix * lEyeModelMatrix);
	eyeMesh->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, eyeTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skullModelMatrix * rEyeModelMatrix);
	eyeMesh->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}




