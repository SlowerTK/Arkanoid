#include "button.h"
#include <iostream>

const unsigned long long screenWidth = 640, screenHeight = 480;
const int paddleY = screenHeight - 5, paddleHight = 3;
int ball = 1, paddle = 1, ballXDir = 1, ballYDir = 1, paddleX = 0, paddleXDir = -1, paddleWidth = 32, ballWidth = 8, ballHight = 8, ballSpeed = 1, multiply = 10, life = 2, brickHight = 32, brickWidth = 64, ballX = 0, ballY = 0, win = 0, countVolume = 0;
int paddleCenter = paddleWidth / 2, max_color = 255;

int init = Mix_Init(0);
SDL_Window *window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

int main(int argc, char *argv[])
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *music = Mix_LoadMUS("audio/awesomeness.wav");
    Mix_Chunk *sound = Mix_LoadWAV("audio/click_2.wav");
    Mix_Music *music2 = Mix_LoadMUS("audio/audio.wav");
    Mix_Chunk *sound2 = Mix_LoadWAV("audio/negative_2.wav");
    Mix_Chunk *sound3 = Mix_LoadWAV("audio/positive.wav");
    Mix_Chunk *sound4 = Mix_LoadWAV("audio/click.wav");
    Mix_Music *music3 = Mix_LoadMUS("audio/pause.wav");
    Mix_VolumeMusic(32);
    bool quit = false, menu = false, options = false, game = false, ease = true, restarts = false;
    Mouse mouse;

    Button startButton;
    startButton.srect.y = 0;
    startButton.srect.x = screenWidth / 2 - startButton.drect.w / 2;
    startButton.drect.y = screenHeight / 2 - startButton.drect.h / 2;
    startButton.drect.x = screenWidth / 2 - startButton.drect.w / 2;
    Button optiButton;
    optiButton.srect.y = 300;
    optiButton.srect.x = screenWidth / 2 - optiButton.drect.w / 2;
    optiButton.drect.y = (startButton.drect.y + screenHeight - optiButton.drect.h) / 2;
    optiButton.drect.x = screenWidth / 2 - optiButton.drect.w / 2;
    Button exitButton;
    exitButton.srect.y = 700;
    exitButton.srect.x = screenWidth / 2 - exitButton.drect.w / 2;
    exitButton.drect.y = screenHeight - exitButton.drect.h;
    exitButton.drect.x = screenWidth / 2 - exitButton.drect.w / 2;
    Button backButton;
    backButton.srect.y = 200;
    backButton.srect.x = screenWidth / 2 - backButton.drect.w / 2;
    backButton.drect.y = screenHeight - backButton.drect.h;
    backButton.drect.x = screenWidth / 2 + backButton.drect.w / 4;
    Button easeButton;
    easeButton.srect.y = 800;
    easeButton.srect.x = screenWidth / 2 - easeButton.drect.w / 2;
    easeButton.drect.y = screenHeight / 2 - easeButton.drect.h * 2 + easeButton.drect.h / 2;
    easeButton.drect.x = screenWidth / 2 + easeButton.drect.w / 4;
    Button hardButton;
    hardButton.srect.y = 900;
    hardButton.srect.x = screenWidth / 2 - hardButton.drect.w / 2;
    hardButton.drect.y = screenHeight / 2 + hardButton.drect.h / 2;
    hardButton.drect.x = screenWidth / 2 + hardButton.drect.w / 4;
    Button continueButton;
    continueButton.srect.y = 100;
    continueButton.srect.x = screenWidth / 2 - continueButton.drect.w / 2;
    continueButton.drect.y = screenHeight / 2 - continueButton.drect.h / 2;
    continueButton.drect.x = screenWidth / 2 - continueButton.drect.w / 2;
    Button volumeButton;
    volumeButton.srect.y = 1000;
    volumeButton.srect.x = screenWidth / 2 - volumeButton.drect.w / 2;
    volumeButton.drect.y = screenHeight / 2 + volumeButton.drect.h + volumeButton.drect.h / 2 + volumeButton.drect.h / 4 + volumeButton.drect.h / 8 + volumeButton.drect.h / 16;
    volumeButton.drect.x = screenWidth / 2 - volumeButton.drect.w;

    ballX = screenWidth / 2;
    ballY = screenHeight - (screenHeight / 4);
    paddleX = screenWidth / 2 - paddleWidth / 2;
    ballYDir = -1;

    SDL_Event e_menu, e, paddleEvent, option, restart;
    Mix_PlayMusic(music, -1);
menu:
    menu = false;
    options = false;
    game = false;
    while (!menu)
    {
        mouse.update();
        startButton.update(mouse);
        optiButton.update(mouse);
        exitButton.update(mouse);
        while (SDL_PollEvent(&e_menu))
        {
            if (e_menu.type == SDL_MOUSEBUTTONUP)
            {
                if (e_menu.button.button == SDL_BUTTON_LEFT)
                {
                    if (startButton.isSelected)
                    {
                        Mix_PlayChannel(-1, sound, 0);
                        game = true;
                        menu = true;
                    }
                    if (optiButton.isSelected)
                    {
                        Mix_PlayChannel(-1, sound, 0);
                        options = true;
                        menu = true;
                    }
                    if (exitButton.isSelected)
                    {
                        Mix_PlayChannel(-1, sound, 0);
                        SDL_Delay(100);
                        return 0;
                    }
                }
            }
            if (e_menu.type == SDL_KEYUP)
            {
                if (e_menu.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 0;
                }
            }
            SDL_SetRenderDrawColor(ren, 50, 50, 50, max_color);
            SDL_RenderClear(ren);
            SDL_Texture *background = IMG_LoadTexture(ren, "images/backGround.png");
            SDL_RenderCopy(ren, background, NULL, NULL);
            startButton.draw();
            optiButton.draw();
            exitButton.draw();
            mouse.draw();
            SDL_RenderPresent(ren);
        }
    }

    if (options == true)
    {
        while (options == true)
        {
            backButton.update(mouse);
            easeButton.update(mouse);
            hardButton.update(mouse);
            volumeButton.update(mouse);
            mouse.update();
            while (SDL_PollEvent(&option))
            {
                if (option.type == SDL_KEYUP)
                {
                    if (option.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 0;
                    }
                }
                if (option.type == SDL_MOUSEBUTTONUP)
                {
                    if (option.button.button == SDL_BUTTON_LEFT)
                    {
                        if (backButton.isSelected)
                        {
                            Mix_PlayChannel(-1, sound, 0);
                            options = false;
                        }
                    }
                }
                if (option.type == SDL_MOUSEBUTTONUP)
                {
                    if (option.button.button == SDL_BUTTON_LEFT)
                    {
                        if (easeButton.isSelected)
                        {
                            Mix_PlayChannel(-1, sound, 0);
                            ease = false;
                        }
                        if (hardButton.isSelected)
                        {
                            Mix_PlayChannel(-1, sound, 0);
                            paddleWidth = 64;
                        }
                    }
                }
                if (option.type == SDL_MOUSEBUTTONUP)
                {
                    if (option.button.button == SDL_BUTTON_LEFT)
                    {
                        if (volumeButton.isSelected)
                        {
                            Mix_PlayChannel(-1, sound, 0);
                            countVolume++;
                            if (countVolume % 5 == 0)
                            {
                                Mix_VolumeMusic(32);
                            }
                            if (countVolume % 5 == 1)
                            {
                                Mix_VolumeMusic(64);
                            }
                            if (countVolume % 5 == 2)
                            {
                                Mix_VolumeMusic(96);
                            }
                            if (countVolume % 5 == 3)
                            {
                                Mix_VolumeMusic(128);
                            }
                            if (countVolume % 5 == 4)
                            {
                                Mix_VolumeMusic(0);
                            }
                        }
                    }
                }
            }
            SDL_RenderClear(ren);
            SDL_SetRenderDrawColor(ren, 45, 45, 45, max_color);
            SDL_Texture *option = IMG_LoadTexture(ren, "images/options.png");
            SDL_Rect optionRect = {0, 0, screenWidth, screenHeight};
            SDL_RenderCopy(ren, option, NULL, &optionRect);
            backButton.draw();
            easeButton.draw();
            hardButton.draw();
            volumeButton.draw();
            mouse.draw();
            SDL_RenderPresent(ren);
        }
        goto menu;
    }

    if (ease == true)
    {
        ballSpeed = 3;
    }
    if (ease == false)
    {
        ballSpeed = 1;
    }
restarting:
    restarts = false;
    win = 0;
    life = 2;
    quit = false;
    multiply = 10;
    ballX = screenWidth / 2;
    ballY = screenHeight - (screenHeight / 4);
    paddleX = screenWidth / 2 - paddleCenter;
    int brick[10][20];
    for (int i = 1; i < 9; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            brick[i][j] = 1;
        }
    }
    int backColor = 0, gameover = 0;
    if (game == true)
    {
        Mix_PlayMusic(music2, -1);
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_KEYUP)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 0;
                    }
                    break;
                }
            }

            // clear screen
            SDL_SetRenderDrawColor(ren, max_color, max_color, max_color, max_color);
            SDL_RenderClear(ren);
            // draw bricks and check for collision
            for (int i = 1; i < 9; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (brick[i][j] == 1)
                    {
                        SDL_Rect rect = {j * brickWidth, i * brickHight, brickWidth, brickHight};
                        // SDL_Texture *brickTexture = IMG_LoadTexture(ren, "images/brick.png");
                        // SDL_RenderCopy(ren, brickTexture, NULL, &rect);
                        // SDL_RenderPresent(ren);
                        SDL_SetRenderDrawColor(ren, 0, 0, 0, max_color);
                        SDL_RenderFillRect(ren, &rect);
                        for (int k = 0; k < brickWidth; k++)
                        {
                            if ((ballX - 1 == j * brickWidth + k && (ballY == i * brickHight || ballY == i * brickHight + brickHight)) || (ballX + ballWidth - 1 == j * brickWidth + k && (ballY + ballHight - 1 == i * brickHight || ballY + ballHight - 1 == i * brickHight + brickHight)))
                            {
                                brick[i][j] = 0;
                                ballYDir = -ballYDir;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if ((ballY - 1 == i * brickHight + k && (ballX == j * brickWidth || ballX == j * brickWidth + brickWidth)) || (ballY + ballHight - 1 == i * brickHight + k && (ballX + ballWidth - 1 == j * brickWidth || ballX + ballWidth - 1 == j * brickWidth + brickWidth)))
                            {
                                brick[i][j] = 0;
                                ballXDir = -ballXDir;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                        }
                    }
                }
            }

            // draw ball and check for collision
            if (ball == 1)
            {
                SDL_Rect rect = {ballX, ballY, ballWidth, ballHight};
                SDL_SetRenderDrawColor(ren, 0, 0, 0, max_color);
                // SDL_Texture *ball = IMG_LoadTexture(ren, "images/ball.png");
                // SDL_RenderCopy(ren, ball, NULL, &rect);
                SDL_RenderFillRect(ren, &rect);
            }
            // draw paddle and check for collision
            if (paddle == 1)
            {
                SDL_Texture *paddleTexture = IMG_LoadTexture(ren, "images/paddleX32.png");
                if (paddleWidth == 64)
                {
                    SDL_Texture *paddleTexture = IMG_LoadTexture(ren, "images/paddleX64.png");
                }

                SDL_Rect rect = {paddleX, paddleY, paddleWidth, paddleHight};
                SDL_RenderCopy(ren, paddleTexture, NULL, &rect);
                SDL_RenderPresent(ren);
            }
            // move paddle and check for collision
            SDL_PumpEvents();
            SDL_GetMouseState(&paddleCenter, NULL);
            paddleX = paddleCenter - paddleWidth / 2;
            if (paddleX < 0)
            {
                paddleX = 0;
            }
            if (paddleX > screenWidth - paddleWidth)
            {
                paddleX = screenWidth - paddleWidth;
            }

            ballX += ballXDir;
            ballY += ballYDir;
            if (ballX <= 0 || ballX >= screenWidth - ballWidth)
            {
                ballXDir = -ballXDir;
                Mix_PlayChannel(-1, sound4, 0);
            }
            if (ballY == 0)
            {
                ballYDir = -ballYDir;
                Mix_PlayChannel(-1, sound4, 0);
            }
            if (ballY == screenHeight)
            {
                ball = 0;
                paddle = 0;
            }
            for (int i = 0; i < paddleWidth; i++)
            {
                if (ballX == paddleX + i && ballY == paddleY - ballHight)
                {
                    if (ballX + ballWidth / 2 == paddleCenter || ballX + ballWidth / 2 == paddleCenter - 1 || ballX + ballWidth / 2 == paddleCenter + 1 || ballX + ballWidth / 2 == paddleCenter - 2 || ballX + ballWidth / 2 == paddleCenter + 2 || ballX + ballWidth / 2 == paddleCenter - 3 || ballX + ballWidth / 2 == paddleCenter + 3)
                    {
                        ballXDir = 0;
                    }
                    else if (ballX + ballWidth / 2 < paddleCenter)
                    {
                        if (ballX + ballWidth / 2 < paddleCenter - 3)
                        {
                            ballXDir = -1;
                        }
                        if (ballX + ballWidth / 2 < paddleCenter - 14)
                        {
                            ballXDir = -2;
                        }
                    }
                    else if (ballX + ballWidth / 2 > paddleCenter)
                    {
                        if (ballX + ballWidth / 2 > paddleCenter + 3)
                        {
                            ballXDir = 1;
                        }
                        if (ballX + ballWidth / 2 > paddleCenter + 14)
                        {
                            ballXDir = 2;
                        }
                    }
                    ballYDir = -ballYDir;
                    Mix_PlayChannel(-1, sound4, 0);
                }
            }

            // update screen
            SDL_RenderPresent(ren);

            // if ball is out of screen
            if (paddle == 0 && life == 0)
            {
                quit = true;
            }
            if (paddle == 0 && life > 0)
            {
                life--;
                paddle = 1;
                ball = 1;
                ballX = paddleCenter - ballWidth / 2;
                ballY = screenHeight - paddleHight * 2 - ballHight;
                ballYDir = -1;
                if (ease == false)
                {
                    SDL_Delay(1000);
                }
                else
                {
                    SDL_Delay(700);
                }
            }

            // check for win
            for (int i = 1; i < 9; i++)
            {
                for (int j = 1; j < 9; j++)
                {
                    if (brick[i][j] == 0)
                    {
                        win++;
                    }
                }
            }
            if (win == 32 && ease == false)
            {
                multiply = 5;
            }
            else if (win == 48 && ease == false)
            {
                multiply = 2;
            }
            else if (win == 32 && ease == true)
            {
                multiply = 9;
            }
            else if (win == 48 && ease == true)
            {
                multiply = 6;
            }
            if (win == 64)
            {
                quit = true;
            }
            else
            {
                win = 0;
            }
            SDL_Delay(ballSpeed * multiply);
        }
    }

    SDL_SetRenderDrawColor(ren, max_color, max_color, max_color, max_color);
    SDL_RenderClear(ren);
    if (life == 0 && paddle == 0)
    {
        SDL_Texture *gameOver = IMG_LoadTexture(ren, "images/gameOver.png");
        Mix_PlayChannel(-1, sound2, 0);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, gameOver, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
        SDL_DestroyTexture(gameOver);
        gameover = 1;
    }
    else if (win > 0 && life >= 0)
    {
        SDL_Texture *gameWin = IMG_LoadTexture(ren, "images/gameWin.png");
        Mix_PlayChannel(-1, sound3, 0);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, gameWin, NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(1000);
        SDL_DestroyTexture(gameWin);
        gameover = 2;
    }

    if (gameover == 1)
    {
        backColor = 35;
    }
    else if (gameover == 2)
    {
        backColor = 55;
    }
    Mix_PlayMusic(music3, -1);
    while (!restarts)
    {
        exitButton.update(mouse);
        continueButton.update(mouse);
        mouse.update();
        SDL_SetRenderDrawColor(ren, backColor, backColor, backColor, max_color);
        SDL_RenderClear(ren);
        while (SDL_PollEvent(&restart) != 0)
        {
            if (restart.type == SDL_MOUSEBUTTONUP)
            {
                if (restart.button.button == SDL_BUTTON_LEFT)
                {
                    if (continueButton.isSelected)
                    {
                        Mix_PlayChannel(-1, sound4, 0);
                        goto restarting;
                    }
                }
                if (restart.button.button == SDL_BUTTON_LEFT)
                {
                    if (exitButton.isSelected)
                    {
                        Mix_PlayChannel(-1, sound4, 0);
                        SDL_Delay(400);
                        return 0;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(ren, backColor, backColor, backColor, max_color);
        exitButton.draw();
        continueButton.draw();
        mouse.draw();
        SDL_RenderPresent(ren);
    }

    // clear window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ren);
    IMG_Quit();
    SDL_Quit();
    return 0;
}