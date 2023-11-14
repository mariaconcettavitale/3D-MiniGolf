#include "Menu.h"

void Menu::init(int numberOfButtons, vector<Point2D> menu, bool animation)
{
    this->numberButtons = numberOfButtons;
    
    this->buttons = menu;
    if (animation)
        this->obj.loadAnimation();

}

//center the buttons at middle of window screen
void Menu::rearrangeButtons(GLfloat width, GLfloat height)
{

    float totalButtonHeight = this->numberButtons * (BUTTON_OFFSET_HEIGHT + 40);

    float startY = (float)(height / 2) + (totalButtonHeight / 2);

    for (int i = 0; i < this->numberButtons; i++) {
        this->buttons[i].x = (float)(width / 2) - (BUTTON_OFFSET_WIDTH / 2); // Center horizontally
        this->buttons[i].y = startY - i * (BUTTON_OFFSET_HEIGHT + 40); // Adjust the Y-coordinate for each button


    }

}

//check wether button clicked and return its index
int Menu::CheckButtons(float x, float y, int selectedMenu)
{

    string choosenName;
    for (int i = 0; i < this->numberButtons; i++)
    {
        if ((y >= this->buttons[i].y) && (y < (this->buttons[i].y + BUTTON_OFFSET_HEIGHT)) && (x >= this->buttons[i].x) && (x < (this->buttons[i].x + BUTTON_OFFSET_WIDTH)))
        {
            return i;
            break;
        }

        //if the selected menu is equal to 1, so handle and save the username chosen by the user interacting with the menu.
        if (selectedMenu == 1)
        {

            if ((y >= this->buttons[i].y) && (y < (this->buttons[i].y + BUTTON_OFFSET_HEIGHT)) && (x >= this->buttons[this->numberButtons - 1].x - 20.0f) && (x < (this->buttons[this->numberButtons - 1].x + BUTTON_OFFSET_WIDTH) - 2.0f))
            {
                
                if (this->userIndex > 0)
                    this->userIndex -= 1;
                else
                    this->userIndex = this->sizeUsers - 1;

              

                this->buttons[this->numberButtons - 1].text_menu = this->getUsersPossibility();
                this->nameActiveUser = this->buttons[this->numberButtons - 1].text_menu;

                break;

            }


            if ((y >= this->buttons[i].y) && (y < (this->buttons[i].y + BUTTON_OFFSET_HEIGHT)) && (x >= this->buttons[this->numberButtons - 1].x + 2.0f) && (x < (this->buttons[this->numberButtons - 1].x + BUTTON_OFFSET_WIDTH) + 20.0f))
            {
                this->userIndex += 1;
               
                this->buttons[this->numberButtons - 1].text_menu = this->getUsersPossibility();
                this->nameActiveUser = this->buttons[this->numberButtons - 1].text_menu;

                break;

            }


        }
    }
}


string Menu::getUsersPossibility()
{

    return this->usersName[this->userIndex % this->sizeUsers];
}

void Menu::resetUserId()
{
    this->userIndex = -1;
}

int Menu::getSizeButtons()
{
    return this->buttons.size();
}

void Menu::setIndexTexture(float index)
{
    this->indexTexture = index;
}

void Menu::setFPState(bool state)
{
    this->updateFPS = state;
}

void Menu::setStateMenu(bool state)
{
    this->isActive = state;
}

bool Menu::getStateMenu()
{
    return this->isActive;
}

void Menu::Draw(int idMenu, bool pressing, int* numTextures, float* lastFrame)
{

    GLfloat windowWidth;
    GLfloat windowHeight;
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);

   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();

    glOrtho(0, windowWidth, 0, windowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);


    Point2D bottomLeft, bottomRight, topRight, topLeft;
   
    //while the user doesn't press space-bar 
    if (!pressing)
    {
        /* 
           order drawing :
           text start button
           quads in which draw the texture.
       */
        this->isActive = true;
    
        if (this->animationHandle)
        {

            bottomLeft.x = this->buttons[1].x;
            bottomLeft.y = this->buttons[1].y;
            bottomRight.x = this->buttons[1].x + BUTTON_OFFSET_WIDTH;
            bottomRight.y = this->buttons[1].y;
            topLeft.x = bottomLeft.x;
            topLeft.y = bottomLeft.y + BUTTON_OFFSET_HEIGHT;
            topRight.x = bottomRight.x;
            topRight.y = bottomRight.y + BUTTON_OFFSET_HEIGHT;

            // Calculate the center of each button
            GLfloat centerX = (topLeft.x + bottomRight.x) / 2 - (buttons[1].text_menu.length() * 4);
            GLfloat centerY = (topLeft.y + bottomRight.y) / 2;

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glPushMatrix();

            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);

            glRasterPos2f(centerX, centerY);

            for (int j = 0; j < (int)this->buttons[1].text_menu.length(); j++)
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->buttons[1].text_menu[j]);

            glPopMatrix();

            glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

            bottomLeft.x = this->buttons[0].x;
            bottomLeft.y = this->buttons[0].y;
            bottomRight.x = this->buttons[0].x + windowWidth;
            bottomRight.y = bottomLeft.y;
            topRight.x = bottomRight.x;
            topRight.y = windowHeight;
            topLeft.x = bottomLeft.x;
            topLeft.y = topRight.y;

            glPushMatrix();
            glEnable(GL_DEPTH);
            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, this->obj.textures[this->indexTexture].getTextureId());

            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(bottomLeft.x, bottomLeft.y);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(bottomRight.x, bottomRight.y);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(topRight.x, topRight.y);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(topLeft.x, topLeft.y);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);

            float currentTime = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

           

            if (this->indexTexture == 132) // max index reached
            {
                /*
                * Set the lastFrame with the currentTime in order to compute the time elapsed from the lastFrame.
                * This is only done once the condition is met to avoid recalculating the 'last frame' value.
               *  Indeed the indexTexture value is 132 until the elapsed time condition is
                * satisfy**/
               
                if (this->updateFPS==false)
                {
                    *lastFrame = currentTime;
                   
                    this->updateFPS = true;
                }
            }
            else
                this->indexTexture += 1;
              

            *numTextures = this->indexTexture;

            glDisable(GL_DEPTH);
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }
    }
    else //if animation is false
    {
        Point2D bottomLeft, bottomRight, topRight, topLeft;
        for (int i = 0; i < this->numberButtons; i++)
        {
            bottomLeft.x = this->buttons[i].x;
            bottomLeft.y = this->buttons[i].y;
            bottomRight.x = this->buttons[i].x + BUTTON_OFFSET_WIDTH;
            bottomRight.y = this->buttons[i].y;
            topLeft.x = bottomLeft.x;
            topLeft.y = bottomLeft.y + BUTTON_OFFSET_HEIGHT;
            topRight.x = bottomRight.x;
            topRight.y = bottomRight.y + BUTTON_OFFSET_HEIGHT;
           
            // Calculate the center of each button
            GLfloat centerX = (topLeft.x + bottomRight.x) / 2 - (buttons[i].text_menu.length() * 4);
            GLfloat centerY = (topLeft.y + bottomRight.y) / 2;


            glPushMatrix();
            glLoadIdentity();
            glColor3f(1.0f, 1.0f, 1.0f);


            glRasterPos2f(centerX, centerY);

            for (int j = 0; j < (int)this->buttons[i].text_menu.length(); j++)
            {

                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this->buttons[i].text_menu[j]);
            }
            glPopMatrix();



            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.0f, 0.0f, 0.0f, 0.7f);

            glBegin(GL_QUADS);
            glVertex2f(bottomLeft.x, bottomLeft.y);
            glVertex2f(bottomRight.x, bottomRight.y);
            glVertex2f(topRight.x, topRight.y);
            glVertex2f(topLeft.x, topLeft.y);
            glEnd();
            glDisable(GL_BLEND);

           

            glPopMatrix();

        }
        //draws arrows to choose the name user
        if (idMenu == 1)
        {
            glPushMatrix();
            glLoadIdentity();
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            glBegin(GL_TRIANGLES);
            glVertex2f(buttons[this->numberButtons - 1].x + BUTTON_OFFSET_WIDTH + 2.0f, buttons[this->numberButtons - 1].y);
            glVertex2f(buttons[this->numberButtons - 1].x + BUTTON_OFFSET_WIDTH + 2.0f, buttons[this->numberButtons - 1].y + BUTTON_OFFSET_HEIGHT);
            glVertex2f(buttons[this->numberButtons - 1].x + BUTTON_OFFSET_WIDTH + 20.0f, buttons[this->numberButtons - 1].y + BUTTON_OFFSET_HEIGHT / 2);
            glEnd();

            glBegin(GL_TRIANGLES);
            glVertex2f(buttons[this->numberButtons - 1].x - 2.0f, buttons[this->numberButtons - 1].y);
            glVertex2f(buttons[this->numberButtons - 1].x - 2.0f, buttons[this->numberButtons - 1].y + BUTTON_OFFSET_HEIGHT);
            glVertex2f(buttons[this->numberButtons - 1].x - 20.0f, buttons[this->numberButtons - 1].y + BUTTON_OFFSET_HEIGHT / 2);
            glEnd();
            glPopMatrix();


        }
       
        glPushMatrix();
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
        glBegin(GL_QUADS);
        glVertex2f(5.0f, windowHeight - 10.0f);
        glVertex2f(5.0f + windowWidth - 10.0f, windowHeight - 10.0f);
        glVertex2f(5.0f + windowWidth - 10.0f, 10.0f);
        glVertex2f(5.0f, 10.0f);
        glEnd();
        glDisable(GL_BLEND);
        glPopMatrix();

    }

    glPopMatrix();
}

void Menu::getUserName(string* name)
{
    *name = this->nameActiveUser;
}

