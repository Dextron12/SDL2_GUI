//SDL_GUI
//Author: Dextron12

#pragma once

//standard includes
#include <iostream> //<--- For debugging purposes


//SDL Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Events{
    private:
        int width, height;
        bool programState;
        SDL_Event event;

        //DeltaTime vars
        float LAST, NOW;

    public:
        //Pulbic variables
        SDL_Window* window;
        SDL_Renderer* renderer;
        float deltaTime;

        Events(const char* title, int windowWidth, int windowHeight);

        void update();

        //Getter functions
        bool getState();
        
        
};