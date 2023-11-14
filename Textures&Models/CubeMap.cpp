#include "../Libraries.h"
#include "CubeMap.h"

/*
* This method is responsible for setting up the rendering environment for the cube map.
It clears the color and depth buffers, sets the clear color to black,and specifies
the path for loading and set the texture files for the cube map by the 'obj' TextureHandler object.
*/
void CubeMap::setParameters(int idSelectedMenu)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	this->obj.loadSkyBox();
	//doesn't draw the front face of cubemap because we are always inside the cube!
	//if(idSelectedMenu!=0)
	//	glCullFace(GL_FRONT);
}

/*
* This method is used for rendering the cube map.
* For each face of the cube (right, left, top, bottom, front, back), it binds the corresponding texture and uses OpenGL 
* to render each side of the cube.
*Each face is defined using a series of vertices and texture coordinates.
*/
void CubeMap::Draw()
{
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
	float materialColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

	//right
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[0].getTextureId());
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, 1000.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, -2000.0f);
	glEnd();


	//left
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[1].getTextureId());
	glBegin(GL_TRIANGLES);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, -2000.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glEnd();

	//top
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[2].getTextureId());
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, 1000.0f, -2000.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, 1000.0f);
	glEnd();

	//bottom
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[3].getTextureId());
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, -2000.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, -1000.0f, -2000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glEnd();


	//front
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[4].getTextureId());
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000.0f, -1000.0f, 1000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, 1000.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, 1000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, 1000.0f);
	glEnd();

	//back
	glBindTexture(GL_TEXTURE_2D, this->obj.textures[5].getTextureId());
	glBegin(GL_TRIANGLES);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, -2000.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000.0f, -1000.f, -2000.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, -2000.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1000.0f, 1000.0f, -2000.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1000.0f, -1000.0f, -2000.0f);
	glEnd();


	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
}





