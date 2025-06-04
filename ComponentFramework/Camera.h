#pragma once
#include "Vector.h"
#include "MMath.h"
#include "QMath.h"
#include "Skybox.h"
#include "SDL_events.h"
#include "Trackball.h"

using namespace MATH;

class Camera {
private:
	Vec3 pos;
	Quaternion orientation;
	Matrix4 projection;
	Skybox *skybox;
	Trackball trackball;
	
public:
	Camera();
	~Camera();
	void Render() const;

	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return MMath::translate(pos) * MMath::toMatrix4(orientation); }

	inline Vec3 getPos() { return pos; }
	inline void setPos(Vec3 pos_) { pos = -pos_; }
	inline void setOrientation(Quaternion orientation_) { orientation = orientation_; }
	inline void HandleEvents(const SDL_Event& sdlEvent);
};

