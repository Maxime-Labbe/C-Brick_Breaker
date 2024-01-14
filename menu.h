#ifndef BRICKBREAKER_MENU_H
#define BRICKBREAKER_MENU_H

#endif //BRICKBREAKER_MENU_H

#include "game.h"

void ChooseDifficulty(SDL_Renderer *renderer, struct window myWindow, SDL_Texture *textures[29], TTF_Font **fonts, SDL_Texture *background, SDL_AudioDeviceID deviceId, Uint32 wavLength, Uint8 *wavBuffer);

void GameloopRender(SDL_Renderer *renderer, SDL_Window *window);

void freeTextures(SDL_Texture *textures[29]);

void freeFonts(TTF_Font **fonts);