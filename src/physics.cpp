#include "physics.hpp"

Events::Events(){
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
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

        //Update keyboard
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_ESCAPE:
                    b_escape = true;
                    std::cout << "activated escape btn" << std::endl;
                    break;
            }
        }

    }
    //Update deltaTime
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = ((NOW - LAST)*1000/(float)SDL_GetPerformanceFrequency());
}

void Events::keyboardUpdate(SDL_Event* event){
    if (event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym){
            case SDLK_a:
                if (b_lShift || b_rShift){
                    c_activeKey = "A";
                } else {
                    c_activeKey = "a";
                }
                
                break;
            case SDLK_b:
                c_activeKey = "b";
                break;
            case SDLK_c:
                c_activeKey = "c";
                break;
            case SDLK_d:
                c_activeKey = "d";
                break;
            case SDLK_e:
                c_activeKey = "e";
                break;
            case SDLK_f:
                c_activeKey = "f";
                break;
            case SDLK_g:
                c_activeKey = "g";
                break;
            case SDLK_h:
                c_activeKey = "h";
                break;
            case SDLK_i:
                c_activeKey = "i";
                break;
            case SDLK_j:
                c_activeKey = "j";
                break;
            case SDLK_k:
                c_activeKey = "k";
                break;
            case SDLK_l:
                c_activeKey = "l";
                break;
            case SDLK_m:
                c_activeKey = "m";
                break;
            case SDLK_n:
                c_activeKey = "n";
                break;
            case SDLK_o:
                c_activeKey = "o";
                break;
            case SDLK_p:
                c_activeKey = "p";
                break;
            case SDLK_q:
                c_activeKey = "q";
                break;
            case SDLK_r:
                c_activeKey = "r";
                break;
            case SDLK_s:
                c_activeKey = "s";
                break;
            case SDLK_t:
                c_activeKey = "t";
                break;
            case SDLK_u:
                c_activeKey = "u";
                break;
            case SDLK_v:
                c_activeKey = "v";
                break;
            case SDLK_w:
                c_activeKey = "w";
                break;
            case SDLK_x:
                c_activeKey = "x";
                break;
            case SDLK_y:
                c_activeKey = "y";
                break;
            case SDLK_z:
                c_activeKey = "z";
                break;

            //Modifier keys
            case SDLK_ESCAPE:
                b_escape = true;
                //std::cout << "escape" << std::endl;
                break;
            case SDLK_LSHIFT:
                b_lShift = true;
                //std::cout << "Left Shift" << std::endl;
                break;
            case SDLK_RSHIFT:
                b_rShift = true;
                //std::cout << "Right Shift" << std::endl;
                break;
            case SDLK_KP_ENTER:
                //std::cout << "Enter" << std::endl;
                b_enter = true;
                break; 

            //Numbers (0-9)
            case SDLK_0:
                c_activeKey = "0";
                break;
            case SDLK_1:
                c_activeKey = "1";
                break;
            case SDLK_2:
                c_activeKey = "2";
                break;
            case SDLK_3:
                c_activeKey = "3";
                break;
            case SDLK_4:
                c_activeKey = "4";
                break;
            case SDLK_5:
                c_activeKey = "5";
                break;
            case SDLK_6:
                c_activeKey = "6";
                break;
            case SDLK_7:
                c_activeKey = "7";
                break;
            case SDLK_8:
                c_activeKey = "8";
                break;
            case SDLK_9:
                c_activeKey = "9";
                break;

        }
    }
}


void Events::reset(){
    b_resize = false;

    //mouse
    b_mouseClick1 = false;
    b_mouseClick2 = false;
    b_mouseClick3 = false;

    //keyboard
    //NO NEED TO CLEAR c_activeKey!
    b_escape = false;
    b_enter = false;
    b_lShift = false;
    b_rShift = false;
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

const char* Events::pressedKey(){
    return c_activeKey;
}

bool Events::keyEscape(){
    return b_escape;
}

bool Events::keyEnter(){
    return b_enter;
}

bool Events::keyLShift(){
    return b_lShift;
}

bool Events::keyRShift(){
    return b_rShift;
}