#include "Tile.h"

//initialize the specific tile with texture.
Tile::Tile()
{
	this->textureobj.setPath("../MiniGolf3D/textures/ground.png");
	this->textureobj.loadTextures(false);
}

void Tile::draw(float colorR, float colorG, float colorB)
{
	// Render Tile Logic
	glEnable(GL_LIGHTING);
	float materialColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
	float ambientColor[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientColor);

	float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureobj.textures[0].getTextureId());

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

	float s[] = { 1.0, 0.0, 0.0, 0.0 };
	float t[] = { 0.0, 0.0, 1.0, 0.0 };
	glTexGenfv(GL_S, GL_OBJECT_PLANE, s);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, t);

	glBegin(GL_TRIANGLES);

	if (this->vertices.size() >= 3) {
		auto it = this->vertices.begin();
		Point3D first = it->second;
		Point3D second;
		++it;
		Point3D third = it->second;

		while (++it != this->vertices.end()) {
			second = third;
			third = it->second;

			glVertex3f(first.x, first.y, first.z);
			glVertex3f(second.x, second.y, second.z);
			glVertex3f(third.x, third.y, third.z);
		}
		glNormal3f(normal.x, normal.y, normal.z);

	}

	glEnd();


	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}


//method that computes for each tile the edge normals that will be used to resolve the collision beetween ball and each tile.
void Tile::initCollisionDetectionEdges(void)
{
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		edges[i].init(this->vertices[i], this->vertices[(i + 1) % this->numberOfVertices]);
		
		edges[i].CrossProduct(this->normal, &edgeNormals[i]);
		
		edgeNormals[i].Reverse();
		edgeNormals[i].Normalize();

		
	}
}


void Tile::setTileType(string type)
{
	this->tileType = type;
}

string Tile::getTileType()
{
	return this->tileType;
}

void Tile::setTileID(int id)
{
	this->tileID = id;

}

int Tile::getTileId()
{
	return tileID;
}

void Tile::setNumberOfVertices(int nVertices)
{
	this->numberOfVertices = nVertices;
}

int Tile::getNumberOfVertices()
{
	return this->numberOfVertices;
}

Vector3D Tile::getNormal()
{
	return this->normal;
}

void Tile::updateNormal(Vector3D newNormal)
{
	this->normal.x += newNormal.x;
	this->normal.y += newNormal.y;
	this->normal.z += newNormal.z;

}

void Tile::normalizeNorm()
{
	this->normal.Normalize();
}

void Tile::setNormal(Vector3D normal)
{
	this->normal = normal;
}
