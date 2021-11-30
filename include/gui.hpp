//SDL_GUI | GUI Header
//Author: Dextron12


#pragma once

//Standard headers
#include <iostream> //<--- For debugging purposes

//SDL2 Headers
#include <SDL2/SDL.h>

class Primitives{
    public:
        static void setColour(SDL_Renderer* renderer, SDL_Colour colour);

        static void Rectangle(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void Line(SDL_Renderer* renderer, SDL_Point begin, SDL_Point end, SDL_Colour colour);
        static void Circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour);
};