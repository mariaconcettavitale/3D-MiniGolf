#include "MenuManager.h"

void MenuManager::initAnimation(GLfloat width, GLfloat height)
{
    vector<Point2D> tempAnimation;
    float startX = (float)(width / 2) - (BUTTON_OFFSET_WIDTH / 2);
    float startY =  ((BUTTON_OFFSET_HEIGHT + 40) / 2) - 10.0f;

    this->width = width;
    this->height = height;

    Point2D animationButtons[2] = { 0.0f,0.0f,"", startX,startY, "Press [SPACE BAR] to start" };

    for (int i = 0; i < 2; i++)
        tempAnimation.push_back(animationButtons[i]);

    this->menu[0].init(2, tempAnimation, true);
    this->menu[0].setStateMenu(true);


}

void MenuManager::init()
{
    vector<Point2D> temp;
    Point2D startingMenu[5] = { 200.0f,600.0f,"START",200.0f,510.0f,"LOAD GAME",200.0f, 420.0f, "HIGH SCORES",200.0f,330.0f,"EXIT", 200.0f,200.0f,"CHOOSE USER NAME" };


    for (int i = 0; i < 5; i++)
        temp.push_back(startingMenu[i]);

    this->menu[1].init(5, temp, false);
    this->menu[1].rearrangeButtons(this->width, this->height);

    this->menu[1].setStateMenu(true);
    this->usersIndex = -1;

    vector<Point2D> temp1;
    Point2D tempPauseMenu[3] = { 200.0f,600.0f,"RESUME GAME",200.0f,510.0f,"BACK TO MENU ",200.0f, 420.0f, "EXIT GAME" };

    for (int i = 0; i < 3; i++)
        temp1.push_back(tempPauseMenu[i]);

    this->menu[2].init(3, temp1, false);
    this->menu[2].rearrangeButtons(this->width, this->height);

    this->menu[2].setStateMenu(true);
    this->usersIndex = -1;



}


void MenuManager::initLoadGame(vector<string>names)
{
    vector<Point2D> temp_menu1;
    int i;
    //this boolean flag became true when the user choose to load a precisely level from the menu 
    this->loadGameUser = false;

    for (i = 0; i < names.size(); i++)
    {
        Point2D p = { 200.0f , static_cast<float>(this->height) - (i + 1) * 40, names[i] };
        temp_menu1.push_back(p);
    }

    temp_menu1.push_back({ 200.0f,static_cast<float>(this->height) - (i + 1) * 40, "BACK TO MENU" });
    this->menu[3].init(names.size() + 1, temp_menu1, false);
    this->menu[3].rearrangeButtons(this->width, this->height);
    this->menu[3].setStateMenu(true);
}

void MenuManager::initHighScore()
{
    vector<Point2D> temp_menu2;

    float score;
    int i;
    string name, stroke;

    this->loadHighScores("../MiniGolf3D/Scores/high_scores.txt");

   
    // Create a vector of indices
    vector<size_t> indices(this->history.size());
    iota(indices.begin(), indices.end(), 0);

    // Sort the indices based on the score
    std::sort(indices.begin(), indices.end(), [this](size_t a, size_t b) {
        return this->history[a].getScore() < this->history[b].getScore();
        });

    
    // Rearrange your original data based on the sorted indices
    std::vector<UserProfile> sortedHistory(this->history.size());
    for (size_t i = 0; i < indices.size(); ++i) {
        sortedHistory[i] = this->history[indices[i]];
    }
    // Save only the first 9 elements
    size_t numToKeep = 9;
    if (sortedHistory.size() > numToKeep) {
        sortedHistory.erase(sortedHistory.begin() + numToKeep, sortedHistory.end());
    }

    // Replace your original data with the sorted data
    this->history = sortedHistory;
   

    for (i = 0; i < this->history.size(); i++)
    {
      
        
        history[i].getInformation(&name, &score, &stroke);
        
       
        // Calculate the vertical position for this row
        float yPos = static_cast<float>(this->height) - (i + 1) * 70.0f;

        Point2D buttonName = { 20.0f , yPos, name };
        temp_menu2.push_back(buttonName);
        
        string scoreString = to_string(score).substr(0, to_string(score).find(".") + 1 + 1);
        Point2D scoreButton = { 20.0f + BUTTON_OFFSET_WIDTH + 20.0f , yPos, scoreString};
     
        temp_menu2.push_back(scoreButton);

        Point2D levelButton = { 20.0f + 2 * BUTTON_OFFSET_WIDTH + 2 * 20.0f, yPos, stroke };
        temp_menu2.push_back(levelButton);


    }


    //center the exit button
    float totalButtonHeight = this->history.size() * 3 * (BUTTON_OFFSET_HEIGHT + 40);
    float startY = (float)(this->height / 2) + (totalButtonHeight / 2);

    temp_menu2.push_back({ (float)(this->width / 2) - (BUTTON_OFFSET_WIDTH / 2),10.0f, "BACK TO MENU" });


    this->menu[4].init(temp_menu2.size(), temp_menu2, false);
    this->menu[4].setStateMenu(true);

}

void MenuManager::drawActiveMenu(bool pressing)
{
    int index = this->selectedMenu;
    
    //if the animation is draw while the space bar is pressing
    if (index == 0 && pressing)
    {
        //increment the index to change and draw the menu options.
        index = index + 1;
        this->menu[index].setStateMenu(true);
        this->selectedMenu = 1;

    }

    int numTextures;

    if (this->menu[index].getStateMenu())
    {
        glutSetCursor(GLUT_CURSOR_INHERIT);

        this->menu[index].Draw(index, pressing, &numTextures, &this->lastFrame);
        if (numTextures == 132 && pressing==false)
        {
           
            //compute the currentTime
            this->currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f; //conversion in milliseconds
            this->deltaTime = this->currentTime - this->lastFrame;
         
            // if the time elapsed since the last texture binding is within the specific range reported, then restart the animation.
            if (deltaTime >= 9.0 and deltaTime <= 10.0)
            {
                this->menu[index].setIndexTexture(0.0f);
                this->menu[index].setFPState(false);
                deltaTime = 0.0f;

            }
        }



    }
    else
    {
        //draw bar power
        drawBarPower();
    }
}


//}

//Draw the bar power
void MenuManager::drawBarPower()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    float rectangleHeight = 10;
    Point2D topLeftRectangle = { -90, 90, "" };
    char text[] = "Press key up or down to select power and then 's' to set";

    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.75f, 0.75f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(topLeftRectangle.x, topLeftRectangle.y);
    glVertex2f(topLeftRectangle.x + this->powerBall, topLeftRectangle.y);
    glVertex2f(topLeftRectangle.x + this->powerBall, topLeftRectangle.y - rectangleHeight);
    glVertex2f(topLeftRectangle.x, topLeftRectangle.y - rectangleHeight);
    glEnd();
    glPopMatrix();


    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-95, -90);

    for (int j = 0; j < (int)sizeof(text); j++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[j]);
    glPopMatrix();



    glPushMatrix();
    glLoadIdentity();
    glTranslatef(40.0f, 90.0f, 0.0f);
    glScalef(0.02f, 0.02f, 0.02f);
    stringstream MessageConstructor;
    MessageConstructor << "Available par: ";
    MessageConstructor << this->parLevel;
    string outputMessage = MessageConstructor.str();
    int index = 0;
    glColor3f(0.75f, 0.75f, 1.0f);
    while (outputMessage[index++] != '\0')
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, outputMessage[index - 1]);
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(40.0f, 85.0f, 0.0f);
    glScalef(0.02f, 0.02f, 0.02f);

    string outputStroke;
    MessageConstructor.str("");
    MessageConstructor << "Stroke: ";
    int score = userScore - parLevel;
    switch (score)
    {
    case -4:
        //Condor: four strokes under par
        outputStroke = "Condor";
        MessageConstructor << "Condor";
        break;
    case -3:
        outputStroke = "Albatross";

        //Albatross: Three shots less than par
        MessageConstructor << "Albatross";
        break;
    case -2:
        // Eagle: Two shots less
        outputStroke = "Eagle";

        MessageConstructor << "Eagle";
        break;
    case -1:
        outputStroke = "Birdie";

        // Birdie: One shot less
        MessageConstructor << "Birdie";
        break;
    case 0:
        outputStroke = "Par";

        // Par: equal to par
        MessageConstructor << "Par";
        break;
    case 1:
        outputStroke = "Bogey";

        // Bogey: One shot more
        MessageConstructor << "Bogey";
        break;
    case 2:
        outputStroke = "Double Bogey";
        // Double bogey: Two shots more
        MessageConstructor << "Double Bogey";
        break;
    case 3:
        outputStroke = "Triple Bogey";
        // Triple bogey: Three shots more
        MessageConstructor << "Triple Bogey";
        break;
    case 4:
        outputStroke = "Quadruple Bogey";
        // Quadruple Bogey: four strokes over par
        MessageConstructor << "Quadruple Bogey";
        break;
    default:
        outputStroke = to_string(score);
      
        MessageConstructor << score;
        break;
    }
 
    outputMessage = MessageConstructor.str();
    index = 0;
    glColor3f(0.75f, 0.75f, 1.0f);
    while (outputMessage[index++] != '\0')
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, outputMessage[index - 1]);
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(40.0f, 77.0f, 0.0f);
    glScalef(0.03f, 0.03f, 0.03f);
    MessageConstructor.str("");
    MessageConstructor << "User:  ";
    MessageConstructor << getUserActive();
    string userActive = MessageConstructor.str();
    index = 0;
    glColor3f(0.75f, 0.75f, 1.0f);
    while (userActive[index++] != '\0')
        glutStrokeCharacter(GLUT_STROKE_ROMAN, userActive[index - 1]);
    glPopMatrix();


    glPopMatrix();
   

    setInformationsUserToSave(getUserActive(), outputStroke, this->totalUserScore);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_LIGHTING);


}

//save user's information to save the actual score of the user 
void MenuManager::setInformationsUserToSave(string userName, string stroke, float score)
{
    this->activeUser.saveUser(userName);
    this->activeUser.saveScore(score);
    this->activeUser.saveStroke(stroke);

}

void MenuManager::saveHighScores()
{
    this->activeUser.saveToFile();
    initHighScore();
}

//update the power of the power bar
void MenuManager::updatePower(int powerStep)
{
    this->powerBall += powerStep;
    if (this->powerBall > 30)
        this->powerBall = 30;

    if (this->powerBall <= 0)
        this->powerBall = 1;
}

bool MenuManager::getStateMenu()
{
    if (this->menu[this->selectedMenu].getStateMenu())
        return true;
    else
        return false;

}

int MenuManager::checkButtons(float x, float y)
{
    //reverse y in order to correctly map the glut coordinate system to opengl coordinate system
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;


    int level = -1;

    // Determine the behavior based on the selected menu.
    switch (this->selectedMenu)
    {
        // Animation menu (Initial menu)
    case 0:
        switch (this->menu[0].CheckButtons(x, y, 0))
        {
        case 0:
            level = -1;
            break;
        case 1:
            this->menu[0].setStateMenu(false);
            // Move to "Start Game" menu
            this->setSelectedMenu(1);
            level = -1; 
            break;
        }
        break;

        //start Game menu
    case 1:
        switch (this->menu[1].CheckButtons(x, y, 1))
        {
            //start button 
        case 0:
            this->menu[1].setStateMenu(false);
            level = 0; //first level
            this->loadGameUser = false;
            break;
            //load button
        case 1:
            this->menu[1].setStateMenu(false);
            this->setSelectedMenu(3);
            level = -1;
            break;

            //high-score button
        case 2:
            this->menu[1].setStateMenu(false);
            this->setSelectedMenu(4);
            level = -1;
            break;
            //exit button
        case 3:
            exit(1);
            break;
        }
        break;
    //pause menu
    case 2:
    {
        switch (this->menu[2].CheckButtons(x, y, 2))
        {
            //resume game button
        case 0:
            this->menu[2].setStateMenu(false);
            level = -1;
            break;
            //go back button
        case 1:
            this->menu[2].setStateMenu(false);
            this->setSelectedMenu(1);
            level = -1;
            break;

        case 2: //exit button
            this->menu[2].setStateMenu(false);
            level = -1;
            exit(1);
            break;
        }
        break;
    }
    //Load menu
    case 3:

        switch (this->menu[3].CheckButtons(x, y, 3))
        {

         //for each case, load the corresponding level 
        case 0:
            this->menu[3].setStateMenu(false);
            this->loadGameUser = true;
            level = 0;
            break;

        case 1:
            this->menu[3].setStateMenu(false);
            this->loadGameUser = true;

            level = 1;
            break;

        case 2:
            this->menu[3].setStateMenu(false);
            this->loadGameUser = true;

            level = 2;
            break;
        case 3:
            
            this->menu[3].setStateMenu(false);
            this->loadGameUser = true;

            level = 3;
            break;
        case 4:
            this->menu[3].setStateMenu(false);
            this->loadGameUser = true;

            level = 4;
            break;

        case 5:
            this->menu[3].setStateMenu(false);
            this->menu[1].setStateMenu(false);
            this->loadGameUser = false;
            this->setSelectedMenu(1);
            level = -1;
            break;
        }
        break;
    //High score menu:
    case 4:
    {
        //if press the exit menu 
        int index = this->menu[4].CheckButtons(x, y, 4);

        if (index == (this->menu[4].getSizeButtons() - 1))
        {
            this->menu[4].setStateMenu(false);
            this->menu[1].setStateMenu(true);
            //return to the init menu
            this->setSelectedMenu(1);
            level = -1;
            break;

        }

    }
 }
    return level;
}

bool MenuManager::getStateLoadGame()
{
    return loadGameUser;
}

string MenuManager::getUserActive()
{
    string userName;
    this->menu[1].getUserName(&userName);
    return userName;

}

//load high scores from file
void MenuManager::loadHighScores(const char* filename)
{
    this->history.clear();
    ifstream infile;
    infile.open(filename);
    string s;

    if (!infile)
    {
        cout << "Unable to open '" << filename
            << "'. Please check file and re-run command." << endl;
        exit(1);
    }


    while (infile >> s)
    {

        if (caseInsensitiveCompare(s, "begin_user"))
        {
            UserProfile temp;

            while ((infile >> s) && (!caseInsensitiveCompare(s, "end_user")))
            {
             
                string name;
                float score;
                string stroke;

                if (caseInsensitiveCompare(s, "username"))
                {
                    string name;
                    infile >> name;

                    if (name == "score")
                    {
                        name = " UNKNOWN ";
                        float score;
                        infile >> score;

                        score = roundf(score * 100) / 100.0;
                        temp.saveScore(score);

                    }
                     
                     temp.saveUser(name);
                }
                else if (caseInsensitiveCompare(s, "score"))
                {
                    float score;
                    infile >> score;
                 
                    score = roundf(score * 100) / 100.0;
                
                    temp.saveScore(score);
                }

                else if (caseInsensitiveCompare(s, "stroke"))
                {
                    string stroke;
                    infile >> stroke;
                    temp.saveStroke(stroke);

                }


            }
           

            this->history.push_back(temp);

        }

    }


}

//draw launch direction of the ball with an arrow.
void MenuManager::drawArrow(Point3D fulcrum, float roty, map<int, Point3D> verticesTile)
{

    glEnable(GL_LIGHTING);
    float materialColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float specularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

    float vertices[7][3] = { { 0.05f, 0.0f, 0.05f },
                            { 0.05f, 0.0f, -0.20f },
                             { 0.10f, 0.0f, -0.10f },
                             { 0.00f, 0.0f, -0.20f },
                             { -0.10f, 0.0f, -0.10f },
                             { -0.05f, 0.0f, -0.10f },
                             { -0.05f, 0.0f, 0.05f } };
   

    glPushMatrix();
    // Translate the drawing to the fulcrum point
    float yArrow = 0.0f;
    getYArrow(fulcrum, verticesTile, &yArrow);
    
    if (yArrow != 0 && yArrow > 0.15)
        yArrow = yArrow - 0.15;

    glTranslatef(fulcrum.x, fulcrum.y + yArrow, fulcrum.z);
    // Rotate about the fulcrum point for input angles
    glRotatef(roty, 0.0f, 1.0f, 0.0f);

    
    glBegin(GL_TRIANGLES);
    glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
    glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
    glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
    glEnd();
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

void MenuManager::getYArrow(Point3D point, map<int, Point3D> verticesTile, float* arrowPosition)
{
    for (map<int, Point3D>::iterator j = verticesTile.begin(); j != verticesTile.end(); j++)
    {
        Point3D pointOnTile = j->second;
        if (point.y < pointOnTile.y)
            *arrowPosition = pointOnTile.y;
        
    }

}
void MenuManager::resetPower()
{
    this->powerBall = 1;
}
int MenuManager::getPower()
{
    return this->powerBall;

}

void MenuManager::incrementStroke()
{
    this->userScore++;
    this->totalUserScore++;
}

void MenuManager::setParLevel(int par)
{
    this->parLevel = par;
}

void MenuManager::resetScore(bool matchFinished, bool backMenu)
{
    if (matchFinished)
    {
        this->init();
        this->totalUserScore = 0;
    }
    if(backMenu)
        this->totalUserScore = 0;

    this->userScore = 0;
}

void MenuManager::setSelectedMenu(int menuId)
{
    this->selectedMenu = menuId;
    this->menu[selectedMenu].setStateMenu(true);
}

int MenuManager::getIndexMenu()
{
    return this->selectedMenu;
}