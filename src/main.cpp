#include "gui.hpp"


int main(int argc, char *argv[]){
    GUI scene("GUI_example", 800, 600);
    scene.loadFont("C:\\Windows\\Fonts\\Arial.ttf", 14);

    GUI::Form form(SDL_Rect{50,300,700,30}, SDL_Colour{105,105,105,255}, SDL_Colour{0,0,0,255}, "Username");

    while (!scene.events.getActiveWindowState()){
        scene.events.update();
        SDL_SetRenderDrawColor(scene.renderer, 140, 140, 140, 255);
        SDL_RenderClear(scene.renderer);

        scene.FilledRect(scene.renderer, SDL_Rect{200,200,100,100}, SDL_Colour{160,150,20,255});
        scene.LineRect(scene.renderer, SDL_Rect{50,50,50,50}, SDL_Colour{255,255,255,255});
        scene.FilledCircle(scene.renderer, 150, 150, 15, SDL_Colour{40,60,140,255});
        scene.LineCircle(scene.renderer, 250, 100, 25, SDL_Colour{40,60, 140, 255});
        scene.Text(scene.renderer, scene.useFont(), SDL_Rect{80,300}, "Hello World", SDL_Colour{40,60,140,255});

        form.update(scene.renderer, scene.useFont(), &scene.events);
        


        //Stop drawing
        SDL_RenderPresent(scene.renderer);
        scene.events.reset();
    }
    return 0;

}