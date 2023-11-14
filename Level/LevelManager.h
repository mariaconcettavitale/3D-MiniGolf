#pragma once
#ifndef __LevelManager_h
#define __LevelManager_h

/**
 * @class LevelManager
 * @brief Manages the game's levels, user input, and gameplay flow.
 *
 * This class serves as a manager for the game. It handles various aspects of the game,
 * including user input, level updates, ball movement, collision resolution, and loading levels
 * from a file. The class integrates components like levels, balls, cameras, skyboxes, menus, and models
 * to bring the game together.
 *
 * @note The `LevelManager` class plays a central role in orchestrating the game's functionality.
 */

#include "../Physics/Ball.h"
#include "../Physics/Camera.h"
#include "../Textures&Models/CubeMap.h"
#include "../Menu/MenuManager.h"
#include "../Textures&Models/ModelLoader.h"
#include "../Textures&Models/TextureHandler.h"
#include "../Math/Plane.h"
#include "../Math/Vector3D.h"
#include "Level.h"

class LevelManager
{
private:
	string courseName;
	int numberOfLevels;
	int currentLevel;
	int ballOnTileID;
	float theta_aroundY;
	int activedMenu;
	bool setFlag;

public:

	Ball ball;
	Camera camera;
	CubeMap sky;
	MenuManager menu;
	ModelLoader model;
	vector<Level> levels;

	LevelManager() { setFlag = false; };
	~LevelManager() {};

	void setTheta(float);
	
	void updateTheta(float);
	float getTheta();
	void readLevelsFromFile(const char* );
	void resetToLevel(int );
	void drawCurrentLevel(bool);
	void updateCurrentLevel(float);
	void resolveCollisions(float);
	void drawFlag(string, Point3D);
	void setBallAcceleration();
	Vector3D getDirection(int);
	
};

#endif