#include "gui.hpp"

int main(int argc, char* argv[]){
    Scene scene(800, 600, "test");

    while (scene.events.appState){
        scene.events.update();

        SDL_SetRenderDrawColor(scene.renderer, 39, 58, 93, 255);
        SDL_RenderClear(scene.renderer);

        SDL_RenderPresent(scene.renderer);
    }
}