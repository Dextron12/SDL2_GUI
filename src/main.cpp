#include "gui.hpp"

int main(int argc, char* argv[]){
    Scene scene(800, 600, "test");
    Events events;

    while (scene.appState){
        SDL_SetRenderDrawColor(scene.renderer, 100, 149, 237, 255);
        SDL_RenderClear(scene.renderer);

        events.update(&scene);

        SDL_RenderPresent(scene.renderer);
    }


    return 0;
}