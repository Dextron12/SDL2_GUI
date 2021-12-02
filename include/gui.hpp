//SDL_GUI | GUI Header
//Author: Dextron12


#pragma once

//Standard headers
#include <iostream> //<--- For debugging purposes

//SDL2 Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Primitives{
    public:
        static void setColour(SDL_Renderer* renderer, SDL_Colour colour);

        static void Rectangle(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void Line(SDL_Renderer* renderer, SDL_Point begin, SDL_Point end, SDL_Colour colour);
        static void Circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour);
        
        static void Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, SDL_Colour colour, char* msg);
        static TTF_Font* loadFont(std::string path);

        static void lineRectangle(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void lineCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour);
};


//A input class to gather precise user-input(DO NOT USE THIS FOR SIMPLE KEY PRESSES!)
class TextInput{
    private:
        char* text;
        bool activeState = false;

    public:
        //No need for a user-defined constructor, call enableInput() to use object

        //Enable or disable object input
        void enableInput();
        void disableInput();

        //update key press events
        void update(SDL_Event event);

        //Returns a char* of text input, if active. Otherwise returns NULL
        char* getText();
};