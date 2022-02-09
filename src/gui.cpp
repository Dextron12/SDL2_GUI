#include "gui.hpp"

Scene::Scene(int width, int height, const char* Title){
    //Init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "ERROR::INITIATION::SDL2" << std::endl;
        events.appState = false;
    } else {
        window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, 0);

        //Error check
        if (window == NULL){
            std::cout << "ERROR:INITIATION::WINDOW" << std::endl;
            events.appState = false;
        }
        if (renderer == NULL){
            std::cout << "ERROR:INITIATION::RENDERER" << std::endl;
            events.appState = false;
        }

        //Init Image
        if (IMG_Init(IMG_INIT_PNG) == 0){
            std::cout << "ERROR::INITIATION::IMG" << std::endl;
            events.appState = false;
        } else {events.appState = true;}

        if (TTF_Init() < 0){
            std::cout << "ERROR::INITIATION::TTF" << std::endl;
            events.appState = false;
        } else {events.appState = true;}
    }
}



//Events class

void Events::update() {
    while (SDL_PollEvent(&event)){
        //QUIT HANDLER
        if (event.type == SDL_QUIT){
            appState = false;
        }

        //WINDOW HANDLER
        if (event.type == SDL_WINDOWEVENT){
            //RESIZE
            if(event.window.type == SDL_WINDOWEVENT_RESIZED){
                resizeWindow.x = SDL_GetWindowSurface(window);
            }
        }
    }
}
