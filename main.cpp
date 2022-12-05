//======================================================================================
//Source code for main function = main control loop for programme
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

//Extension code; 84RZJCB4DHYZJFHF
//Student ID : HAJ17684295
//Name: Kacper Hajda

#include "game.h"
#include "level.h"
#include "dynamic.h"
#include "bots.h"
#include <windows.h>

//======================================================================================
//Globals
//======================================================================================
SDL_Window *gMainWindow = NULL;
SDL_Renderer *gMainRenderer = NULL;
SDL_Surface *tileSurface = NULL;
SDL_Surface* tileBlockedSurface = NULL;
SDL_Surface* targetSurface = NULL;
SDL_Surface* botSurface = NULL;
SDL_Surface* tileClosedSurface = NULL;
SDL_Surface* tileRouteSurface = NULL;
SDL_Texture* tileTexture = NULL;
SDL_Texture* tileBlockedTexture = NULL;
SDL_Texture* targetTexture = NULL;
SDL_Texture* botTexture = NULL;
SDL_Texture* tileClosedTexture = NULL;
SDL_Texture* tileRouteTexture = NULL;
bool gQuit;


//======================================================================================
//Main function
//======================================================================================
int main(int argc, char* argv[])
{
	gQuit = false;

    //======================================================================================
    //Initialise SDL
    //======================================================================================
    SDL_Init(SDL_INIT_EVERYTHING);
	gMainWindow = SDL_CreateWindow
	("Pathfinder", // window's title
		30, 50, // coordinates on the screen, in pixels, of the window's upper left corner
		640, 640, // window's length and height in pixels  
		SDL_WINDOW_OPENGL);
    gMainRenderer = SDL_CreateRenderer(gMainWindow, -1, SDL_RENDERER_ACCELERATED);

    MessageBox(0, "To change the heurstics press:\n1:(Manhattan)\n2:(Diagonal)\n3:(Euclidean)\nFollowed by the P button to path", "Instructions", MB_OK);
    //an alert box that will instruct the user on how to use the solution

    //======================================================================================
    //Load graphics for tiles, bot and target
    //======================================================================================
    tileSurface = SDL_LoadBMP("tile.bmp");
    tileBlockedSurface = SDL_LoadBMP("tile-blocked.bmp");
    targetSurface = SDL_LoadBMP("target.bmp");
    botSurface = SDL_LoadBMP("bot.bmp");
    tileClosedSurface = SDL_LoadBMP("tile-closed.bmp");
    tileRouteSurface = SDL_LoadBMP("tile-route.bmp");
    
    tileTexture = SDL_CreateTextureFromSurface(gMainRenderer, tileSurface);
    tileBlockedTexture = SDL_CreateTextureFromSurface(gMainRenderer, tileBlockedSurface);
    targetTexture = SDL_CreateTextureFromSurface(gMainRenderer, targetSurface);
    botTexture = SDL_CreateTextureFromSurface(gMainRenderer, botSurface);
    tileClosedTexture = SDL_CreateTextureFromSurface(gMainRenderer, tileClosedSurface);
    tileRouteTexture = SDL_CreateTextureFromSurface(gMainRenderer, tileRouteSurface);

    //======================================================================================
    //Load the map and set target position
    //======================================================================================
    gLevel.Load("maps/3.txt");
    gTarget.SetCurrent(30, 20, gLevel);
    //======================================================================================
    //Locals variables fro key presses and frame timer
    //======================================================================================
    SDL_Event event;
    const Uint8* keystate;  
    int timerMS = SDL_GetTicks();
    int deltaTimeMS = 0;

    //======================================================================================
    // Create Bot
    //======================================================================================
    cBotBase* pBot = new cbot_pathfinding();
    pBot->SetCurrent(10, 20, gLevel);

    //======================================================================================
    //Main loop
    //======================================================================================
    while (!gQuit)
    {
        //======================================================================================
        //Poll events for quit
        //======================================================================================
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gQuit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gQuit = true;
                    break;
                }
                break;
            }
        }

        //======================================================================================
        //Keyboard input for target control 
        //======================================================================================
        keystate = SDL_GetKeyboardState(NULL);
        static bool p_down = false;
        int offsetX = 0;
        int offsetY = 0;
        if (keystate[SDL_SCANCODE_UP]) offsetY -= 1;
        if (keystate[SDL_SCANCODE_DOWN]) offsetY += 1;
        if (keystate[SDL_SCANCODE_LEFT]) offsetX -= 1;
        if (keystate[SDL_SCANCODE_RIGHT]) offsetX += 1;


        if (keystate[SDL_SCANCODE_1]) //checks if key number 1 was pressed
        {
            gAStar.heuristicChoice = 1; // changes a public variable delcared in bots.h that will indicate
            //what heuristic method the program will be used.
            //can be changed whilst the bot is running but the number has to go first
            //then P has to be pressed to recalculate the path.
            //1 corresponds to manhattan distance
        }
        if (keystate[SDL_SCANCODE_2])//checks if key number 2 was pressed
        {
            gAStar.heuristicChoice = 2; //corresponds to Diagonal distance
        }
        if (keystate[SDL_SCANCODE_3])// checks if key number 3 was pressed
        {
            gAStar.heuristicChoice = 3;//corresponds to Euclidean distance
        }


        if (keystate[SDL_SCANCODE_P])
        {
            if (!p_down)
            {
                gAStar.Build(*pBot);
                p_down = true;
            }
        }
        else { p_down = false; }
        //checks the state of button P, if its pressed down, it will rebuild the path finding solution.

        if ((offsetX != 0) || (offsetY != 0))
        {
            gTarget.SetNext((gTarget.PositionX() + offsetX), (gTarget.PositionY() + offsetY), gLevel);
        }

        //======================================================================================
        //Start render for this frame
        //======================================================================================
        SDL_SetRenderDrawColor(gMainRenderer, 200, 200, 255, 255);
        SDL_RenderClear(gMainRenderer);

        //======================================================================================
        //Compute time in miliseconds of last update cycle
        //======================================================================================
        int newFrameTimeMS = SDL_GetTicks();
        deltaTimeMS = newFrameTimeMS - timerMS;
        if (deltaTimeMS < 0) deltaTimeMS = 0;
        timerMS = newFrameTimeMS;

        //======================================================================================
        //Update moving objects
        //======================================================================================
        gTarget.Update(deltaTimeMS);
        pBot->Update(deltaTimeMS);

        //======================================================================================
        //Draw the level grid, then target, then bot
        //======================================================================================
        gLevel.Draw();
        gTarget.Draw(targetTexture);
        pBot->Draw(botTexture);

        //======================================================================================
        //Finalise render for this frame
        //======================================================================================
        SDL_RenderPresent(gMainRenderer);
	}

    //======================================================================================
    //Clean up
    //======================================================================================
	SDL_DestroyWindow(gMainWindow);
	SDL_Quit();
	return 0;
}

