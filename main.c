#include <stdio.h>
#include "SDL2/SDL.h"

#define SCR_W 1600
#define SCR_H 900

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


static void panic_and_abort(const char *title, const char *message){
    fprintf(stderr, "PANIC: %s ... %s\n", title, message);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, window);
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


        //      Buffer swap
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}

