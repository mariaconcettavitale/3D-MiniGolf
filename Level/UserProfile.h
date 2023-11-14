#pragma once
#ifndef __UserProfile_h
#define __UserProfile_h
/**
 * @class UserProfile
 * @brief Represents a user profile with associated information.
 *
 * This class defines a user profile with properties for the user's name, score, strokes, and
 * the file path for storing user data. It includes methods for saving user information, scores,
 * and strokes, as well as retrieving and managing user data.
 *
 * @note The `UserProfile` class is essential for managing user profiles and associated data.
 */

#include "../Libraries.h"

class UserProfile
{
private:
	string userName;
	float score;
	string stroke;
	string filepath;

public:
	UserProfile() {
		userName = '\0'; filepath = "../MiniGolf3D/Scores/high_scores.txt";
	};
	~UserProfile() {};
	void saveUser(string);
	void saveScore(float);
	float getScore();
	void saveStroke(string);
	void saveToFile();

	void getInformation(string*, float*, string*);
	void getUserName(string*);

};

#endif
