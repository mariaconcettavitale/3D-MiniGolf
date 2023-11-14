#pragma once
#ifndef __MenuManager_h
#define __MenuManager_h
/**
 * @class MenuManager
 * @brief Manages menus, user profiles, and game settings.
 *
 * This class serves as a manager for menus, user profiles, and various game settings.
 * It includes properties for active users, user history, menus, textures, and game parameters.
 * The class handles menu initialization, animation, rendering, user selection, high scores, and game progress.
 *
 * @note The `MenuManager` class plays a key role in managing user interaction and game settings.
 */

#include "../Textures&Models/TextureHandler.h"
#include "../Level/UserProfile.h"
#include "Menu.h"
#include "../Math/Point3D.h"
#include "../Libraries.h"

class MenuManager
{
private:
	GLfloat width, height;
	bool isActive;
	float currentTime, lastFrame, deltaTime;
	int usersIndex;
	int powerBall;
	UserProfile activeUser;
	vector<UserProfile> history;
	map<int, Menu> menu;
	TextureHandler obj;
	int selectedMenu;
	int indexTexture;
	int parLevel;
	int userScore;
	bool loadGameUser;
	int totalUserScore;

public:

	MenuManager() { 
		this->userScore = 0.0f;
		this->totalUserScore = 0.0f;
		this->selectedMenu = 0;
		this->loadGameUser = false; 
		this->currentTime = 0.0f;
		this->lastFrame = 0.0f;
		this->deltaTime = 0.0f;
		this->indexTexture = -1.0f;
		this->powerBall= 1; //default value
	};
	~MenuManager() {};

	void init();
	void initAnimation(GLfloat,GLfloat);
	void initLoadGame(vector<string>);
	void initHighScore();
	bool getStateLoadGame();
	void drawActiveMenu(bool);
	void drawBarPower();
	void updatePower(int);
	void setSelectedMenu(int);
	int getPower();
	void resetPower();
	int checkButtons(float, float);
	bool getStateMenu();
	int getIndexMenu();

	string getUserActive();
	//load the file that saved previously and insert into menu
	void loadHighScores(const char*);
	void saveHighScores();

	void drawArrow(Point3D, float, map<int, Point3D>);
	void getYArrow(Point3D, map<int, Point3D>, float*);

	void incrementStroke();

	void resetScore(bool, bool);
	void setParLevel(int);

	void setInformationsUserToSave(string, string, float);
};

#endif