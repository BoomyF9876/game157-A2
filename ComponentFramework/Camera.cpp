#include "Camera.h"

Camera::Camera() :
	pos(0.0f, 0.0f, -10.0f),
	orientation(1.0f, Vec3(0.0f, 0.0f, 0.0f)),
	skybox(nullptr)

{
	projection = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5f, 100.0f);
	skybox = new Skybox("textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg", "textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg");
	if (!skybox->LoadImages() || !skybox->onCreate()) {
		delete skybox;
		skybox = nullptr;
	}
}

Camera::~Camera() {
	delete skybox;
	skybox = nullptr;
}

void Camera::HandleEvents(const SDL_Event& sdlEvent) {
	trackball.HandleEvents(sdlEvent);
	trackball.getQuat(orientation);
}

void Camera::Render() const {
	if (skybox) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		Shader* shader = skybox->getShader();
		glUseProgram(shader->GetProgram());
		glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projection);
		glUniformMatrix4fv(shader->GetUniformID("orientationMatrix"), 1, GL_FALSE, MMath::toMatrix4(orientation));

		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());
		skybox->getMesh()->Render();
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glUseProgram(0);
	}
}