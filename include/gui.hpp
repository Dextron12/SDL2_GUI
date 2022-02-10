#ifndef GUI_HPP
#define GUI_HPP

#pragma once

//CPP Includes
#include <iostream>

//SDL2 Includes
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

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


class Scene{
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Point windowSize;

        float NOW, LAST, deltaTime;

        //Mouse
        SDL_Point mousePos;
        Uint32 mouseButtons;

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


//Text Position
enum textAlignment{
    //IN
    I_LEFT,
    I_RIGHT,
    CENTER,

    //Out
    TOP,
    BOTTOM,
    O_LEFT,
    O_RIGHT
};

//Switches
class Switch{
    private:
        textAlignment textAlign;
        
        SDL_Rect pos, textPos;

        SDL_Colour c_Fore, c_Back, c_Active;

        bool state;
        TTF_Font* font;
        const char* text;

    public:
        Switch(SDL_Rect pos, SDL_Colour Foreground, SDL_Colour Background, SDL_Colour Active, textAlignment textPos, TTF_Font* font, const char* textMsg);

        void updateLogic(Scene* event);

        void RenderText(SDL_Renderer* renderer);

        void Render(SDL_Renderer* renderer);
};

class OvalSwitch: Switch{
    public:
        void Render(SDL_Renderer* renderer);
}





#endif