#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define SCR_W 800
#define SCR_H 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;
static SDL_Surface *text = NULL;
static SDL_Texture *text_texture = NULL;

static void panic_and_abort(const char *title, const char *message){
    fprintf(stderr, "PANIC: %s ... %s\n", title, message);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
    SDL_Quit();
    exit(1);
}

int main(int argc, char **argv){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        panic_and_abort("SDL_Init Failed!", SDL_GetError());
    }

    window = SDL_CreateWindow("Protome", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, 0);
    if(window == NULL){
        panic_and_abort("SDL_CreateWindow Failed!", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        panic_and_abort("SDL_CreateWindow Failed!", SDL_GetError());
    }


    if(TTF_Init() != 0){
        panic_and_abort("TTF_Init Failed!", TTF_GetError());
    }

    font = TTF_OpenFont("FreeSans.ttf", 24);
    if(font == NULL){
        panic_and_abort("TTF_OpenFont Failed!", TTF_GetError());
    }


    SDL_Color color = { 0, 0, 0, 0};


    text = TTF_RenderText_Solid(font, "Hello Ash", color);

    if(text == NULL){
        panic_and_abort("TTF_OpenFont Failed!", TTF_GetError());
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect dst = { 0, 0, 500, 500};


    SDL_bool is_running = SDL_TRUE;

    while(is_running){

        //  Handle Input
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                is_running = SDL_FALSE;
            }
            if(e.type == SDL_MOUSEMOTION){
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
            }
            if(e.type == SDL_MOUSEBUTTONUP){
            }
        }


        //  Update Update

        //  Draw
        //      Reset Frame 
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);


        //      Draw things
        SDL_RenderCopy(renderer, text_texture, NULL, &dst);


        //      Buffer swap
        SDL_RenderPresent(renderer);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
    SDL_Quit();
    return 0;
}

