#pragma once
#ifndef __Camera_h
#define __Camera_h

/**
 * @class Camera
 * @brief Represents a 3D camera for viewing a 3D scene.
 *
 * This class defines a 3D camera with properties for its position, target, and orientation.
 * The camera is used to view a 3D scene and provides methods for updating its position,
 * orientation, and parameters. It allows for setting the camera's view direction, perspective,
 * and other rendering-related settings.
 */


#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"


class Camera {
private:
	Vector3D cameraTarget;
	Vector3D cameraPosition;
	Vector3D cameraUp;
public:
	

	Camera();
	~Camera() {};

	void UpdateCamera(Point3D objectPosition, Vector3D dir, float CameraDistance);
	void setLookAt(GLfloat, GLfloat);
};

#endif