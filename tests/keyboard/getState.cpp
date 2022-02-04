#include <stdio.h>

#include <SDL2\SDL.h>

int main(int argc, char* argv[]){
    //Init SDL2
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    int width, height;
    bool state;

    unsigned int* keys;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow("Keyboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, 0);
    }

    while (state){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                state = false;
            }

        }

        //Keyboard
    
    }


}