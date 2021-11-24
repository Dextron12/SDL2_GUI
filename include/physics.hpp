//A physics and events engine
//Author: Dextron12
//Begin date: 12/11/21

#pragma once

#include <SDL2\SDL.h>
#include <iostream>


class Events{
    private:
        SDL_Event event;

        //DeltaTime
        float NOW, LAST, deltaTime;


        //booleans
        bool b_quit;
        bool b_resize;

        //keyboard
        bool b_lShift;
        bool b_rShift;
        bool b_escape;
        bool b_return;
        std::string activeChar;
        char* keyChar; //WARNING: ONLY USED TO STORE event.text.text INPUT, SHOULD NOT BE EXTERNERLY USED. oNLY USED PROVIDED PUBLIC FUNCTIONS!

        //mouse
        SDL_Point p_mousePoint;
        bool b_mouseClick1; //Left
        bool b_mouseClick2; //Right
        bool b_mouseClick3; //Middle


        void keyboardUpdate(SDL_Event* event);
        
    public:
        Events(); // Only required to init deltaTime
        void update();

        //getters

        //window
        bool getActiveWindowState();
        bool getResizeWindowState();
        float getDeltaTime();

        //mouse
        SDL_Point mousePos();
        bool mouseBtn1();
        bool mouseBtn2();
        bool mosueBtn3();


};