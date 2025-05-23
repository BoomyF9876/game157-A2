#include "Camera.h"

Camera::Camera() :
	pos(0.0f, 0.0f, -10.0f),
	orientation(1.0f, Vec3(0.0f, 0.0f, 0.0f))

{
	projection = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5f, 100.0f);


}

Camera::~Camera() {}
