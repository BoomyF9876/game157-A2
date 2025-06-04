#pragma once
#include <glew.h>
#include "Shader.h"
#include "Mesh.h"

class Skybox {
	GLuint textureID;
	Mesh* cubeMesh;
	Shader* skyboxShader;

	const char* posX; 
	const char* posY; 
	const char* posZ; 
	const char* negX; 
	const char* negY; 
	const char* negZ;

	public:
		Skybox(
			const char* posX_,
			const char* posY_,
			const char* posZ_,
			const char* negX_,
			const char* negY_,
			const char* negZ_
		);
		~Skybox();

		bool LoadImages();
		bool onCreate();
		inline GLuint getTextureID() const { return textureID; }
		inline Shader* getShader() const { return skyboxShader; }
		inline Mesh* getMesh() const { return cubeMesh; }
};