#include "Ball.h"

static float displacement(float u, float a, float t);
static GLfloat t = 0.0; // Time parameter.

// Initialize the Ball at a given vertex, as per a Ball radius, along a specified normal
void Ball::init(Point3D vertex, Vector3D normal)
{
	memset(this, 0, sizeof(Ball));
	velocity.Zero();
	acceleration.Zero();
	newPosition.init(vertex.x + (BALL_RADIUS * normal.x), vertex.y + (BALL_RADIUS * normal.y), vertex.z + (BALL_RADIUS * normal.z));

	oldPosition = newPosition;

	this->ballTexture.setPath("../MiniGolf3D/textures/golfball.jpg");
	this->ballTexture.loadTextures(false); 
}

bool Ball::isEqualToOld()
{
	if (newPosition.isEqual(oldPosition))
		return true;
	else
		return false;

}

Point3D Ball::getPosition()
{
	return newPosition;
}
Vector3D Ball::getVelocity()
{
	return velocity;
}

void Ball::setVelocity(Vector3D vel)
{
	velocity.init(vel.x,vel.y,vel.z);
}

void Ball::updateVelocity(float t)
{
	velocity.x += (acceleration.x *t) ;
	velocity.y += (acceleration.y * t);
	velocity.z += (acceleration.z * t);

}

void Ball::updateReflection(Vector3D normals)
{
	acceleration.getReflectionVector(normals);
	velocity.getReflectionVector(normals);
	
}

void Ball::setY(float yPos)
{
	newPosition.y = yPos;
}
// To set the acceleration of the ball to a specific vector
void Ball::setAcceleration(Vector3D vec)
{
	acceleration.init(vec.x, vec.y, vec.z);
}
void Ball::setYAcceleration(float y)
{
	acceleration.y = y;
}

// To move the ball for a time-slice 't'
// NOTE:	The ball sometimes gets stuck due to higher ticks returned by the 
//			clock when using a timer for render loop

void Ball::move(float t)

{
	acceleration.y += (GRAVITY);

	oldPosition.init(newPosition);

	newPosition.x += displacement(velocity.x, acceleration.x, t);
	newPosition.z += displacement(velocity.z, acceleration.z, t);
	newPosition.y += displacement(velocity.y, acceleration.y, t);
	

}

void Ball::decreaseVelocity(float v)
{
	velocity.y *= v;
}

//This method applies frictional forces to the movement of the ball by reducing its velocity and acceleration.


void Ball::applyFriction(void)
{
	velocity /= FRICTION;
	acceleration /= FRICTION;
}


// To draw the ball at its current position
void Ball::draw(float colorR, float colorG, float colorB)
{
	glEnable(GL_LIGHTING);

	float materialColor[] = { colorR, colorG, colorB, 0.7f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
	float materialAmbient[] = { 0.5, 0.5, 0.5, 0.7f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->ballTexture.textures[0].getTextureId());
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();
		glTranslatef(newPosition.x, newPosition.y, newPosition.z);
		updateBallRotation();
		glutSolidSphere(BALL_RADIUS, 50, 50);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);


}


void Ball::updateBallRotation() {

	//rotate the ball along x-axis to simulate a real rotation in the x-z plane
	float rotationAxis[3] = { 1.0f, 0.0f, 0.0f };
	//calculate the angular velocity(rotation rate) along the x-z plane
	float rotationAngle = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z) / BALL_RADIUS;
	//convert rotationg angle from float to degree 
	glRotatef(rotationAngle * 180.0f / M_PI, rotationAxis[0], rotationAxis[1], rotationAxis[2]);
}

static float displacement(float u, float a, float t)
{
	return ((u * t) + (a * t * t / 2));
}