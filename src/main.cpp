#include <iostream>

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "Events.hpp"

int main(int argc, char* argv[]){
    Events event(800, 600, "test");

    while (!event.getAppState()){
        event.update();
        SDL_SetRenderDrawColor(event.renderer, 140,140,140,255);
        SDL_RenderClear(event.renderer);


        SDL_RenderPresent(event.renderer);
    }
    return 0;
}