//Extension code; 84RZJCB4DHYZJFHF
//Student ID : HAJ17684295
//Name: Kacper Hajda
#include "bots.h"
using namespace std;//makes it easier to write the vector function without using the std:: function.

void cDijkstra::Build(cBotBase& bot)
{
	for (int i = 0; i < GRIDWIDTH; i++)
	{
		for (int j = 0; j < GRIDHEIGHT; j++)
		{
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1; //link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	//this goes through each node in the grid and assigns the following described properties.

	cost[bot.PositionX()][bot.PositionY()] = 0;
	//assigns the first locations cost to zero
	while (closed[gTarget.PositionX()][gTarget.PositionY()] == false)
	{
		//a loop that will start calculating the nodes costs until it reaches the x and y of the player
		float tempCost = 1000;
		int x = 0;
		int y = 0;
		//variables that will be used to store the locations of the closed nodes and calculate the nodes that will are the shortest path.
		for (int i = 0; i < GRIDWIDTH; i++)
		{
			for (int j = 0; j < GRIDHEIGHT; j++)
			{
				if ((cost[i][j] <= tempCost) && (closed[i][j] != true) && (gLevel.isValid(i, j)))
				{
					tempCost = cost[i][j];
					x = i;
					y = j;
					//two forloops that will traverse the 2D array of nodes and check the cost of the nodes is less than or equal to
					//the temporary cost and that the node is not already a closed node and that the node isnt blocked
					//if the conditions are met, it will assign temp cost the cost of the node, and assign the nodes location to x and y
				}
			}
		}
		closed[x][y] = true;
		//sets the node at x and y to closed.
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <=1; j++)
			{
				if ((gLevel.isValid(x + i, y + j)) && (closed[x + i][y + j] == false))
				{
					//two for loops that check aroud the node both up and down
					//and check if those nodes are valid moves. if they are it will be used to calculate the new cost of the nodes.
					if (((j == 0) ^ (i == 0)) && (cost[x + i][y + j] > cost[x][y] + 1))
					{
						//an XOR if statement that checks that only one of the locations is a 1, as its either up or down, or left and right
						// and checks if the cost of the nodes is greater than the cost of the currrent node + 1
						cost[x + i][y + j] = cost[x][y] + 1;
						//works out the new cost of the nodes
						linkX[x + i][y + j] = x;
						linkY[x + i][y + j] = y;
						//links the surrounding nodes to this node.
					}
					else if (cost[x + i][y + j] > cost[x][y] + 1.4)
					{
						//sets all the diagonal nodes to 1.4
						cost[x + i][y + j] = cost[x][y] + 1.4;
						linkX[x + i][y + j] = x;
						linkY[x + i][y + j] = y;
						//sets all the diagonal nodes costs to + 1.4
						//and links them to the current node that the path finder is on.
					}
				}
			}
		}
	}


	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		if (nextClosedX < 40 && nextClosedY < 40)
		{
			inPath[nextClosedX][nextClosedY] = true;
			int tmpX = nextClosedX;
			int tmpY = nextClosedY;
			nextClosedX = linkX[tmpX][tmpY];
			nextClosedY = linkY[tmpX][tmpY];
			if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;

			//creates the path made by the pathfinderr to the target through the closed nodes.
		}

	}
	completed = true;
}
cDijkstra gDijkstra;


/*
                A star implementation

*/

void cAStar::Build(cBotBase& bot)//the path building function for A star that passes in the bot object.
{

	for (int i = 0; i < GRIDWIDTH; i++)
	{
		for (int j = 0; j < GRIDHEIGHT; j++)
		{
			closed[i][j] = false; //whether or not location is closed
			cost[i][j] = 1000; //cost value for each location
			linkX[i][j] = -1; //link X coord for each location
			linkY[i][j] = -1; //link Y coord for each location
			inPath[i][j] = false; //whether or not a location is in the final path
		}
	}
	//this goes through each node in the grid and assigns the following described properties.
	cost[bot.PositionX()][bot.PositionY()] = 0;
	//assigns the first locations cost to zero
	while (closed[gTarget.PositionX()][gTarget.PositionY()] == false)
	{
		//a loop that will start calculating the nodes costs until it reaches the x and y of the player
		float heuristic = 0; // heuristic initialisation.
		float tempCost = 1000;
		int x = 0;
		int y = 0;
		for (int i = 0; i < GRIDWIDTH; i++)
		{
			for (int j = 0; j < GRIDHEIGHT; j++)
			{
				if (heuristicChoice == 1) 
				{
					heuristic = fabs(gTarget.PositionX() - i) + fabs(gTarget.PositionY() - j);
				}
				else if (heuristicChoice == 2)
				{
					heuristic = (fabs(gTarget.PositionX() - i) + fabs(gTarget.PositionY() - j)) - (0.6) * min(fabs(gTarget.PositionX() - i), fabs(gTarget.PositionY() - j));
				}
				else if (heuristicChoice == 3)
				{
					heuristic = sqrt(pow(fabs(gTarget.PositionX() - i), 2) + pow(fabs(gTarget.PositionY() - j), 2));
				}
				//if else statement that, depending on the users choice, will calculate the shortest path using the different heuristic
				//functions, 1 being manhattan, 2 being diagonal and 3 being eucliean.

				if ((cost[i][j] + heuristic < tempCost) && (closed[i][j] != true) && (gLevel.isValid(i, j)))
				{
					tempCost = cost[i][j] + heuristic;
					x = i;
					y = j;
					//two forloops that will traverse the 2D array of nodes and check the cost of the nodes + the heuristic is less than or equal to
					//the temporary cost and that the node is not already a closed node and that the node isnt blocked
					//if the conditions are met, it will assign temp cost to the cost of the node
					// and the heuristic the cost of the node, and assign the nodes location to x and y
					//the heurstic is what makes the A star more efficient than dikstras as the nodes costs will be less the closer the node is
					// to the target, so it will scan less nodes to find the path as nodes that will have a higher cost will be ignored on the
					//next iteration of the while loop.
				}
			}
		}
		closed[x][y] = true;
		//sets the node at x and y to closed.
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((gLevel.isValid(x + i, y + j)) && (closed[x + i][y + j] == false))
				{
					//two forloops traversing the nodes around the currently selected node and calculating the costs around them.
					if (((j == 0) ^ (i == 0)) && (cost[x + i][y + j] > cost[x][y] + 1))
					{
						//an XOR if statement that checks that only one of the locations is a 1, as its either up or down, or left and right
						// and checks if the cost of the nodes is greater than the cost of the currrent node + 1
						cost[x + i][y + j] = cost[x][y] + 1;
						//calculate the cost of the nodes up, down, left and right of the current node.
						linkX[x + i][y + j] = x;
						linkY[x + i][y + j] = y;
						//links the nodes to the current node.

					}
					else if (cost[x + i][y + j] > cost[x][y] + 1.4)
					{
						cost[x + i][y + j] = cost[x][y] + 1.4;
						linkX[x + i][y + j] = x;
						linkY[x + i][y + j] = y;
						//sets all the diagonal nodes costs to + 1.4
						//and links them to the current node that the path finder is on.
					}
				}
			}
		}
	}


	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path

	coordinates.clear(); //clears the vector that contains the path that the pathfinding bot will take
	while (!done)
	{
		if (nextClosedX < 40 && nextClosedY < 40)
		{
			
			inPath[nextClosedX][nextClosedY] = true;
			int tmpX = nextClosedX;
			int tmpY = nextClosedY;
			//temporary variables that store the x and the y of the next closed location.
			coordinates.push_back(tmpX);
			coordinates.push_back(tmpY);
			//pushes back the x and the y cordinates of the node for the final path to be used by the path finder.
			nextClosedX = linkX[tmpX][tmpY];
			nextClosedY = linkY[tmpX][tmpY];
			if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) 
			{
				done = true;
				//once the next closed node is the target position, it will finish the loop.
			}
		}
	}

	completed = true;
	//sets the pathfiding to be complete
}
cAStar gAStar;
