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

    //Initiate other variables
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
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

        //Mouse
        if (event.type == SDL_MOUSEMOTION){
            scene->mouseButtons = SDL_GetMouseState(&scene->mousePos.x, &scene->mousePos.y);
        }


    }
    //Update deltaTime
    scene->LAST = scene->NOW;
    scene->NOW = SDL_GetPerformanceCounter();
    scene->deltaTime = ((scene->NOW - scene->LAST)/SDL_GetPerformanceFrequency())/1000;
}


//Primitives
void Primitives::FilledRect(SDL_Renderer* renderer, SDL_FRect pos, SDL_Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRectF(renderer, &pos);
}

void Primitives::Rect(SDL_Renderer* renderer, SDL_FRect pos, SDL_Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawRectF(renderer, &pos);
}

void Primitives::Line(SDL_Renderer* renderer, SDL_FPoint point1, SDL_FPoint point2, SDL_Colour colour, int thickness){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawLineF(renderer, point1.x, point1.y, point2.x, point2.y);
}

void Primitives::FilledCircle(SDL_Renderer* renderer, SDL_Colour colour, int x, int y, int radius){
    int offsetx, offsety, d;
    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);

    while (offsety >= offsetx){
        SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (d >= 2 * offsetx){
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * offsety - 1){
            d += 2 * offsety - 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void Primitives::Circle(SDL_Renderer* renderer, SDL_Colour colour, int x, int y, int radius){
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
        } else if ( d < 2 * (radius - offsety)){
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void Primitives::Text(SDL_Renderer* renderer, SDL_Rect pos, TTF_Font* font, SDL_Colour colour, std::string msg){
    SDL_Surface* surface = TTF_RenderText_Blended(font, msg.c_str(), colour);
    pos.w = surface->w; pos.h = surface->h;
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
    //Render Text
    SDL_RenderCopy(renderer, text, NULL, &pos);
    //Free memory
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
}


//Overloaded Primitive functions
void Primitives::FilledRect(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(renderer, &pos);
}

void Primitives::Line(SDL_Renderer* renderer, SDL_Point point1, SDL_Point point2, SDL_Colour colour, int thickness){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
}


//Switches
Switch::Switch(SDL_Rect pos, SDL_Colour Foreground, SDL_Colour Background, SDL_Colour Active, textAlignment textPos, TTF_Font* font, const char* textMsg){
    //Assign vars
    this->pos = pos;
    textAlign = textPos;
    this->font = font;
    text = textMsg;

    c_Fore = Foreground;
    c_Back = Background;
    c_Active = Active;

    state = true;
}

void Switch::updateLogic(Scene* scene){
    //Check if mouse cursor is over switch
    if ( (pos.x+pos.w >= scene->mousePos.x && scene->mousePos.x >= pos.x) && (pos.y+pos.h >= scene->mousePos.y && scene->mousePos.y >= pos.y) ){
        //If left click, change form state
        if (scene->mouseButtons && SDL_BUTTON_LMASK){
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
            //Let the render function draw active & inactive states
        }
    }
}

void Switch::Render(SDL_Renderer* renderer){
    //Draw background
    Primitives::FilledRect(renderer, pos, c_Back);

    //Draw slider
    if (state == true){
        //Draw slider to right
        Primitives::FilledRect(renderer, SDL_Rect{pos.x+(pos.w-(pos.w/4)), pos.y+5, pos.w/4, pos.h-10}, c_Active);
    } else {
        Primitives::FilledRect(renderer, SDL_Rect{pos.x+5,pos.y+5,pos.w-10,pos.h-10}, c_Fore);
    }

    //Render text last
    RenderText(renderer);
}

void Switch::RenderText(SDL_Renderer* renderer){
    //1. Create a surface, fill with text
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, c_Fore);
    //2. Get textSurface width & height.
    textPos.w = textSurface->w;
    textPos.h = textSurface->h;
    //Render text depending on textAlign var
    switch (textAlign){
        case I_LEFT:
            textPos.x = pos.x+5;
            textPos.y = pos.y+(textPos.h/2);
        case I_RIGHT:
            textPos.x = pos.x+(pos.w-textPos.w-5);
            textPos.y = pos.y+(textPos.h/2);
        case CENTER:
            textPos.x = pos.x+((pos.w/2)-(textPos.w/2));
            textPos.y = pos.y+(textPos.h/2);
        
        case TOP:
            textPos.x = pos.x+((pos.w/2)-(textPos.w/2));
            textPos.y = pos.y-textPos.h-5;
        case O_LEFT:
            textPos.x = pos.x-textPos.w-5;
            textPos.y = pos.y+(textPos.h/2);
        case O_RIGHT:
            textPos.x = pos.x+pos.w+5;
            textPos.y = pos.y+(textPos.h/2);
    //Convert to texture then render.
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textPos);
    //Free memory
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    }
}

void OvalSwitch::Render(SDL_Renderer* renderer){
    //Draw background
    Primitives::FilledRect(renderer, pos, c_Back);
}