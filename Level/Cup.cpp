#include "Cup.h"

// Draw a Circle with radius = CUP_RADIUS in the x-z plane
void Cup::draw(int triangleCount)
{
	glEnable(GL_LIGHTING);
	float materialColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < triangleCount; i++)
		{
			float theta = PI2 * float(i) / float(triangleCount);

			float deltax = CUP_RADIUS * cosf(theta);
			float deltaz = CUP_RADIUS * sinf(theta);

			glVertex3f(vertex.x + deltax, vertex.y + (0.01f * normal.y), vertex.z + deltaz);
		}
		glNormal3f(normal.x, normal.y, normal.z);
	glEnd();
	glDisable(GL_LIGHTING);

}
