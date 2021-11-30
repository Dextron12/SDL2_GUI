#include <iostream>

#include <SDL2/SDL.h>


#include "events.hpp"
#include "gui.hpp"

int main(int argc, char* argv[]){
    Events event("Test", 800, 600);

    while (event.getState()){
        Primitives::setColour(event.renderer, SDL_Colour{140,140,140});
        
        event.update();
    }
    return 0;
}