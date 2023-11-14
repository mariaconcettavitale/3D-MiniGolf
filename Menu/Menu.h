#pragma once
#ifndef __Menu_h
#define __Menu_h

/**
 * @class Menu
 * @brief Represents an interactive menu for the mini-golf game.
 *
 * This class defines an interactive menu used in the mini-golf game. It includes properties
 * for buttons, textures, and user interface elements. The class manages button selection,
 * and user interaction within the game's menus.
 *
 * @note The `Menu` class plays a key role in the user interface of the mini-golf game.
 */

#include "../Textures&Models/TextureHandler.h"
#include "../Libraries.h"

struct Point2D
{
	float x, y; //bottom left corner 
	string text_menu; 
};

class Menu
{

private:
	string nameActiveUser;
	vector<Point2D> buttons;
	TextureHandler obj;
	int numberButtons;
	int selectedMenu;
	bool animationHandle;
	bool updateFPS;
	bool isActive;
	int indexTexture;
	int userIndex;
	int sizeUsers;
	string usersName[5] = { "HoleInOneHero", "FairwayFun", "Parfectionist", "HoleHunter", "GreenGrassGolfer" };

public:

	Menu() { this->isActive = true;
	this->animationHandle = true; 
	this->userIndex = -1;
	this->updateFPS = false;
	this->indexTexture = 0;
	// Calculate the number of elements in the array
	this->sizeUsers = sizeof(this->usersName) / sizeof(this->usersName[0]);

	};
	~Menu() {};

	void initAnimation(int, Point2D[2]);
	void init(int, vector<Point2D>, bool);
	void resetUserId();
	string getUsersPossibility();
	void Draw(int, bool, int*, float*);
	int CheckButtons(float, float, int);
	int getSizeButtons();
	void setIndexTexture(float);
	void setFPState(bool);
	void setStateMenu(bool);
	bool getStateMenu();
	void rearrangeButtons(GLfloat, GLfloat);
	void getUserName(string*);
};

#endif
