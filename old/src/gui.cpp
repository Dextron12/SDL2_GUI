#include "gui.hpp"

GUI::GUI(std::string windowTitle, int width, int height){
    //Init SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "Failed to init SDL: " << SDL_GetError() << std::endl;
    }
    //Init IMG
    if (IMG_Init(IMG_INIT_PNG) == 0){
        std::cout << "Failed to init IMG: " << IMG_GetError() << std::endl;
    }
    if (TTF_Init() < 0){
        std::cout << "Failed to init TTF: " << TTF_Init() << std::endl;
    }

    //Create window
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    if (window == NULL){
        std::cout << "Window initialization error: " << SDL_GetError() << std::endl;
    }

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        std::cout << "Renderer initialization error: " << SDL_GetError() << std::endl;
    }
}

void GUI::loadFont(const char* fontPath, int fontSize){
    TTF_Font* font;
    font = TTF_OpenFont(fontPath, fontSize);
    if (!font){
        std::cout << "Failed to open font: " << TTF_GetError() << std::endl;
    } else {
        this->font = font;
    }
}

TTF_Font* GUI::useFont(){
    return font;
}

void Primitives::FilledRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Color colour){
    //Set colour
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    //Draw rect
    SDL_RenderFillRect(renderer, &pos);
}

void Primitives::LineRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour){
    //Set Colour
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    //Draw rect
    SDL_RenderDrawRect(renderer, &pos);
}

void Primitives::FilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour){
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius -1;

    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

    while (offsety >= offsetx){
        SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (d >= 2*offsetx){
            d -= 2*offsetx + 1;
            offsetx += 1;
        } else if ( d < 2 * offsety - 1){
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void Primitives::LineCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour){
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

    while (offsety >= offsetx){
        SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (d >= 2 * offsetx){
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)){
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void Primitives::Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, std::string msg, SDL_Colour colour){
    //Create surface
    SDL_Surface* text = TTF_RenderText_Blended(font, msg.c_str(), colour);
    //grab width and height and assin to pos
    pos.w = text->w; pos.h = text->h;
    //COnvert to surface
    SDL_Texture* renderText = SDL_CreateTextureFromSurface(renderer, text);
    //Render text
    SDL_RenderCopy(renderer, renderText, NULL, &pos);
    //Free memory
    SDL_FreeSurface(text);
    SDL_DestroyTexture(renderText);
    
    
}

GUI::Form::Form(SDL_Rect pos, SDL_Colour background, SDL_Colour foreground, std::string msg){
    //set state to false.
    state = false;
    this->pos = pos;
    BG = background;
    FG = foreground;
    stateMsg = msg;
}

void GUI::Form::update(SDL_Renderer* renderer, TTF_Font* font, Events* event){
    Primitives::FilledRect(renderer, pos, BG);

    //Draw text(FG)
    if (!state || input.size() == 0){
        //No user input, render default text if any.
        if (stateMsg.size() > 0){
            Primitives::Text(renderer, font, SDL_Rect{pos.x+5, pos.y+(pos.h/2)}, stateMsg, FG);
            //This is doen so users can pass "" as stateMsg.
        }
    } else {
        //There is user input, lets render it
        Primitives::Text(renderer, font, SDL_Rect{pos.x+5, pos.y+(pos.h/2)}, input, FG);
    }

    //Handle user click
    if ( (pos.x+pos.w >= event->mousePos().x && event->mousePos().x >= pos.x) && (pos.y+pos.h >= event->mousePos().y && event->mousePos().y >= pos.y)){
        if (event->mouseBtn1() == true){
            //change state
            if (state == false){
                state = true;
            } else {
                state = false;
            }
        }
    }

    //Get key inout
    if (state == true){
        //std::cout << event->pressedKey() << std::endl;
    }

}
