#include "gui.hpp"

Scene::Scene(int width, int height, const char* Title){
    //Init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "ERROR::INITIATION::SDL2" << std::endl;
        appState = false;
    } else {
        window = SDL_CreateWindow(Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, 0);

        //Error check
        if (window == NULL){
            std::cout << "ERROR:INITIATION::WINDOW" << std::endl;
            appState = false;
        }
        if (renderer == NULL){
            std::cout << "ERROR:INITIATION::RENDERER" << std::endl;
            appState = false;
        }

        //Init Image
        if (IMG_Init(IMG_INIT_PNG) == 0){
            std::cout << "ERROR::INITIATION::IMG" << std::endl;
            appState = false;
        } else {appState = true;}

        if (TTF_Init() < 0){
            std::cout << "ERROR::INITIATION::TTF" << std::endl;
            appState = false;
        } else {appState = true;}
    }
}



//Events class

void Events::update(Scene* scene) {
    while (SDL_PollEvent(&event)){
        //QUIT HANDLER
        if (event.type == SDL_QUIT){
            scene->appState = false;
        }

        //WINDOW HANDLER
        if (event.type == SDL_WINDOWEVENT){
            //RESIZE
            if(event.window.type == SDL_WINDOWEVENT_RESIZED){
                scene->windowSize.x = SDL_GetWindowSurface(scene->window)->w;
                scene->windowSize.y = SDL_GetWindowSurface(scene->window)->h;
            }
        }
    }
}
