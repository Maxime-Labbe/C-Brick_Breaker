#include "menu.h"

void ChooseDifficulty(SDL_Renderer *renderer, struct window myWindow, SDL_Texture *textures[29], TTF_Font **fonts, SDL_Texture *background, SDL_AudioDeviceID deviceId, Uint32 wavLength, Uint8 *wavBuffer) {
    /*Fonction intermédiaire entre le menu et le jeu afin de laisser un choix de difficulté pour le joueur*/
    SDL_bool quit = false;
    SDL_Event event;

    int mouseX = 0;
    int mouseY = 0;

    SDL_Rect easyRect = {190,380,100,50};
    SDL_Rect mediumRect = {645,380,150,50};
    SDL_Rect hardRect = {1150,380,100,50};

    /*Booléen permettant de savoir si les textes/images sont agrandis*/
    bool oversizedEasy = false;
    bool oversizedMedium = false;
    bool oversizedHard = false;

    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (MouseOnRect(mouseX,mouseY,&easyRect)) {
                    gameloop(renderer,myWindow,textures,fonts,background,deviceId,wavLength,wavBuffer,5,1);
                    quit = true;
                    break;
                } else if (MouseOnRect(mouseX,mouseY,&mediumRect)) {
                    gameloop(renderer,myWindow,textures,fonts,background,deviceId,wavLength,wavBuffer,3,1.4);
                    quit = true;
                    break;
                } else if (MouseOnRect(mouseX,mouseY,&hardRect)) {
                    gameloop(renderer,myWindow,textures,fonts,background,deviceId,wavLength,wavBuffer,1,1.85);
                    quit = true;
                    break;
                }
            } else if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                break;
            }
        }
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&mouseX,&mouseY);

        /*Recadrer les rectangles s'ils sont agrandis*/
        oversizedEasy = FocusOnRect(&easyRect,mouseX,mouseY,oversizedEasy,myWindow);
        easyRect.x = (480 - easyRect.w)/2;
        easyRect.y = (myWindow.height - easyRect.h)/2;
        oversizedMedium = FocusOnRect(&mediumRect,mouseX,mouseY,oversizedMedium,myWindow);
        mediumRect.x = 480 + (480 - mediumRect.w)/2;
        mediumRect.y = (myWindow.height - mediumRect.h)/2;
        oversizedHard = FocusOnRect(&hardRect,mouseX,mouseY,oversizedHard,myWindow);
        hardRect.x = 960 + (480 - hardRect.w)/2;
        hardRect.y = (myWindow.height - hardRect.h)/2;

        DisplayBackground(renderer,background);

        SDL_RenderCopy(renderer,textures[22],NULL,&easyRect);
        SDL_RenderCopy(renderer,textures[23],NULL,&mediumRect);
        SDL_RenderCopy(renderer,textures[24],NULL,&hardRect);

        SDL_RenderPresent(renderer);
    }
}

void GameloopRender(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_bool quit = false;
    SDL_Event event;

    SDL_Color white = {255,255,255};
    SDL_Color titleColor = {36,106,115};
    SDL_Color textColor = {68,157,144};
    SDL_Color easyColor = {129,178,154};
    SDL_Color mediumColor = {242,204,143};
    SDL_Color hardColor = {92,26,27};

    /*Chargement des polices d'écritures, des textures et de la musique pour éviter les problèmes de performances*/

    /*Début du chargement des polices d'écritures*/
    TTF_Font* fonts[2];
    fonts[0] = TTF_OpenFont("..\\assets\\CocogooseProSemilightItalictrial.ttf",100);
    fonts[1] = TTF_OpenFont("..\\assets\\Times New Normal Regular.ttf",70);
    /*Fin du chargement des polices d'écritures*/

    /*Début du chargement des textures contenant les images et les textes*/
    SDL_Texture* textures[29];
    textures[0] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Score : 0", white));
    textures[1] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Play !", textColor));
    textures[2] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[0], "Brick Breaker", titleColor));
    textures[3] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Quit", textColor));
    textures[4] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Settings", white));
    textures[5] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\settings.png"));
    textures[6] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\background1.png"));
    textures[7] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\background2.png"));
    textures[8] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\background3.png"));
    textures[9] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\background4.png"));
    textures[10] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\background5.png"));
    textures[11] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\brick1.png"));
    textures[12] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\brick2.png"));
    textures[13] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\brick3.png"));
    textures[14] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\brick4.png"));
    textures[15] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\brick5.png"));
    textures[16] = SDL_CreateTextureFromSurface(renderer, IMG_Load("..\\assets\\whiteball.png"));
    textures[17] = SDL_CreateTextureFromSurface(renderer, IMG_Load("..\\assets\\player.png"));
    textures[18] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\heart.png"));
    textures[19] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\nextelem.png"));
    textures[20] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\lastelem.png"));
    textures[21] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\close.png"));
    textures[22] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Easy", easyColor));
    textures[23] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Medium", mediumColor));
    textures[24] = SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended(fonts[1], "Hard", hardColor));
    textures[25] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\notapplychange.png"));
    textures[26] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\applychange.png"));
    textures[27] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\volumeon.png"));
    textures[28] = SDL_CreateTextureFromSurface(renderer,IMG_Load("..\\assets\\volumeoff.png"));
    /*Fin du chargement des textures contenant les images et les textes*/


    /*Début du chargement de la musique et du périphérique audio*/
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV("..\\assets\\music.wav",&wavSpec,&wavBuffer,&wavLength);
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL,0,&wavSpec,NULL,0);
    /*Fin du chargement de la musique et du périphérique audio*/

    SDL_Texture *background = textures[10]; /*variable qui stocke le fond d'écran actuel*/

    SDL_Rect settingsRect = {1355,10,75,75};
    SDL_Rect playRect = {645,350,150,60};
    SDL_Rect quitRect = {660,550,120,60};
    SDL_Rect titleRect = {470, 50, 500, 100};

    /*Création d'une structure contenant la largeur et la hauteur de la fenêtre pour utiliser plus facilement*/
    int windowWidth,windowHeight;
    SDL_GetWindowSize(window,&windowWidth,&windowHeight);
    struct window myWindow = {windowWidth,windowHeight};

    int mouseX = 0;
    int mouseY = 0;

    /*Booléen permettant de savoir si les textes/images sont agrandis*/
    bool oversizedSettings = false;
    bool oversizedPlay = false;
    bool oversizedQuit = false;

    SDL_QueueAudio(deviceId,wavBuffer,wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
    SDL_Delay(350);

    while(!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (MouseOnRect(mouseX, mouseY, &settingsRect)) {
                    background = DisplaySettings(renderer, textures, background, deviceId, myWindow);
                    break;
                } else if (MouseOnRect(mouseX, mouseY, &playRect)) {
                    ChooseDifficulty(renderer,myWindow,textures,fonts,background,deviceId,wavLength,wavBuffer);
                    break;
                } else if (MouseOnRect(mouseX, mouseY, &quitRect)) {
                    quit = true;
                    break;
                }
            } else if (event.type == SDL_KEYDOWN) {
                ChooseDifficulty(renderer,myWindow,textures,fonts,background,deviceId,wavLength,wavBuffer);
                break;
            }
        }
        SDL_RenderClear(renderer);

        SDL_GetMouseState(&mouseX,&mouseY);

        /*Recadrer les rectangles s'ils sont agrandis*/
        oversizedSettings = FocusOnRect(&settingsRect,mouseX,mouseY,oversizedSettings,myWindow);
        settingsRect.x = myWindow.width - settingsRect.w - 10;
        oversizedPlay = FocusOnRect(&playRect,mouseX,mouseY,oversizedPlay,myWindow);
        playRect.x = (myWindow.width - playRect.w)/2;
        playRect.y = (myWindow.height - playRect.h)/2;
        oversizedQuit = FocusOnRect(&quitRect,mouseX,mouseY,oversizedQuit,myWindow);
        quitRect.x = (myWindow.width - quitRect.w)/2;
        quitRect.y = (myWindow.height - quitRect.h)/2 + 200;

        DisplayBackground(renderer,background);

        SDL_RenderCopy(renderer,textures[1],NULL,&playRect);
        SDL_RenderCopy(renderer,textures[3],NULL,&quitRect);
        SDL_RenderCopy(renderer,textures[5],NULL,&settingsRect);
        SDL_RenderCopy(renderer, textures[2], NULL, &titleRect);
        loopAudio(wavLength,wavBuffer,deviceId);

        SDL_RenderPresent(renderer);

    }
    freeTextures(textures);
    freeFonts(fonts);
    SDL_DestroyTexture(background);

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void freeTextures(SDL_Texture *textures[29]) {
    /*Libérer les textures pour éviter d'avoir des problèmes lors de la fermeture du programme*/
    for(int i = 0; i < 29; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}

void freeFonts(TTF_Font *fonts[2]) {
    /*Libérer les polices pour éviter d'avoir des problèmes lors de la fermeture du programme*/
    for(int i = 0; i < 2; i++) {
        TTF_CloseFont(fonts[i]);
    }
}