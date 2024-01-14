#include "menu.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTf_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              1440, 810, SDL_WINDOW_SHOWN);

    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr,"Erreur SDL_Init_Audio : %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    GameloopRender(renderer,window);

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}