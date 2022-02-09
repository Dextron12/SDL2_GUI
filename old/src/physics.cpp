#include "physics.hpp"


Events::Events(){
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
    SDL_StartTextInput();
}
void Events::keyboardUpdate(SDL_Event* event){
    //update modifers first!
    if (event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym){
            case SDLK_LSHIFT:
                b_lShift = true;
                break;
            case SDLK_RSHIFT:
                b_lShift = true;
                break;
            case SDLK_ESCAPE:
                b_escape = true;
                break;
            case SDLK_RETURN:
                b_return = true;
                break;

            //numbers
            case SDLK_0:
                activeChar = "0";
                break;
            case SDLK_1:
                activeChar = "1";
                break;
            case SDLK_2:
                activeChar = "2";
                break;
            case SDLK_3:
                activeChar = "3";
                break;
            case SDLK_4:
                activeChar = "4";
                break;
            case SDLK_5:
                activeChar = "6";
                break;
            case SDLK_6:
                activeChar = "6";
                break;
            case SDLK_7:
                activeChar = "7";
                break;
            case SDLK_8:
                activeChar = "8";
                break;
            case SDLK_9:
                activeChar = "9";
                break;

            //Special chars
            case SDLK_AMPERSAND:
                activeChar = "&";
                break;
            case SDLK_ASTERISK:
                activeChar = "*";
                break;
            case SDLK_AT:
                activeChar = "@";
                break;
            case SDLK_CARET:
                activeChar = "^";
                break;
            case SDLK_COLON:
                activeChar = ":";
                break;
            case SDLK_DOLLAR:
                activeChar = "$";
                break;
            case SDLK_EXCLAIM:
                activeChar = "!";
                break;
            case SDLK_GREATER:
                activeChar = ">";
                break;
            case SDLK_LESS:
                activeChar = "<";
                break;
            case SDLK_HASH:
                activeChar = "#";
                break;
            case SDLK_LEFTPAREN:
                activeChar = "(";
                break;
            case SDLK_PERCENT:
                activeChar = "%";
                break;
            case SDLK_PLUS:
                activeChar = "+";
                break;
            case SDLK_QUESTION:
                activeChar = "?";
                break;
        }
    }
}

void Events::update(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            b_quit = true;
        }

        if (event.type == SDL_WINDOWEVENT){
            if (event.window.event == SDL_WINDOWEVENT_RESIZED){
                b_resize = true;
            }
        }

        if (event.type == SDL_MOUSEMOTION){
            SDL_GetMouseState(&p_mousePoint.x, &p_mousePoint.y);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.button == SDL_BUTTON_LEFT){
                b_mouseClick1 = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT){
                b_mouseClick2 = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT){
                b_mouseClick3 = true;
            }
        }

        if (event.type == SDL_MOUSEBUTTONUP){
            if (event.button.button == SDL_BUTTON_LEFT){
                b_mouseClick1 = false;
            }
        }
        
        //keyboardUpdate(&event);
        if (event.type == SDL_KEYDOWN){
            std::cout << event.key.keysym.scancode << std::endl;
        }

    }
    //Update deltaTime
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = ((NOW - LAST)*1000/(float)SDL_GetPerformanceFrequency());
}



//Event Getter Functions
bool Events::getActiveWindowState(){
    return b_quit;
}

bool Events::getResizeWindowState(){
    return b_resize;
}

float Events::getDeltaTime(){
    return deltaTime;
}

SDL_Point Events::mousePos(){
    return p_mousePoint;
}

bool Events::mouseBtn1(){
    return b_mouseClick1;
}

bool Events::mouseBtn2(){
    return b_mouseClick2;
}

bool Events::mosueBtn3(){
    return b_mouseClick3;
}

