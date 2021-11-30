#include "events.hpp"

Events::Events(const char* title, int windowWidth, int windowHeight){
    //Initiate SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Initiation Error: (Window): " << SDL_GetError() << std::endl;
    }
    //Init window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    if (window == NULL){
        std::cout << "Initiation Error: (Window): " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        std::cout << "Initiation Error: (renderer): " << SDL_GetError() << std::endl;
    }
    //Init SDL_TFF
    if (TTF_Init() < 0){
        std::cout << "Initiation Error: (TTF_Init): " << TTF_GetError() << std::endl;
    }
    //Initialize variables
    width = windowWidth; height = windowHeight;
    programState = true;

    //Initialize deltaTime
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
}

void Events::update(){
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            programState = false;
        }

        if (event.type == SDL_WINDOWEVENT){
            if (event.window.type == SDL_WINDOWEVENT_RESIZED){
                width = SDL_GetWindowSurface(window)->w;
                height = SDL_GetWindowSurface(window)->h;
            }
        }


    }
    //Update deltaTime
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = ((NOW - LAST)*1000/(float)SDL_GetPerformanceFrequency());

    //Swap buffers
    SDL_RenderPresent(renderer);
}


//Event getter functions
bool Events::getState(){
    return programState;
}