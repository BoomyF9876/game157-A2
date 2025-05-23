#pragma once
#include "Vector.h"
#include "MMath.h"
#include "QMath.h"

using namespace MATH;

class Camera {
private:
	Vec3 pos;
	Quaternion orientation;
	Matrix4 projection;
public:
	Camera();
	~Camera();
	Matrix4 getProjectionMatrix() const { return projection; }

	Matrix4 getViewMatrix() const { return MMath::translate(pos) * MMath::toMatrix4(orientation); }

	void setPos(Vec3 pos_) { pos = -pos_; }
};

