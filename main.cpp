#include "Libraries.h"
#include "Level/LevelManager.h"
#include <../irrKlang/irrKlang.h>

using namespace irrklang;
bool pressing = false;
bool fullscreen = false;
int kWindowWidth = 800;
int kWindowHeight = 640;

LevelManager levels;

void setupLight(float posx, float posy, float posz, float a)
{
    static GLfloat light0Ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static GLfloat light0Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    static GLfloat light0Specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    static GLfloat light0Position[] = { posx, posy, posz, a };


    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void glUpdateScene(int value)
{
    //1/fps is the time elapsed to process 1 frame at given frame rate .
    levels.updateCurrentLevel(1 / fps);
    glutPostRedisplay();
    //*1000 is specified to express the time value in millisecond, 1 is the frame per second.
    glutTimerFunc(1000 / fps, glUpdateScene, value);
}

// Function to draw the scene.
void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSetCursor(GLUT_CURSOR_NONE);

    glPushMatrix();
    levels.drawCurrentLevel(pressing);
    glPopMatrix();

    glutSwapBuffers();
}


// To toggle the fullscreen state of the GL window
void toggleFullScreenMode(void)
{
   
    fullscreen = !fullscreen;
  

    if (fullscreen)
    {
        glutFullScreen();
        kWindowWidth = glutGet(GLUT_SCREEN_WIDTH);
        kWindowHeight = glutGet(GLUT_SCREEN_HEIGHT);
    }
    else
    {
        glutReshapeWindow(800, 640);
        glutPositionWindow(100, 100);
        kWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
        kWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    }
    
}

void setup()
{
    glClearColor(0.2f, 0.4f, 0.73f, 0.0f);

    glClearDepth(1.0f);
    glEnable(GL_CULL_FACE);// Enable cull face

}

void special(int key) {

    if (key == GLUT_KEY_LEFT)
    { //counterclockwise rotation - positive angle
        levels.updateTheta(arrowMoveStep);

        if (levels.getTheta() < 0)
            levels.updateTheta(360);
    }

    if (key == GLUT_KEY_RIGHT)
    {
        //clockwise rotation - negative angle
        levels.updateTheta(-arrowMoveStep);


        if (levels.getTheta() > 360)
            levels.updateTheta(-360);


    }

    if (key == GLUT_KEY_F1)     
        toggleFullScreenMode();

   

    if (key == GLUT_KEY_UP)
        levels.menu.updatePower(1);

    if (key == GLUT_KEY_DOWN)
        levels.menu.updatePower(-1);

  
}


void glSpecial(int key, int x, int y)
{
    special(key);

    glutPostRedisplay();
   
}

void keyboards_handle(unsigned char key, int x, int y)
{
    /*
    * If the user presses the 'Escape' button while in the initial menu(animation - index = 0),
    *    the game will be exited.If the user presses the 'Escape' button during the game,
    *    the pause menu will be activated.
    */
    switch (key)
    {
    case 27:
        if (levels.menu.getIndexMenu() != 0)
            //activate the pause menu
            levels.menu.setSelectedMenu(2);
        else
            //exit
            glutLeaveMainLoop();

        break;
    case 32: //press space bar to play!
        pressing = true;
        break;
    case 's': //set the acceleration
        levels.setBallAcceleration();
 
    default:
        break;
    }
}

void glMouse(int button, int state, int x, int y)
{
    // Code to handle Mouse clicks goes here
    int flag = -1;
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if ((state == GLUT_UP) && (levels.menu.getStateMenu()))
        {
            flag = levels.menu.checkButtons(x, y);
            //check if the user has chosen a level by load game menu
            if (flag != -1)
                //set the current level chosen by the user
                levels.resetToLevel(flag);
        }
        break;
    case GLUT_MIDDLE_BUTTON:
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    }


}



int main(int argc, char** argv) {


    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(kWindowWidth, kWindowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D MiniGolf by Maria Concetta Vitale");

    toggleFullScreenMode();

    //clear buffers
    setup();
  

    glEnable(GL_DEPTH_TEST);

    
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_NORMALIZE);

  

    //init menu
    levels.menu.initAnimation(kWindowWidth, kWindowHeight);
    levels.menu.init();

   

    glewExperimental = GL_TRUE;
    glewInit();

    
    //setup asset and levels
    levels.readLevelsFromFile("./Assets/tileSetGame.txt");
    //setup light 0 
    setupLight(0.0f, 5.0f, 0.0f, 1.0f);

    glutDisplayFunc(drawScene);
    glutSpecialFunc(glSpecial);
    glutKeyboardFunc(keyboards_handle);
    glutMouseFunc(glMouse);

    glutTimerFunc(1000 / fps, glUpdateScene, 1);

    // audio setup
    ISoundEngine* SoundEngine = createIrrKlangDevice();
    SoundEngine->play2D("./Audio/start.wav", true);
    SoundEngine->setSoundVolume(0.4);

    glutMainLoop();
    return 0;
}
