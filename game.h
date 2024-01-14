#ifndef BRICKBREAKER_GAME_H
#define BRICKBREAKER_GAME_H

#endif //BRICKBREAKER_GAME_H

#include "brick.h"

struct player {
    int x;
    int y;
    int w;
    int h;
    int speed;
    double inertie; /* [0;1] */
    bool right;
    bool left;

    SDL_Texture *texture;
};

struct ball {
    double x;
    double y;
    int w;
    int h;
    double speedX;
    double speedY;

    SDL_Texture *texture;
};

void MovePlayer(struct player *player, struct window *window);

void MoveBall(struct ball *ball, struct window *window);

bool RemoveLife(struct ball *ball, struct window *window);

void DisplayBricks(SDL_Renderer *renderer, struct List *brickList);

void DisplayText(SDL_Renderer *renderer, SDL_Rect *textRect, SDL_Texture *texture);

void DisplayLife(SDL_Renderer *renderer, SDL_Texture *texture, int life);

void DisplayBackground(SDL_Renderer *renderer, SDL_Texture *texture);

int FindTextureIndex(SDL_Texture *textures[29], SDL_Texture *currentTexture);

bool MouseOnRect(int mouseX, int mouseY, SDL_Rect *rect);

bool FocusOnRect(SDL_Rect *rect, int mouseX, int mouseY, bool oversized, struct window window);

SDL_Texture* DisplaySettings(SDL_Renderer *renderer, SDL_Texture *textures[29],SDL_Texture *background, SDL_AudioDeviceID deviceId, struct window window);

void loopAudio(Uint32 wavLength, Uint8 *wavBuffer, SDL_AudioDeviceID deviceId);

void render(SDL_Renderer *renderer, struct window *myWindow, struct player *player, struct List *brickList, struct ball *ball, SDL_Texture *textures[29], SDL_Texture *background,SDL_Rect *settingsRect, int life, int scoreTextLength);

void EndOfGameScreen(SDL_Renderer *renderer, SDL_Texture* background,SDL_Texture *textTexture, struct window myWindow);

int BallCollideWithBrick(struct List *brickList, struct ball *ball,SDL_Texture *textures[29], int score);

void BallCollideWithPlayer(struct player *player, struct ball *ball, double speedModifier);

void gameloop(SDL_Renderer *renderer, struct window window, SDL_Texture *textures[29], TTF_Font **fonts, SDL_Texture *background, SDL_AudioDeviceID deviceId, Uint32 wavLength, Uint8 *wavBuffer,int life, double speedModifier);