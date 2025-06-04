#include "Skybox.h"
#include <SDL_image.h>


Skybox::Skybox(
    const char* posX_,
    const char* posY_,
    const char* posZ_,
    const char* negX_,
    const char* negY_,
    const char* negZ_
) {
    posX = posX_;
    posY = posY_;
    posZ = posZ_;

    negX = negX_;
    negY = negY_;
    negZ = negZ_;
}

Skybox::~Skybox() {
    glDeleteTextures(1, &textureID);
}

bool Skybox::LoadImages() {
    SDL_Surface* textureSurface;
    int mode;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    textureSurface = IMG_Load(posX);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);

    textureSurface = IMG_Load(posY);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);

    textureSurface = IMG_Load(posZ);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);
    
    textureSurface = IMG_Load(negX);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);
    
    textureSurface = IMG_Load(negY);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);
    
    textureSurface = IMG_Load(negZ);
	if (textureSurface == nullptr) {
		return false;
	}
    mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
    SDL_FreeSurface(textureSurface);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return true;
}

bool Skybox::onCreate() {
    cubeMesh = new Mesh("meshes/Cube.obj");
    skyboxShader = new Shader("shaders/skyboxVert.glsl", "shaders/skyboxFrag.glsl");
    return cubeMesh->OnCreate() && skyboxShader->OnCreate();
}