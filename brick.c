#include "brick.h"

int CountBricks(struct List *brickList) {
    int cnt = 0;
    struct BrickElem* e = brickList->firstBrick;
    while(e!=NULL) {
        cnt++;
        e = e->nextBrick;
    }
    return cnt;
}

void AddBrick(struct List *brickList, struct brick* brick) {
    struct BrickElem *brickElem = malloc(sizeof(struct BrickElem));
    brickElem->Elem = brick;
    brickElem->nextBrick = NULL;
    if (brickList->firstBrick == NULL){
        brickList->firstBrick = brickElem;
        return;
    }
    struct BrickElem* e = brickList->firstBrick;
    for(int i = 0; i < CountBricks(brickList)-1; i++) {
        e = e->nextBrick;
    }
    e->nextBrick = brickElem;
}

struct BrickElem* GetElemAtIndex(struct List *brickList, int index) {
    if(index < 0 || index > CountBricks(brickList)) {
        return NULL;
    }
    struct BrickElem* e = brickList->firstBrick;
    for(int i = 0; i < index; i++) {
        e = e->nextBrick;
    }
    return e;
}

void RemoveBrickAtIndex(struct List* brickList,int index) {
    if(index < 0 || index > CountBricks(brickList)) {
        return;
    }
    struct BrickElem* BrickDel = GetElemAtIndex(brickList,index);
    if(index==0) {
        brickList->firstBrick = GetElemAtIndex(brickList,1);
        free(BrickDel);
        return;
    } else if(index == CountBricks(brickList)-1){
        GetElemAtIndex(brickList,index-1)->nextBrick = NULL;
        free(BrickDel);
        return;
    }
    GetElemAtIndex(brickList,index-1)->nextBrick = GetElemAtIndex(brickList, index+1);
    free(BrickDel);
}

struct brick* CreateBrick(int x, int y, SDL_Texture **textures, int life) {
    struct brick* brick = malloc(sizeof (struct brick));
    brick->x = x;
    brick->y = y;
    brick->w = 50;
    brick->h = 30;
    brick->life = life;
    brick->texture = textures[10 + brick->life];
    return brick;
}

void InitBrickList(struct window *myWindow, struct List *brickList, int nbBricks, SDL_Texture **textures,int level) {
    /*Fonction qui permet d'initialiser les briques automatiquement en fonction du niveau*/
    int ligne = nbBricks / (myWindow->width/60) + 1;
    for(int i = 0; i < ligne; i++) {
        for(int j = 0; j < nbBricks - (i * myWindow->width/60 ); j++) {
            if(level != 10) {
                AddBrick(brickList, CreateBrick(j*60 + 5,i*40 + 60, textures,1 + (level/2) - i));
            } else {
                AddBrick(brickList, CreateBrick(j*60 + 5,i*40 + 60, textures,5));
            }
        }
    }
}