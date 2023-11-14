#include "Camera.h"

Camera::Camera()
{
	this->cameraTarget.init(0.0f, 0.0f, -1.0f);
	this->cameraPosition.init(0.0f, 0.0f, 15.0);
	this->cameraUp.init(0, 1, 0);
}

/*
This method updates the camera's position and target based on the provided
object position, viewing direction vector, and a camera distance. It effectively 
positions the camera to follow an object.*/

void Camera::UpdateCamera(Point3D objectPosition, Vector3D dir, float CameraDistance)
{

	dir.normalize();

	this->cameraPosition.x = objectPosition.x - dir.x;
	this->cameraPosition.y = objectPosition.y + CameraDistance;
	this->cameraPosition.z = objectPosition.z - dir.z;

	this->cameraTarget.x = objectPosition.x;
	this->cameraTarget.y = objectPosition.y;
	this->cameraTarget.z = objectPosition.z;
}

void Camera::setLookAt(GLfloat kWindowWidth, GLfloat kWindowHeight)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0f, (GLfloat)kWindowWidth / (GLfloat)kWindowHeight, 0.1f, 3000.0f);

	gluLookAt(this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z, this->cameraTarget.x, this->cameraTarget.y, this->cameraTarget.z, this->cameraUp.x, this->cameraUp.y, this->cameraUp.z);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}