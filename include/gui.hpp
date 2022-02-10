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
        SDL_Point windowSize;

        bool appState;

        Scene(int width, int height, const char* Title);
};

class Events{
    private:
        SDL_Event event;

    public:
        

        void update(Scene* scene);


        //getter
        

};





#endif