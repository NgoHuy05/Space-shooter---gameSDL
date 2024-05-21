void countdown(SDL_Renderer* renderer, TTF_Font* font) {
    int countdown = 3;
    Mix_Chunk* clickSound = Mix_LoadWAV("sound/click.mp3");
    Mix_Chunk* tingSound = Mix_LoadWAV("sound/ting.mp3");
    while (countdown > 0) {
        Mix_PlayChannel(-1, clickSound, 0);
        SDL_RenderClear(renderer);
        std::string countdownText = std::to_string(countdown);
        renderText(renderer, font, countdownText, 500, 250);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        countdown--; 
    }
        Mix_PlayChannel(-1, tingSound, 0);
}

bool isMouseOverButton(int mouseX, int mouseY, const SDL_Rect& buttonRect) {
    return (mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
            mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h));
}

bool showMenu(SDL_Renderer* renderer, TTF_Font* font) {
        SDL_Surface* background2Surface = IMG_Load("image/background2.png");
        SDL_Texture* background2Texture = SDL_CreateTextureFromSurface(renderer, background2Surface);
        SDL_FreeSurface(background2Surface);

        SDL_Surface* titleSurface = IMG_Load("image/title.png");
        SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_FreeSurface(titleSurface);

        SDL_Surface* playSurface = IMG_Load("image/play.png");
        SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
        SDL_FreeSurface(playSurface);

        SDL_Surface* exitSurface = IMG_Load("image/exit.png");
        SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
        SDL_FreeSurface(exitSurface);

        SDL_Surface* instructionSurface = IMG_Load("image/instruction.png");
        SDL_Texture* instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
        SDL_FreeSurface(instructionSurface);

    SDL_Event event;
    bool startGame = false;
    bool instruction = false;
    Mix_Chunk* clickSound = Mix_LoadWAV("sound/click.mp3");
    while (!startGame) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                 exit(0);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Rect startButtonRect = { 330, 250, 250, 80 };
                SDL_Rect exitButtonRect = { 330, 450,  250, 80 };
                SDL_Rect instructionButtonRect = { 330, 350,  250, 80 };
                SDL_Rect exitsettingButtonRect = { 700, 480,  250, 80 };
                if (isMouseOverButton(mouseX, mouseY, startButtonRect)) {
                    Mix_PlayChannel(-1, clickSound, 0);
                    startGame = true;
                } else if (isMouseOverButton(mouseX, mouseY, exitButtonRect)) {
                    Mix_PlayChannel(-1, clickSound, 0);
                    exit(0);
                }
                else if (isMouseOverButton(mouseX, mouseY, instructionButtonRect)) {
                    Mix_PlayChannel(-1, clickSound, 0);
                    instruction = true;
                }
                else if(isMouseOverButton(mouseX, mouseY, exitsettingButtonRect)){
                    Mix_PlayChannel(-1, clickSound, 0);
                    instruction = false;
                }
            }

        }
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool mouseOverStartButton = isMouseOverButton(mouseX, mouseY, {330, 250, 250, 80});
        bool mouseOverExitButton = isMouseOverButton(mouseX, mouseY, {330, 450, 250, 80});
        bool mouseOverInstructionButton = isMouseOverButton(mouseX, mouseY, {330, 350, 250, 80});
        bool mouseOverexitsettingButton = isMouseOverButton(mouseX, mouseY, {700, 480, 250, 80});

        if (instruction) {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background2Texture, NULL, NULL);
            SDL_Rect exitRect = { 700, 480,  250, 80 };

            if (mouseOverexitsettingButton) {
                SDL_SetTextureColorMod(exitTexture, 255, 255, 100);
            } else {
                SDL_SetTextureColorMod(exitTexture, 255, 255, 255);
            }

            SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
            renderText(renderer, font, "Flying up    : UP", 100, 100);
            renderText(renderer, font, "Flying down  : DOWN", 100, 150);
            renderText(renderer, font, "Flying left  : LEFT", 100, 200);
            renderText(renderer, font, "Flying right : RIGHT", 100, 250);
            renderText(renderer, font, "SHOOT: SPACE", 100, 300);
            SDL_RenderPresent(renderer);

        }
        else{
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, background2Texture, NULL, NULL);
            SDL_Rect titleRect = { 330, 100, 250, 150 };
            SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
            SDL_Rect playRect = { 330, 250, 250, 80 };

            if (mouseOverStartButton) {
                SDL_SetTextureColorMod(playTexture, 255, 255, 100);
            } else {
                SDL_SetTextureColorMod(playTexture, 255, 255, 255);
            }

            SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
            SDL_Rect exitRect = { 330, 450,  250, 80 };
            if (mouseOverExitButton) {
                SDL_SetTextureColorMod(exitTexture, 255, 255, 100);
            } else {
                SDL_SetTextureColorMod(exitTexture, 255, 255, 255);
            }

            SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
            SDL_Rect instructionRect = { 330, 350,  250, 80 };
            if (mouseOverInstructionButton) {
                SDL_SetTextureColorMod(instructionTexture, 255, 255, 100);
            } else {
                SDL_SetTextureColorMod(instructionTexture, 255, 255, 255);
            }
            SDL_RenderCopy(renderer, instructionTexture, NULL, &instructionRect);
            SDL_RenderPresent(renderer);
        }
    }
    return startGame;
}
