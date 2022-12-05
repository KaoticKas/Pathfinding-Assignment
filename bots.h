#pragma once
//Extension code; 84RZJCB4DHYZJFHF
//Student ID : HAJ17684295
//Name: Kacper Hajda
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
//important libraries that help the program run through functions.

class cBotRandom : public cBotBase//initial pathfinder that doesnt have any pathfinding attached
{
	virtual void ChooseNextGridPosition();
};

class cbot_pathfinding : public cBotBase //bot that inherits the botBase header.
{
	virtual void ChooseNextGridPosition(); //creates a class that contains the choose next grid function
};

class cDijkstra
{
	public:
		bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed
		float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location
		int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location
		int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location
		bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in the final path
		bool completed;

		cDijkstra() { completed = false; }//function that sets the algorithms complition to false at first

		virtual void Build(cBotBase& bot); //the build function that will create the path

		// Dijkstras header class that contains the definitions of variables that will be used in the cpp file
		//as well as any functions that it will contain
};
class cAStar : public cDijkstra //the Astar algorithm class that inherits the properites of Dijkstras class
{
public:
	virtual void Build(cBotBase& bot); //the build function that builds the path for the bot
	std::vector<int>coordinates;//a vector is an array that can change size, so its perfect for the list of coordinates of the path.
	int heuristicChoice =1;//a default public heuristic choice that is used to change the heuristic function by the user in the main.cpp
};
extern cDijkstra gDijkstra;
extern cAStar gAStar;
//those variables can be externally called anywhere in the program.