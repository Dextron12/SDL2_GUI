#ifndef GUI_HPP
#define GUI_HPP

#pragma once

//CPP Includes
#include <iostream>

//SDL2 Includes
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

class Scene{
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;

        Events events;

        Scene(int width, int height, const char* Title);

};

class Events: public Scene{
    private:
        SDL_Event event;

        //Resize contraint
        SDL_Point resizeWindow;
        bool b_windowResize;

    public:
        bool appState;

        void update();


        //getter
        bool windowResized();

};

#endif