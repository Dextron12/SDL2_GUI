#include <Gui.hpp>

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


//Switch Classes

//Rectanglar switch
rectSwitch::rectSwitch(SDL_Rect pos, SDL_Colour back, SDL_Colour fore, SDL_Colour active, TTF_Font* font, std::string msg){
    this->pos = pos;
    c_fore = fore;
    c_back = back;
    c_active = active;
    state = false;
    this->font = font;
    s_msg = msg;
}

void rectSwitch::update(SDL_Renderer* renderer, Mouse mouse){
    //Draw static background
    Primitives::FilledRect(renderer, pos, c_back);
    Primitives::FilledCircle(renderer, c_back, pos.x, pos.y, pos.h/2); //Left corner
    Primitives::FilledCircle(renderer, c_back, pos.x+pos.w, pos.y, pos.h/2); //Right corner

    //Draw switch(25% of width of switch) depending on state
    switch (state){
        case false:
            //Draw switch on the left.
            Primitives::FilledRect(renderer, SDL_Rect{pos.x+5, pos.y+5, pos.w/4, pos.h-10}, c_fore);
            break;
        case true:
            //Draw switch on the right.
            Primitives::FilledRect(renderer, SDL_Rect{(pos.x+pos.w)-5, pos.y+5, pos.w/4, pos.h-10}, c_active); 
    }

    //Logic
    if ( (pos.x+pos.w >= mouse.x && mouse.x >= pos.x) && (pos.y+pos.h >= mouse.y && mouse.y >= pos.y)){
        if (mouse.button && SDL_BUTTON_LEFT != 0){
            //change state of switch
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
        }
    }
}

//Oval switch
ovalSwitch::ovalSwitch(SDL_Rect pos, SDL_Colour back, SDL_Colour fore, SDL_Colour active, TTF_Font* font, std::string msg){
    this->pos = pos;
    c_fore = fore;
    c_back = back;
    c_active = active;
    this->font = font;
    msg = msg;
    radius = pos.h/2;

    state = false;

}

void ovalSwitch::update(SDL_Renderer* renderer, Mouse mouse){
    //Draw static background
    Primitives::FilledRect(renderer, pos, c_back);

    //Draw switch
    switch (state){
        case true:
            //Draw switch on the right
            Primitives::FilledCircle(renderer, c_active, (pos.x-radius)-5, pos.y+5, radius);
            break;
        case false:
            //Draw switch on the left
            Primitives::FilledCircle(renderer, c_fore, pos.x+5, pos.y+5, radius);
            break;
    }

    //Logic
    if ( (pos.x+pos.w >= mouse.x && mouse.x >= pos.x) && (pos.y+pos.h >= mouse.y && mouse.y >= pos.y)){
        if (mouse.button && SDL_BUTTON_LEFT != 0){
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
        }
    }
}


//Button classes


Button::Button(SDL_Rect pos, SDL_Colour back, SDL_Colour fore, SDL_Colour active, TTF_Font* font, std::string msg){
    this->pos = pos;
    c_back = back;
    c_fore = fore;
    c_active = active;
    this->font = font;
    s_msg = msg;

    state = false;
}

void Button::update(SDL_Renderer* renderer, Mouse mouse){
    if ( (pos.x+pos.w >= mouse.x && mouse.x >= pos.x) && (pos.y+pos.h >= mouse.y && mouse.y >= pos.y)){
        if (mouse.button && SDL_BUTTON_LEFT != 0){
            //Draw active button
            Primitives::FilledRect(renderer, pos, c_active);
            //change state
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
        } else {
            //Draw inactive state
            Primitives::FilledRect(renderer, pos, c_back);
        }
    }
}

RndButton::RndButton(SDL_Rect pos, SDL_Colour fore, SDL_Colour back, SDL_Colour active, TTF_Font* font, std::string msg){
    this->pos = pos;
    c_fore = fore;
    c_back = back;
    c_active = active;
    this->font = font;
    s_msg = msg;

    state = false;
}

void RndButton::update(SDL_Renderer* renderer, Mouse mouse){
    if ( (pos.x+pos.w >= mouse.x && mouse.x >= pos.x) && (pos.y+pos.w >= mouse.y && mouse.y >= pos.y)){
        //Draw switch
        Primitives::FilledRect(renderer, pos, c_back);
        Primitives::FilledCircle(renderer, c_back, pos.x, pos.y, pos.h/2);          //Left border
        Primitives::FilledCircle(renderer, c_back, pos.x+pos.w, pos.y, pos.h/2);    //Right Border
        if (mouse.button && SDL_BUTTON_LEFT != 0){
            //Change state
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
        }
    } else {
        Primitives::FilledRect(renderer, pos, c_active);
        Primitives::FilledCircle(renderer, c_active, pos.x, pos.y, pos.h/2);          //Left border
        Primitives::FilledCircle(renderer, c_active, pos.x+pos.w, pos.y, pos.h/2);    //Right Border
    }
}

RadButton::RadButton(int x, int y, int radius, SDL_Colour fore, SDL_Colour back, SDL_Colour active, TTF_Font* font, std::string msg){
    this->x = x; this->y = y; this->radius = radius;
    c_fore = fore;
    c_back = back;
    c_active = active;
    this->font = font;
    s_msg = msg;
}

void RadButton::update(SDL_Renderer* renderer, Mouse mouse){
    //Draw static background
    Primitives::FilledCircle(renderer, c_back, x, y, radius);

    if ( (x+(radius*2) >= mouse.x && mouse.x >= x) && (y+(radius*2) >= mouse.y && mouse.y >= y)){
        //Draw active inner circle
        Primitives::FilledCircle(renderer, c_active, x+4, y+4, radius-8);
        //Check state
        if (mouse.button && SDL_BUTTON_LEFT != 0){
            switch (state){
                case true:
                    state = false;
                    break;
                case false:
                    state = true;
                    break;
            }
        }
    }

    //Draw inner circle if state is active
    if (state == true){
        Primitives::FilledCircle(renderer, c_active, x+4, y+4, radius-8);
    }
}


//Form class

Form::Form(SDL_Rect pos, SDL_Colour Fore, SDL_Colour Back, SDL_Colour textColour, TTF_Font* font){
    state = false; // Deactivates text reciver on init
    this->pos = pos;

    c_fore = Fore;
    c_back = Back;
    c_text = textColour;
    this->font = font;
}

void Form::update(SDL_Renderer* renderer, std::string keyInput){
    //Draw background first.
    Primitives::FilledRect(renderer, pos, c_back);

    //Manually draw Text(due to precise positioning its bette rto manually do it)
    //Set render colour of text.
    SDL_SetRenderDrawColor(renderer, c_text.r, c_text.g, c_text.b, c_text.a);
    //Render inactive text if no keyInfo provided.
    if (keyInput.size() == 0){
        //No input detected, render inactive text
    }
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, keyInput.c_str(), c_text);
    posText.w = textSurface->w; posText.h = textSurface->h;
    //Convert to texture
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    //Draw and position text
    switch (pos_text){
        case Outer_Left:
            //Offset text before pos.x
            posText.x = pos.x-posText.w-10;
            posText.y = pos.y+(pos.h/2)-posText.h;
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
        case Outer_Right:
            //Offset text after pos.x+pos.w
            posText.x = pos.x+pos.w+posText.w+10;
            posText.y = pos.y+(pos.h/2)-posText.h;
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
        case Top:
            //Allign to top center of form.
            posText.x = pos.x+((pos.w/2)-(posText.w/2));
            posText.y = pos.y-posText.h-10;
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
        case Bottom:
            //Allin center bottom.
            posText.x = pos.x+(pos.w/2)-(posText.w/2);
            posText.y = pos.x+pos.h+posText.h+10;
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;

        case Inner_Left:
            //10px in from left border
            posText.x = pos.x+10;
            posText.y = pos.y+(pos.h/2)-posText.h;
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
        case Centered:
            //align with center of form.
            posText.x = pos.x+(pos.w/2)-(posText.w/2);
            posText.y = pos.y+(pos.h/2)-(posText.h/2);
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
        case Inner_Right:
            //align end of text to 10px before right border.
            posText.x = pos.x+(pos.w-posText.w-10);
            posText.y = pos.y+(pos.h/2)+(posText.y/2);
            //Render
            SDL_RenderCopy(renderer, text, NULL, &posText);
            break;
    }
    //Free text memory
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);

}