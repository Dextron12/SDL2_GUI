#pragma once

#include <iostream>

#define SDL_MAIN_HANDLED 

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_image.h>

#include <commons.hpp>


class Events{
    private:
        SDL_Event event;

        double NOW, LAST;

        bool b_windowResize, b_quit;

        //Keyboard
        bool b_logKeys;
        std::string str_key;

        //Mouse
        Mouse mouse;

    public:
        float deltaTime;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Point windowSize;
        
        Events(int width, int height, std::string title);
        
        void update();

        void setKeyboardState(bool state);

        //Getters

        bool getAppState();
        
        std::string getKeyChar();

        SDL_Point mousePos();
        int* mouseState();
        /*
        [0  0   0]
        Left Middle Right buttons
        0 Not active
        1 Held
        2 Released
        */
};

