#include "game.h"

void MovePlayer(struct player *player, struct window *window) {
    if(player->right == true) {
        player->speed = 5;
        player->inertie += .01;
    } else if(player->left == true){
        player->speed = -5;
        player->inertie += .01;
    } else {
        player->speed = 0;
    }
    if(player->x + player->speed > window->width-player->w || player->x + player->speed < 0) { /*Vérification bord du terrain*/
        player->speed = 0;
    }
}

void MoveBall(struct ball *ball, struct window *window) {
    if(ball->x + ball->speedX > window->width-ball->w || ball->x + ball->speedX < 0) {
        ball->speedX = -ball->speedX;
    }
    if(ball->y + ball->speedY < 50) {
        ball->speedY = -ball->speedY;
    }
    ball->x += ball->speedX;
    ball->y += ball->speedY;
}

bool RemoveLife(struct ball *ball, struct window *window) {
    if(ball->y > window->height) {
        return true;
    }
    return false;
}

void DisplayBricks(SDL_Renderer *renderer, struct List *brickList) {
    struct BrickElem *brick = brickList->firstBrick;
    for(int i = 0; i < CountBricks(brickList); i++) {
        SDL_Rect brickRect = {brick->Elem->x,brick->Elem->y,brick->Elem->w,brick->Elem->h};

        SDL_RenderCopy(renderer,brick->Elem->texture,NULL,&brickRect);
        brick = brick->nextBrick;
    }
}

void DisplayText(SDL_Renderer *renderer, SDL_Rect *textRect, SDL_Texture *texture) {
    SDL_RenderCopy(renderer, texture, NULL, textRect);
}

void DisplayLife(SDL_Renderer *renderer, SDL_Texture *texture, int life) {
    SDL_Rect lifeRect = {10, 10, 40, 40};
    for(int i = 0; i < life; i++) {
        SDL_RenderCopy(renderer,texture,NULL,&lifeRect);
        lifeRect.x += lifeRect.w + 10;
    }
}

void DisplayBackground(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_Rect dest = {0, 0, 1440, 810};
    SDL_RenderCopy(renderer,texture,NULL,&dest);
}

int FindTextureIndex(SDL_Texture *textures[29], SDL_Texture *currentTexture) {
    /*Fonction qui permet de montrer le fond d'écran actuel en premier dans les paramètres*/
    for (int i = 6; i <= 10; i++) {
        if (textures[i] == currentTexture) {
            return i;
        }
    }
}

bool MouseOnRect(int mouseX, int mouseY, SDL_Rect *rect) {
    /*Vérifie si la souris se trouve sur un rectangle*/
    if((mouseX >= rect->x && mouseX <= rect->x + rect->w)
    && (mouseY >= rect->y && mouseY <= rect->y + rect->h)) {
        return true;
    }
    return false;
}

bool FocusOnRect(SDL_Rect *rect, int mouseX, int mouseY, bool oversized, struct window window) {
    /*Permet d'agrandir les éléments SI la souris se trouve sur le rectangle de l'élément*/
    bool mouseOnRect = MouseOnRect(mouseX, mouseY, rect);
    if(mouseOnRect && !oversized) {
        rect->w = rect->w*1.2;
        rect->h = rect->h*1.2;
        return true;
    } else if(oversized && !mouseOnRect) {
        rect->w = rect->w/1.2;
        rect->h = rect->h/1.2;
        return false;
    }
    return oversized;
}

SDL_Texture* DisplaySettings(SDL_Renderer *renderer, SDL_Texture *textures[29],SDL_Texture *background, SDL_AudioDeviceID deviceId, struct window window) {
    SDL_bool quit = false;
    SDL_Event event;

    int imageIndex = FindTextureIndex(textures,background);
    int currentImageIndex = imageIndex;

    int mouseX = 0;
    int mouseY = 0;

    SDL_Rect imageRect = {320,175,800,450};
    SDL_Rect nextElemRect = {1300,350,100,100};
    SDL_Rect lastElemRect = {40,350,100,100};
    SDL_Rect closeRect = {1380,10,50,50};
    SDL_Rect applyChangeRect = {640,700,165,55};
    SDL_Rect soundRect = {10,10,50,50};
    SDL_Rect settingsRect = {600,5,250,100};

    /*Booléen permettant de savoir si les textes/images sont agrandis*/
    bool oversizedNextElem = false;
    bool oversizedLastElem = false;
    bool oversizedClose = false;
    bool oversizedApplyChanges = false;
    bool oversizedSound = false;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                /*Naviguer à travers les fonds d'écrans grâce aux boutons*/
                if(MouseOnRect(mouseX, mouseY, &nextElemRect)) {
                    if (imageIndex++ == 10) {
                        imageIndex = 6;
                    }
                    break;
                } else if(MouseOnRect(mouseX, mouseY, &lastElemRect)) {
                    if (imageIndex-- == 6) {
                        imageIndex = 10;
                    }
                    break;
                }
                /*Naviguer à travers les fonds d'écrans grâce aux boutons*/
                else if(MouseOnRect(mouseX, mouseY, &closeRect)) {
                    quit = true;
                    break;
                } else if(MouseOnRect(mouseX, mouseY, &applyChangeRect) && (currentImageIndex != imageIndex)) {
                    background = textures[imageIndex];
                    currentImageIndex = imageIndex;
                    break;
                } else if(MouseOnRect(mouseX, mouseY, &soundRect)) {
                    if (SDL_GetAudioDeviceStatus(deviceId) == SDL_AUDIO_PAUSED || SDL_GetAudioDeviceStatus(deviceId) == SDL_AUDIO_STOPPED) {
                        SDL_PauseAudioDevice(deviceId,0);
                    } else {
                        SDL_PauseAudioDevice(deviceId,1);
                    }
                    break;
                }
            } else if(event.type == SDL_KEYDOWN) {
                /*Naviguer à travers les fonds d'écrans grâce aux flèches directionnelles*/
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    if (imageIndex++ == 10) {
                        imageIndex = 6;
                    }
                    break;
                } else if (event.key.keysym.sym == SDLK_LEFT) {
                    if (imageIndex-- == 6) {
                        imageIndex = 10;
                    }
                    break;
                }
                /*Naviguer à travers les fonds d'écrans grâce aux flèches directionnelles*/
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&mouseX,&mouseY);

        /*Recadrer les rectangles s'ils sont agrandis*/
        oversizedLastElem = FocusOnRect(&lastElemRect,mouseX,mouseY,oversizedLastElem,window);
        lastElemRect.y = (window.height - lastElemRect.h)/2;
        oversizedNextElem = FocusOnRect(&nextElemRect,mouseX,mouseY,oversizedNextElem,window);
        nextElemRect.x = window.width - nextElemRect.w - 40;
        nextElemRect.y = (window.height - nextElemRect.h)/2;
        oversizedClose = FocusOnRect(&closeRect,mouseX,mouseY,oversizedClose,window);
        closeRect.x = window.width - closeRect.w - 10;
        oversizedApplyChanges = FocusOnRect(&applyChangeRect,mouseX,mouseY,oversizedApplyChanges,window);
        applyChangeRect.x = (window.width - applyChangeRect.w)/2;
        applyChangeRect.y = (window.height - applyChangeRect.h - 55);
        oversizedSound = FocusOnRect(&soundRect,mouseX,mouseY,oversizedSound,window);

        DisplayText(renderer,&settingsRect,textures[4]);
        SDL_RenderCopy(renderer,textures[imageIndex],NULL,&imageRect);
        SDL_RenderCopy(renderer,textures[19],NULL,&nextElemRect);
        SDL_RenderCopy(renderer,textures[20],NULL,&lastElemRect);
        SDL_RenderCopy(renderer,textures[21],NULL,&closeRect);

        /*Choix des textures à afficher selon des conditions*/
        if (imageIndex != currentImageIndex) {
            SDL_RenderCopy(renderer,textures[26],NULL,&applyChangeRect);
        } else {
            SDL_RenderCopy(renderer,textures[25],NULL,&applyChangeRect);
        }

        if (SDL_GetAudioDeviceStatus(deviceId) == SDL_AUDIO_PAUSED || SDL_GetAudioDeviceStatus(deviceId) == SDL_AUDIO_STOPPED) {
            SDL_RenderCopy(renderer,textures[28],NULL,&soundRect);
        } else {
            SDL_RenderCopy(renderer,textures[27],NULL,&soundRect);
        }
        /*Choix des textures à afficher selon des conditions*/

        SDL_RenderPresent(renderer);
    }
    return background;
}

void loopAudio(Uint32 wavLength, Uint8 *wavBuffer, SDL_AudioDeviceID deviceId) {
    /*Permet de remettre de la musique en boucle*/
    if (SDL_GetQueuedAudioSize(deviceId) < wavLength) {
        SDL_QueueAudio(deviceId,wavBuffer,wavLength);
    }
}

void render(SDL_Renderer *renderer, struct window *myWindow, struct player *player, struct List *brickList, struct ball *ball, SDL_Texture *textures[29], SDL_Texture *background,SDL_Rect *settingsRect, int life, int scoreTextLength) {
    /*Fonction qui centraliser tous ce qui doit être render dans la fonction gameloop*/
    DisplayBackground(renderer,background);
    DisplayLife(renderer,textures[18],life);
    SDL_RenderCopy(renderer,textures[5],NULL,settingsRect);
    SDL_Rect scoreRect = {(myWindow->width-scoreTextLength)/2,5,scoreTextLength,50};
    DisplayText(renderer,&scoreRect,textures[0]);
    SDL_Rect playerRect = {player->x,player->y,player->w,player->h};
    SDL_RenderCopy(renderer,player->texture,NULL,&playerRect);
    SDL_Rect ballRect = {ball->x,ball->y,ball->w,ball->h};
    SDL_RenderCopy(renderer,ball->texture,NULL,&ballRect);
    DisplayBricks(renderer,brickList);
    SDL_RenderPresent(renderer);
}

void EndOfGameScreen(SDL_Renderer *renderer, SDL_Texture* background,SDL_Texture *textTexture, struct window myWindow) {
    SDL_bool quit = false;
    SDL_Event event;

    SDL_Rect backgroundRect = {0,0,1440,810};
    SDL_Rect textRect = {(myWindow.width-1200)/2,(myWindow.height-100)/2,1200,100};

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                quit = true;
                break;
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,background,NULL,&backgroundRect);
        SDL_RenderCopy(renderer,textTexture,NULL,&textRect);

        SDL_RenderPresent(renderer);
    }
}

int BallCollideWithBrick(struct List *brickList, struct ball *ball, SDL_Texture *textures[29], int score) {
    struct BrickElem *brick = brickList->firstBrick;
    for(int i = 0; i < CountBricks(brickList); i++) {
        if(((ball->x + ball->speedX > brick->Elem->x && ball->x + ball->speedX < brick->Elem->x + brick->Elem->w)
         || (brick->Elem->x > ball->x && brick->Elem->x < ball->x + ball->w + ball->speedX))
        && ((ball->y + ball->speedY > brick->Elem->y && ball->y + ball->speedY < brick->Elem->y + brick->Elem->h)
         || (brick->Elem->y > ball->y && brick->Elem->y < ball->y + ball->h + ball->speedY))) { /*Test de collision entre la balle et une brique*/
            if((brick->Elem->y + brick->Elem->h) - ball->y  < 0 || brick->Elem->y - (ball->y + ball->h) > 0) {
                /*Inverser la vitesse verticale si la balle touche le dessus ou le dessous de la brique*/
                ball->speedY = -ball->speedY;
            } else if((brick->Elem->x + brick->Elem->w) - ball->x  < 0 || brick->Elem->x - (ball->x + ball->w) > 0) {
                /*Inverser la vitesse horizontale si la balle touche la droite ou la gauche de la brique*/
                ball->speedX = -ball->speedX;
            }
            brick->Elem->life--;
            if(brick->Elem->life==0) {
                /*La brique est cassée*/
                RemoveBrickAtIndex(brickList,i);
                score+=50;
            } else {
                /*La brique est endomagée*/
                brick->Elem->texture = textures[10 + brick->Elem->life];
                /*Les textures des briques ont été placés de manière à pouvoir incrémenter et décrémenter l'index selon
                 *la vie de la brique exemple : brick->life = 1 équivaut textures[11] brick->life = 3 =textures[13]*/
                score+=10;
            }
            return score;
        }
        brick = brick->nextBrick;
    }
    return score;
}

void BallCollideWithPlayer(struct player *player, struct ball *ball, double speedModifier) {
    if (((player->x + player->speed > ball->x + ball->speedX && player->x + player->speed < ball->x + ball->w + ball->speedX)
       || (ball->x + ball->speedX > player->x + player->speed && ball->x + ball->speedX < player->x + player->w + player->speed))
      && ((player->y > ball->y + ball->speedY && player->y < ball->y + ball->h + ball->speedY)
       || (ball->y + ball->speedY > player->y && ball->y + ball->speedY < player->y + player->h ))) { /*Test de collision entre la balle et le joueur*/
        /*Calcul du cos afin de changer l'angle de la balle en fonction de où la balle a touché le joueur*/
        double cos1 = (ball->x + ball->w/2 + ball->speedX - player->x - player->w/2 - player->speed)/(player->w/2);
        if(cos1 >=-1 && cos1<=1 && ball->y+ball->h/2 < player->y) {
            double point = acos((ball->x + ball->w/2 + ball->speedX - player->x - player->w/2 - player->speed)/(player->w/2));
            ball->speedY = -sin(point) * 2 * (1 + player->inertie/2) * speedModifier;
            ball->speedX = cos1 * 2 * (1 + player->inertie/2) * speedModifier;
        }
    }
}

void gameloop(SDL_Renderer *renderer, struct window myWindow, SDL_Texture *textures[29], TTF_Font **fonts, SDL_Texture *background, SDL_AudioDeviceID deviceId, Uint32 wavLength, Uint8 *wavBuffer, int life, double speedModifier) {
    SDL_bool quit = false;
    SDL_Event event;
    bool ballMove = false;

    int level = 1;
    int score = 0;
    char *scoreText = malloc(50);
    SDL_Color white = {255,255,255};

    struct player player = {myWindow.width/2-50,myWindow.height-60,100,20,0,0,false,false,textures[17]};
    struct List brickList = {NULL};
    InitBrickList(&myWindow,&brickList,24*((level-1)/2+1),textures,level);
    struct ball ball = {player.x+player.w/4,player.y-50,50,50,0,0,textures[16]};

    int lastTimer = SDL_GetTicks();
    int invicibleTimer = 1000;
    int lastLifeLost = SDL_GetTicks();
    int startMoving = SDL_GetTicks();

    SDL_Rect settingsRect = {1390 ,5,45,45};

    int mouseX = 0;
    int mouseY = 0;

    bool oversizedSettings = false;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                break;
            } else if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_LEFT)) {
                player.left = true;
            } else if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)) {
                player.right = true;
            } else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !ballMove) {
                /*Pouvoir lancer la balle au début ou quand le joueur perd une vie*/
                double speed = (double)rand() / RAND_MAX; /*Nombre entre 0 et 1*/
                ball.speedX = (1 - speed) * 2.5 * speedModifier;
                ball.speedY = -speed * 2.5 * speedModifier;
                ballMove = true;
            } else if(event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_LEFT)) {
                player.left = false;
            } else if(event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)) {
                player.right = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (MouseOnRect(mouseX, mouseY, &settingsRect)) {
                    background = DisplaySettings(renderer, textures, background, deviceId, myWindow);
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);

        if(SDL_GetTicks() - lastTimer > 4) {

            SDL_GetMouseState(&mouseX,&mouseY);

            oversizedSettings = FocusOnRect(&settingsRect,mouseX,mouseY,oversizedSettings,myWindow);
            settingsRect.x = myWindow.width - settingsRect.w - 5;

            BallCollideWithPlayer(&player,&ball,speedModifier);

            if(player.speed==0) {
                MovePlayer(&player,&myWindow);
                if(player.speed!=0) {
                    startMoving = SDL_GetTicks(); /*Savoir quand le joueur commence à bouger pour réduire l'inertie quand il faut*/
                }
            } else {
                MovePlayer(&player,&myWindow);
            }

            if(SDL_GetTicks() - startMoving > 800) {
                player.inertie -= 0.05;
            }

            if(player.inertie > 1) {
                player.inertie = 1;
            } else if(player.inertie<0) {
                player.inertie = 0;
            }

            player.x += player.speed;

            if(!ballMove) {
                /*Suivi de la balle selon la position du joueur s'il n'a pas encore lancé la balle*/
                ball.x = player.x+player.w/4;
                ball.y = player.y-50;
            }

            MoveBall(&ball,&myWindow);

            if(RemoveLife(&ball,&myWindow) && SDL_GetTicks() - lastLifeLost > invicibleTimer) {
                /*Replacer la balle sur le joueur s'il perd une vie*/
                life--;
                ball.x = player.x+player.w/4;
                ball.y = player.y-50;
                ball.speedX = 0;
                ball.speedY = 0;
                ballMove = false;
                lastLifeLost = SDL_GetTicks();
            }

            if(life == 0) {
                sprintf(scoreText,"You have lost the game with a score of %i...", score);
                SDL_DestroyTexture(textures[0]);
                textures[0] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], scoreText, white));
                EndOfGameScreen(renderer,background,textures[0],myWindow);
                quit = true;
            }

            if(CountBricks(&brickList)==0) {
                /*Changer le niveau et initialiser les briques si le joueur a fini le précédent niveau
                 *Ou quitter le jeu si le joueur a atteint le niveau maximum*/
                if(level>=10) {
                    sprintf(scoreText,"You have won the game with a score of %i !!", score);
                    SDL_DestroyTexture(textures[0]);
                    textures[0] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], scoreText, white));
                    EndOfGameScreen(renderer,background,textures[0],myWindow);
                    quit = true;
                } else {
                    level++;
                    ball.x = player.x+player.w/4;
                    ball.y = player.y-50;
                    ball.speedX = 0;
                    ball.speedY = 0;
                    ballMove = false;
                    InitBrickList(&myWindow,&brickList,24*((level-1)/2+1),textures,level);
                }
            }

            score = BallCollideWithBrick(&brickList,&ball,textures,score);
            sprintf(scoreText,"Score : %i", score);
            SDL_DestroyTexture(textures[0]);
            textures[0] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], scoreText, white));

            render(renderer,&myWindow,&player,&brickList,&ball,textures,background,&settingsRect,life,150+30*(pow(score,0.1)));
            loopAudio(wavLength,wavBuffer,deviceId);

            lastTimer = SDL_GetTicks();
        }
    }
    free(scoreText);
}