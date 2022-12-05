//Extension code; 84RZJCB4DHYZJFHF
//Student ID : HAJ17684295
//Name: Kacper Hajda
#include "bots.h"
#include "stdlib.h"
void cbot_pathfinding::ChooseNextGridPosition()//the pathfinding script that uses the chooseNextGrid function to traverse the nodes.
{
	for (int i = 0; i < int(gAStar.coordinates.size() - 1); i += 2)
	{
		//a loop that will go through each of the coordinates of the vector called coordinates
		//that is used by the bot to traverse the path.
		//it iterates every 2 positions as position 1 is x and position y is position 2.
		SetNext((gAStar.coordinates[i]), (gAStar.coordinates[i+1]), gLevel);
		//the setNext function sets the new coordinates on the map that the bot will animate towards.
	}
}