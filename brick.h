#ifndef BRICKBREAKER_BRICK_H
#define BRICKBREAKER_BRICK_H

#endif //BRICKBREAKER_BRICK_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

struct window {
    int width;
    int height;
};

struct color {
    int r;
    int g;
    int b;
};

struct brick {
    int x;
    int y;
    int w;
    int h;
    int life;

    SDL_Texture *texture;
};

struct BrickElem{
    struct brick* Elem;
    struct BrickElem* nextBrick;
};

struct List{
    struct BrickElem* firstBrick;
};

int CountBricks(struct List *brickList);

void AddBrick(struct List *brickList, struct brick* brick);

struct BrickElem* GetElemAtIndex(struct List *brickList, int index);

void RemoveBrickAtIndex(struct List* brickList,int index);

struct brick* CreateBrick(int x, int y, SDL_Texture **textures, int life);

void InitBrickList(struct window *myWindow, struct List *brickList, int nbBricks, SDL_Texture **textures, int level);