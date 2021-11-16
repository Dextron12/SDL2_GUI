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

        //mouse
        SDL_Point p_mousePoint;
        bool b_mouseClick1; //Left
        bool b_mouseClick2; //Right
        bool b_mouseClick3; //Middle

        //keyboard
        const char* c_activeKey;
        bool b_escape;
        bool b_enter;
        bool b_lShift;
        bool b_rShift;

        void keyboardUpdate(SDL_Event* event);
        
    public:
        Events(); // Only required to init deltaTime
        void update();
        void reset();

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

        //keyboard
        const char* pressedKey();
        bool keyEscape();
        bool keyEnter();
        bool keyLShift();
        bool keyRShift();


};