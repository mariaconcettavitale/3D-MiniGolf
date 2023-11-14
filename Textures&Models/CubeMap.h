#pragma once
#ifndef __CubeMap_h
#define __CubeMap_h

/**
 * @class CubeMap
 * @brief Represents a cube map (skybox) used for rendering environments.
 *
 * This class is designed to handle cube maps, which are used for rendering
 * 3D environments, especially for simulating background scenery.
 * It contains methods to set cube map parameters and draw the cube map.
 */

#include "TextureHandler.h"

class CubeMap
{
public:

	
	CubeMap() {};
	~CubeMap() {};

	TextureHandler obj;
	void setParameters(int);
	void Draw();

};

#endif