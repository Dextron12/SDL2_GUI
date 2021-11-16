//A simple GUI header
//Can render basic shapes (rect, square, circle, line)
//Render widgets(forms, push button, radio buton, drop downs, msg popups)
//Author: Dextron12
//Begin date: 12//11/21

#pragma once

#include <iostream>

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

#include "physics.hpp"

class Primitives{
    public:
        static void FilledRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void LineRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour);
        static void FilledCircle(SDL_Renderer*, int x, int y, int radius, SDL_Colour);
        static void LineCircle(SDL_Renderer*, int x, int y, int radius, SDL_Color);
        static void Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, std::string msg, SDL_Colour colour);
};

/*class Form: public Primitives{
    private:
        bool active;

        SDL_Rect pos;
        SDL_Colour colour;

    public:
        Form(SDL_Rect pos, SDL_Colour colour);

        void update(SDL_Renderer* renderer, TTF_Font* font, Events* event);
        void setState(bool state);
};*/



class GUI: public Primitives{
    private:
        int width, height;

        bool programState;
        TTF_Font* font;

    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Events events;
        
        

        GUI(std::string windowTitle, int width, int height);
        void createForm(SDL_Rect pos, SDL_Colour colour);

        void loadFont(const char* fontPath, int fontSize);
        TTF_Font* useFont();

        class Form{
            private:
                bool state;

                SDL_Rect pos;
                SDL_Colour BG;
                SDL_Colour FG;
                std::string stateMsg;
                std::string input;

            public:
                Form(SDL_Rect pos, SDL_Colour background, SDL_Colour foreground, std::string msg);

                void update(SDL_Renderer* renderer, TTF_Font* font, Events* event);

                //Getters
                bool getState();
        };
        

};