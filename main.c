#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define SCALE 150

#define SCR_W 16*SCALE
#define SCR_H 9*SCALE

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;
static SDL_Surface *text;
static SDL_Texture *text_texture[127];


static char buffer[1024];
static int cursor = 0;
static int buflen = 0;


static void panic_and_abort(const char *title, const char *message){
    fprintf(stderr, "PANIC: %s ... %s\n", title, message);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, window);
    TTF_CloseFont(font);
    TTF_Quit();
    char c;
    for(c = 0; c < 95; ++c){
        SDL_DestroyTexture(text_texture[c]);
    }
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

    int fontsize = 32;

    font = TTF_OpenFont("FreeSans.ttf", fontsize);

    if(font == NULL){
        panic_and_abort("TTF_OpenFont Failed!", TTF_GetError());
    }

    SDL_Color color = { 0, 0, 0, 0};

    char c;
    char cb[2];
    cb[1] = '\0';
    for(c = 0; c < 95; ++c){
        cb[0] = ' ' + c;
        text = TTF_RenderText_Solid(font, cb, color);
        text_texture[c] = SDL_CreateTextureFromSurface(renderer, text);
        SDL_FreeSurface(text);
    }

    memset(buffer, 0, 1024);
    int dstx = SCR_W/2;
    int dsty = 0;

    SDL_Rect dst = { dstx, dsty, fontsize, fontsize};
    SDL_Rect dstbox = { dstx, dsty, SCR_W - dstx, SCR_H - dsty};

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
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym >= ' ' && e.key.keysym.sym <= '~'){
                    printf("%c - Pressed\n", e.key.keysym.sym);
                    if(cursor == buflen){
                        buffer[cursor] = (char)e.key.keysym.sym;
                        cursor++;
                        buflen++;
                    }
                }
                if(e.key.keysym.sym == SDLK_BACKSPACE){
                    buffer[cursor] = '\0';
                    cursor--;
                    buflen--;
                }
            }
        }

        //  Update Update

        //  Draw
        //      Reset Frame 
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
    
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x90, 0x90, 0xFF);
        SDL_RenderFillRect(renderer, &dstbox);

        //      Draw things
        int i;
        for(i = 0; i < buflen; ++i){
            if((i % ((SCR_W - dstx)/fontsize)) == 0){
                dst.x = dstx;
                dst.y += fontsize;
            }else{
                dst.x = dst.x + dst.w;
            }
            SDL_RenderCopy(renderer, text_texture[buffer[i] - ' '], NULL, &dst);
        }
        dst.x = dstx;
        dst.y = dsty;
        


        //      Buffer swap
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(text);
    for(c = 0; c < 95; ++c){
        SDL_DestroyTexture(text_texture[c]);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

