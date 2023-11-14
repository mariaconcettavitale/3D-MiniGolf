#include "Level.h"
#include "../Libraries.h"

//This method draws tileset and cup for each current level
void Level::drawLevel()
{
	for (map<int, Tile>::iterator i = this->tileSet.begin(); i != this->tileSet.end(); ++i)
	{
		if (i->second.getTileType() == "tile")
		{
			i->second.draw(0.0f, 0.7f, 0.0f);

		}
		
	}

	cups.draw(20);

}
