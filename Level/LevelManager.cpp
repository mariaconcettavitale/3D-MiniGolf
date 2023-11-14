#include "../Libraries.h"
#include "LevelManager.h"

//setup the IrrKlang sound engine object
ISoundEngine* soundEffect = createIrrKlangDevice();

/*
* This method reads level data from a file specified by filename. 
* It processes the file to extract information about the course, holes, 
* tiles, tees, and cups for each level. The data is stored in appropriate data structures.
*/

void LevelManager::readLevelsFromFile(const char* filename)
{
	sky.setParameters(this->menu.getIndexMenu());
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		cout << "Unable to open '" << filename
			<< "'. Please check file and re-run command." << endl;
		exit(1);
	}
	
	currentLevel = 0;
	string s;
	while (infile >> s)
	{
		if (caseInsensitiveCompare(s, "course"))
		{
			string name;
			infile >> name;
			string::iterator it = name.end();
			it--;
			while (*it != '\"')
			{
				infile >> s;
				name += " " + s;
				it = name.end();
				it--;
			}
			courseName = name;
			infile >> numberOfLevels;
		}
		else if (caseInsensitiveCompare(s, "begin_hole"))
		{
			Level lvl;
			while ((infile >> s) && (!caseInsensitiveCompare(s, "end_hole")))
			{
				int i;
				float a, b, c;
				Point3D point;
				if (caseInsensitiveCompare(s, "name"))
				{
					string name;
					infile >> name;
					string::iterator it = name.end();
					it--;
					while (*it != '\"')
					{
						infile >> s;
						name += " " + s;
						it = name.end();
						it--;
					}
					lvl.levelName = name;
				}
				else if (caseInsensitiveCompare(s, "tile"))
				{
					Tile tile;
					int tileId, numberOfVertices;
					tile.setTileType("tile");
					infile >> tileId;
					infile >> numberOfVertices;
					tile.setTileID(tileId);
					tile.setNumberOfVertices(numberOfVertices);
					for (int j = 0; j < tile.getNumberOfVertices(); j++)
					{
						infile >> a;
						infile >> b;
						infile >> c;
						point.init(a, b, c);
						tile.vertices[j] = point;

					}
					for (int j = 0; j < tile.getNumberOfVertices(); j++)
					{
						infile >> i;
						tile.neighbours[j] = i;
					}
					
					//Newell method to computes the normal of each faces.
					for (int j = 0; j < tile.getNumberOfVertices(); j++)
					{						
						Vector3D normal;
						int s = (j + 1) % (tile.getNumberOfVertices());
						Point3D Vj, Vs;
						Vj = tile.vertices[j];
						Vs = tile.vertices[s];
						normal.x = (Vj.y - Vs.y) * (Vj.z + Vs.z);
						normal.y = (Vj.z - Vs.z) * (Vj.x + Vs.x);
						normal.z = (Vj.x - Vs.x) * (Vj.y + Vs.y);
						tile.updateNormal(normal);
					}

					tile.normalizeNorm();

					tile.initCollisionDetectionEdges();
					lvl.tileSet[tile.getTileId()] = tile;
				}
				else if (caseInsensitiveCompare(s, "tee"))
				{
					Tee tee;
					tee.teeID = 0;
					infile >> tee.tileID;
					infile >> a;
					infile >> b;
					infile >> c;
					tee.vertex.init(a, b, c);
					tee.normal.init(lvl.tileSet[tee.tileID].getNormal());
					lvl.tees = tee;
				}
				else if (caseInsensitiveCompare(s, "cup"))
				{
					Cup cup;
					cup.cupID = 0;
					infile >> cup.tileID;
					infile >> a;
					infile >> b;
					infile >> c;
					cup.vertex.init(a, b, c);
					cup.normal.init(lvl.tileSet[cup.tileID].getNormal());
					lvl.cups = cup;
				}
				//set the number of predetermined number of strokes called 'par'
				else if (caseInsensitiveCompare(s, "par"))
					infile >> lvl.Par;
			}
			levels.push_back(lvl);
		}
	}
	infile.close();

	resetToLevel(this->currentLevel);
	vector<string> levelsName;
	for (int i = 0; i < (int)levels.size(); i++)
		levelsName.push_back(levels[i].levelName);

	//setup the menu load game section
	this->menu.initLoadGame(levelsName);
	//setup the menu high score section
	this->menu.initHighScore();

}
/*
* This method sets the current game level to the one specified by the index.
* It initializes the player's ball position, camera, and other game-related parameters. 
*/

void LevelManager::resetToLevel(int index)
{
	currentLevel = index;
	
	if (currentLevel >= numberOfLevels)
		currentLevel = 0;
	
	if(currentLevel==0)
		this->menu.resetScore(false,true);
	
	ballOnTileID = levels[currentLevel].tees.tileID;
	ball.init(levels[currentLevel].tees.vertex, levels[currentLevel].tees.normal);
	this->theta_aroundY = 0;
	this->camera.UpdateCamera(ball.getPosition(), getDirection(1), CAMERA_DISTANCE);
	this->menu.setParLevel(levels[currentLevel].Par);
	this->menu.resetPower();
}

/*
	we start from 180 because the cosine(the z direction) is - 1
	and therefore the direction of the camera is oriented with
	respect to the negative values of the z axis
	*/

Vector3D LevelManager::getDirection(int x)
{
	Vector3D direction(0, 0, 0);
	
	direction.x = sin(DEGREES_TO_RADIANS(this->theta_aroundY - 180));
	direction.z = cos(DEGREES_TO_RADIANS(this->theta_aroundY - 180));
	direction.ScalarMultiply((float)x);

	return direction;
}

void LevelManager::setTheta(float theta)
{
	theta_aroundY = theta;
}
void LevelManager::updateTheta(float theta)
{

		theta_aroundY += theta;
	
}
float LevelManager::getTheta()
{
	return theta_aroundY;
}

void LevelManager::drawCurrentLevel(bool pressing)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Variables defining window size
	GLfloat windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	GLfloat windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	glCullFace(GL_BACK);

	glPushMatrix();

		//setup camera
		this->camera.setLookAt(windowWidth, windowHeight);
		//set color buffer to white
		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
			
			
			levels[currentLevel].drawLevel();
			//arguments: color RGB
			ball.draw(1.0f, 1.0f, 1.0f);
			//arguments: models and position
			drawFlag("../MiniGolf3D/Assets/flag.3ds", levels[currentLevel].cups.vertex);
			sky.Draw();
			//draw arrow only if the ball is stationary (to simulate the reality of golf game)
			if (ball.isEqualToOld())
				this->menu.drawArrow(ball.getPosition(), this->theta_aroundY, levels[currentLevel].tileSet[ballOnTileID].vertices);
	
		
		 //if the bar space has been pressed, the boolean value 'pressing' became true so we can active and draw the menu .
		 this->menu.drawActiveMenu(pressing);
		
		 glPopMatrix();
		 
		
	glPopMatrix(); 

	glDisable(GL_FOG);


}


void LevelManager::drawFlag(string path, Point3D initPos)
{
	Vector3D scale(0.005f, -0.005f, 0.005f);
	model.init(initPos, scale);
	model.Load3dsObject(path.c_str());
	model.Draw();
}

/*
* This method updates the game world for the current level. 
* It moves the player's ball, handles collisions with tiles, and updates the camera.
*/

void LevelManager::updateCurrentLevel(float deltaTime)
{
	if (!this->menu.getStateMenu())
	{
		ball.move(deltaTime);
		resolveCollisions(deltaTime);
		this->camera.UpdateCamera(ball.getPosition(), getDirection(1), CAMERA_DISTANCE);
		ball.applyFriction();
	}

}

void LevelManager::resolveCollisions(float t)
{
	Plane tilePlane;
	

	// Loop through the vertices and edge normals of the current tile.
	// This loop handles collisions with individual tiles.
	for (int i = 0; i < levels[currentLevel].tileSet[ballOnTileID].getNumberOfVertices(); i++)
	{
		// Initialize the plane with vertex and edge normal information.
		tilePlane.init(levels[currentLevel].tileSet[ballOnTileID].vertices[i], levels[currentLevel].tileSet[ballOnTileID].edgeNormals[i]);

		// Calculate the signed distance 'ds' of the ball's position to the tile plane.
		float ds = tilePlane.ComputePointPlaneHalfSpace(ball.getPosition());
		//if the distance is less then BALL_RADIUS: collision detected!
		if (ds < BALL_RADIUS)
		{
		
			// If the current tile has no neighboring tile (i.e., a boundary tile).
			if (levels[currentLevel].tileSet[ballOnTileID].neighbours[i] == 0)
			    // Reflect the ball's acceleration and ball's velocity vectors off the tile's edge normal.
				ball.updateReflection(levels[currentLevel].tileSet[ballOnTileID].edgeNormals[i]);
			else
			{  // Update the current tile ID to the ID of the neighboring tile.
				int ID = levels[currentLevel].tileSet[ballOnTileID].neighbours[i];
				ballOnTileID = ID;
			}
		}
	}

	//after handles the collision along y axis, so re-initialize the tilePlane
	tilePlane.init(levels[currentLevel].tileSet[ballOnTileID].vertices[0],levels[currentLevel].tileSet[ballOnTileID].getNormal());

	float yOffset = tilePlane.ComputePointPlaneHalfSpace(ball.getPosition());
	if (yOffset < BALL_RADIUS)
	{
		// Adjust the ball's y-position to be on top of the tile's plane, considering the ball's radius.
		float y = tilePlane.ComputeSafeYonPlane(ball.getPosition().x, ball.getPosition().z) + BALL_RADIUS;
		ball.setY(y);
		
		ball.decreaseVelocity(-0.5f);
		ball.setYAcceleration(GRAVITY);
	}

	//update the velocity after the collision
	ball.updateVelocity(t);
	

	float ballToCup_dist = sqrt(pow(levels[currentLevel].cups.vertex.x - ball.getPosition().x, 2) + pow(levels[currentLevel].cups.vertex.z - ball.getPosition().z, 2));
	//verify if the ball hit with the cup
	if ((ballToCup_dist < CUP_RADIUS) && (ball.getPosition().y <= levels[currentLevel].cups.vertex.y + BALL_RADIUS) && (ball.getVelocity().Length() < 0.9f))
	{
		//so, update the current level 
		currentLevel++;
		// If all levels are completed and the game is not in load mode:
		if (currentLevel >= this->numberOfLevels && this->menu.getStateLoadGame() == false)
		{
			//drawMenu
			this->menu.setSelectedMenu(1);
			//reset both score and total score
			this->menu.saveHighScores();
			this->menu.resetScore(true, false);
			//restart to level 0
			resetToLevel(currentLevel);

		}
		else
		{
			// If the game is in load mode:
			// Display the game menu, save high scores, reset scores, and return to the first level.

			if (this->menu.getStateLoadGame())
			{
				this->menu.setSelectedMenu(1);
				this->menu.saveHighScores();
				this->menu.resetScore(true, false);
				resetToLevel(0);


			}
			else
				//continue game: reset only user score and not total score
				this->menu.resetScore(false,false);
			resetToLevel(currentLevel);

		}
		//set sound when the ball hit the cup.
		soundEffect->play2D("../MiniGolf3D/Audio/win.wav");
	}
}


void LevelManager::setBallAcceleration()
{

	
		int power = this->menu.getPower();

		if (ball.isEqualToOld())
		{
			ball.setAcceleration(getDirection(power * powerMultiplier));
			//increment the score of the user after the launch of the ball
			this->menu.incrementStroke();
			soundEffect->play2D("../MiniGolf3D/Audio/power.wav");
		}

}



