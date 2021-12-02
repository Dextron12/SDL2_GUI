#include "gui.hpp"

void Primitives::setColour(SDL_Renderer* renderer, SDL_Colour colour){
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255); //<--- Intentionlly ignore passed Alpha value!
    SDL_RenderClear(renderer);
}

void Primitives::Rectangle(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour){
	//Set colour
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255); //<--- ingore alpha
	//Render rect
	SDL_RenderFillRect(renderer, &pos);
}

void Primitives::Circle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour){
	int offsetx, offsety, d;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;

	while (offsety >= offsetx){
		SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
    SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
    SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
	  SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

		if (d >= 2*offsetx){
			d -= 2*offsetx+1;
			offsetx += 1;
		} else if (d < 2 * offsety - 1){
			d += 2 * offsety - 1;
			offsety -= 1;
		} else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}
}

void Primitives::Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect pos, SDL_Colour colour, char* msg){
	//Create surface
	SDL_Surface* text = TTF_RenderText_Blended(font, msg, colour);
	if (text == NULL){
		std::cout << "Text Error(SURFACE): " << TTF_GetError() << std::endl;
	}
	//Get rect width and height
	pos.w = text->w; pos.h = text->h;
	//Convert to texture adn render
	SDL_Texture* ren = SDL_CreateTextureFromSurface(renderer, text);
	SDL_RenderCopy(renderer, ren, NULL, &pos);
	//Free memory!
	SDL_DestroyTexture(ren);
	SDL_FreeSurface(text);
}

TTF_Font* Primitives::loadFont(std::string path){
	TTF_Font* font = TTF_OpenFont(path.c_str(), 16);
	return font;
}

void Primitives::lineRectangle(SDL_Renderer* renderer, SDL_Rect pos, SDL_Colour colour){
	//Set colour
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
	//Draw rect
	SDL_RenderDrawRect(renderer, &pos);
}

void Primitives::lineCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Colour colour){
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


void TextInput::enableInput(){
	//First enable text input
	SDL_StartTextInput();
	//Change var state
	activeState = true;
}

void TextInput::disableInput(){
	SDL_StopTextInput();
	activeState = false;
}

void TextInput::update(SDL_Event event){
	switch (event.type)
	{
	case SDL_TEXTINPUT:
		strcat(text, event.text.text);
		break;
	
	default:
		break;
	}
}

char* TextInput::getText(){
	if (activeState){
		return text;
	} else {
		//text input not active, return NULL.
		return NULL;
	}
}

