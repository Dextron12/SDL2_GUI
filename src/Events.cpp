#include "Events.hpp"

Events::Events(int width, int height, std::string title){
    //Init sdl2
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        //Init window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        if (window == NULL){
            std::cout << "Initiation Error: " << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer == NULL){
            std::cout << "Initiation Error: " << SDL_GetError() << std::endl;
        }
        if (TTF_Init() != 0){
            std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        }
        if (IMG_Init(IMG_INIT_PNG) == 0){
            std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
        }

        //Initiate other variables here
        NOW = SDL_GetPerformanceCounter();
        LAST = 0;
        deltaTime = 0;

        windowSize.x = width; windowSize.y = height;

        b_quit = false; b_windowResize = false;


    } else {
        std::cout << "Failed to initate SDL2: " << SDL_GetError() << std::endl;
    }
}

void Events::update(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            b_quit = true;
        }

        if (event.type == SDL_WINDOWEVENT){
            if (event.window.type == SDL_WINDOWEVENT_RESIZED){
                //Get new width and height
                windowSize.x = SDL_GetWindowSurface(window)->w;
                windowSize.y = SDL_GetWindowSurface(window)->h;
            }
        }

        //Keyboard events
        //KeyState = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
        if (b_textInput == true){
            if (event.type == SDL_TEXTINPUT){
                c_textOutput.append(event.text.text);
            }

            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_BACKSPACE && c_textOutput.size() > 0){
                    //Remove char
                    c_textOutput.erase(c_textOutput.end()-1);
                }
            }
        }

        //Mouse events
        if (event.type == SDL_MOUSEMOTION){
            mouse.button = SDL_GetMouseState(&mouse.x, &mouse.y);
        }

    }
    //Update deltaTime.
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = ((NOW-LAST)/SDL_GetPerformanceFrequency())/1000;

}


bool Events::getAppState(){
    return b_quit;
}

SDL_Point Events::mousePos(){
    return SDL_Point{(int)mouse.x, (int)mouse.y};
}

int* Events::mouseState(){
    return &mouse.button;
}

char* Events::getTextOutput(){
    std::cout << c_textOutput << std::endl;
}

void Events::clearTextOutput(){
    c_textOutput.clear();
}

void Events::startTextInput(bool state){
    b_textInput = state;
}

