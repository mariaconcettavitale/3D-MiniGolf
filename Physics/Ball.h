#pragma once
#ifndef __Ball_h
#define __Ball_h
/**
 * @class Ball
 * @brief Represents a 3D ball with position, velocity, and acceleration properties.
 *
 * This class defines a 3D ball in space, which can be manipulated and rendered. It stores
 * information about the ball's position, velocity, acceleration, and its texture for rendering.
 * The class provides methods to initialize the ball, set its textures, update its position and
 * movement, apply friction, draw it, and update its rotation.
 *
 * @note The `Ball` class relies on the `Point3D` and `Vector3D` classes for handling positions,
 *       vectors, `TextureHandler` class for handling  and textures.
 */

#include "../Math/Point3D.h"
#include "../Math/Vector3D.h"
#include "../Textures&Models/TextureHandler.h"

class Ball {
private:
	Point3D newPosition;
	Point3D oldPosition;
	Vector3D velocity;
	Vector3D acceleration;
	TextureHandler ballTexture;

public:
	Ball() {};
	~Ball() {};

	void init(Point3D, Vector3D);
	void setAcceleration(Vector3D);
	void setYAcceleration(float);
	bool isEqualToOld();
	Point3D getPosition();
	void setVelocity(Vector3D);
	void decreaseVelocity(float);
	void updateVelocity(float);
	Vector3D getVelocity();
	void setY(float);


	void move(float t);
	void applyFriction(void);
	void draw(float, float, float);
	void updateBallRotation();
	void updateReflection(Vector3D);
};

#endif
