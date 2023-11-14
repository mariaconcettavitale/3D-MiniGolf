#include "../Libraries.h"
#include "UserProfile.h"

void UserProfile::saveToFile()
{
    // Open the file for writing (clearing the existing content)
    std::ofstream file(this->filepath, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << this->filepath << std::endl;
        return;
    }

    // Write the new high score to the file for current user
    file << "begin_user" << endl;
    file << "username " << this->userName << endl;
    file << "score " << this->score << endl;
    file << "stroke " << this->stroke << endl;
    file << "end_user" << endl;

    // Close the file
    file.close();
}

void UserProfile::saveUser(string name)
{
    this->userName = name;

}

void UserProfile::saveScore(float score)
{
    this->score = score;
}

float UserProfile::getScore()
{
    return this->score;
}
void UserProfile::saveStroke(string stroke)
{
    this->stroke = stroke;

}

void UserProfile::getInformation(string* name, float* score, string* stroke)
{
    *name = this->userName;
    *score = this->score;
    *stroke = this->stroke;
}

void UserProfile::getUserName(string* name)
{
    *name = this->userName;
}