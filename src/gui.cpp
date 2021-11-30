#include "gui.hpp"

void Primitives::setColour(SDL_Renderer* renderer, SDL_Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255); //<--- Intentionlly ignore passed Alpha value!
    SDL_RenderClear(renderer);
}