//GUI Header for SDL2 API
//Dextron 2022

#pragma once

//DefinES

//SDL2 includes
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

//standard headers
#include <iostream>

//Custom headers
#include <commons.hpp>
#include <Events.hpp>


class Primitives{
    public:
        //Solids
        static void FilledRect(SDL_Renderer* renderer, SDL_FRect pos, SDL_Colour colour);
        static void Line(SDL_Renderer* renderer, SDL_FPoint point1, SDL_FPoint point2, SDL_Colour colour, int thickness=1);
        static void FilledCircle(SDL_Renderer* renderer, SDL_Colour colour, int x, int y, int radius);
        static void Text(SDL_Renderer* renderer, SDL_Rect pos, TTF_Font* font, SDL_Colour colour, std::string msg);
        //Outlines
        static void Rect(SDL_Renderer* renderer, SDL_FRect rect, SDL_Colour colour);
        static void Circle(SDL_Renderer* renderer, SDL_Colour colour, int x, int y, int radius);

        //Overloaded int functions
        static void FilledRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void Rect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Colour colour);
        static void Line(SDL_Renderer* renderer, SDL_Point point1, SDL_Point point2, SDL_Colour colour, int thickness=1);
};

//Switches

class rectSwitch{
    private:
        SDL_Rect pos;
        SDL_Colour c_fore, c_back, c_active;
        bool state; //Global state of switch.

        //Text
        TTF_Font* font;
        std::string s_msg;
    public:
        rectSwitch(SDL_Rect pos, SDL_Colour back, SDL_Colour fore, SDL_Colour active, TTF_Font* font, std::string msg);

        void update(SDL_Renderer*, Mouse mouse);
};

class ovalSwitch{
    private:
        SDL_Rect pos;
        SDL_Colour c_fore, c_back, c_active;
        bool state;

        //Text
        TTF_Font* font;
        std::string s_msg;
        
        //Borders
        int radius;
    public:
        ovalSwitch(SDL_Rect pos, SDL_Colour back, SDL_Colour fore, SDL_Colour active, TTF_Font* font, std::string msg);

        void update(SDL_Renderer* renderer, Mouse mouse);
};

//Buttons

class Button{
    private:
        bool state;

        //Positioning
        SDL_Rect pos;
        
        //Graphical
        SDL_Colour c_fore, c_back, c_active;
        TTF_Font* font;
        std::string s_msg;
    public:
        Button(SDL_Rect pos, SDL_Colour fore, SDL_Colour back, SDL_Colour active, TTF_Font* font, std::string msg);

        void update(SDL_Renderer* renderer, Mouse mouse);
};

class RndButton{
    private:
        bool state;

        //Positioning
        SDL_Rect pos;
        
        //Graphical
        SDL_Colour c_fore, c_back, c_active;
        TTF_Font* font;
        std::string s_msg;
    public:
        RndButton(SDL_Rect pos, SDL_Colour fore, SDL_Colour back, SDL_Colour active, TTF_Font* font, std::string msg);

        void update(SDL_Renderer* renderer, Mouse mouse);
};

class RadButton{
    private:
        bool state;

        int x, y, radius;

        SDL_Colour c_fore, c_back, c_active;
        TTF_Font* font;
        std::string s_msg;

    public:
        RadButton(int x, int y, int radius, SDL_Colour fore, SDL_Colour back, SDL_Colour active, TTF_Font* font, std::string msg);

        void update(SDL_Renderer* renderer, Mouse mouse);
};

//Forms

enum textPos{
    Outer_Left,
    Outer_Right,
    Top,
    Bottom,

    //Inner text positions
    Inner_Left,
    Centered,
    Inner_Right
};

class Form{
    private:
        bool state;

        //Logic vars
        SDL_Rect pos;

        //Graphical vars
        TTF_Font* font;
        SDL_Colour c_fore, c_back, c_text;
        textPos pos_text;
        SDL_Rect posText; //Coords for text.


    public:
        Form(SDL_Rect pos, SDL_Colour Fore, SDL_Color Back, SDL_Colour textColour, TTF_Font* font);

        void update(SDL_Renderer* renderer, std::string keyInput);

        //Flag functions
};


//Menus


