#include "button.h"
#include <iostream>

const unsigned long long screenWidth = 640, screenHeight = 480;
const int paddleY = screenHeight - 5, paddleHight = 3;
int ball = 1, paddle = 1, ballXDir = 1, ballYDir = 1, paddleX = 0, paddleXDir = -1, paddleWidth = 64, ballWidth = 8, ballHight = 8, ballSpeed = 1, multiply = 10, life = 2, brickHight = 20, brickWidth = 32, ballX = 0, ballY = 0, win = 0, countVolume = 0;
int paddleCenter = paddleWidth / 2, max_color = 255, BGmenu = 50, BGwin = 55, BGlose = 35, wall = 20, temprand, bonusX, bonusY, bonusYDir = 2, bonusWidth = 7, bonusHight = 5, errorcount = 0, sumforwin=0;
bool quit = false, gameMenu = false, options = false, game = false, ease = false, restarts = false, gameeee = false, magnet = true, bonus = false;

int init = Mix_Init(0);
SDL_Window *window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

int main(int argc, char *argv[])
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *music = Mix_LoadMUS("audio/awesomeness.wav");
    if (music == NULL)
    {
        errorcount++;
    }
    Mix_Chunk *sound = Mix_LoadWAV("audio/click_2.wav");
    if (sound == NULL)
    {
        errorcount++;
    }
    Mix_Music *music2 = Mix_LoadMUS("audio/audio.wav");
    if (music2 == NULL)
    {
        errorcount++;
    }
    Mix_Chunk *sound2 = Mix_LoadWAV("audio/negative_2.wav");
    if (sound2 == NULL)
    {
        errorcount++;
    }
    Mix_Chunk *sound3 = Mix_LoadWAV("audio/positive.wav");
    if (sound3 == NULL)
    {
        errorcount++;
    }
    Mix_Chunk *sound4 = Mix_LoadWAV("audio/click.wav");
    if (sound4 == NULL)
    {
        errorcount++;
    }
    Mix_Music *music3 = Mix_LoadMUS("audio/pause.wav");
    if (music3 == NULL)
    {
        errorcount++;
    }
    Mix_VolumeMusic(32);

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

    SDL_Texture *menuBackground = IMG_LoadTexture(ren, "images/backGround.png");
    if (menuBackground == NULL)
    {
        errorcount++;
    }
    SDL_Texture *optionBackGround = IMG_LoadTexture(ren, "images/options.png");
    if (optionBackGround == NULL)
    {
        errorcount++;
    }
    SDL_Texture *brickTexture = IMG_LoadTexture(ren, "images/brick.png");
    if (brickTexture == NULL)
    {
        errorcount++;
    }
    SDL_Texture *unbrickTexture = IMG_LoadTexture(ren, "images/brickunbreakable.png");
    if (unbrickTexture == NULL)
    {
        errorcount++;
    }
    SDL_Texture *ballTexture = IMG_LoadTexture(ren, "images/ball.png");
    if (ballTexture == NULL)
    {
        errorcount++;
    }
    SDL_Texture *paddleTexture = IMG_LoadTexture(ren, "images/paddle.png");
    if (paddleTexture == NULL)
    {
        errorcount++;
    }
    SDL_Texture *gameOver = IMG_LoadTexture(ren, "images/gameOver.png");
    if (gameOver == NULL)
    {
        errorcount++;
    }
    SDL_Texture *gameWin = IMG_LoadTexture(ren, "images/gameWin.png");
    if (gameWin == NULL)
    {
        errorcount++;
    }
    SDL_Texture *BGgame = IMG_LoadTexture(ren, "images/backGroundGame.png");
    if (BGgame == NULL)
    {
        errorcount++;
    }
    SDL_Texture *bonusTexture = IMG_LoadTexture(ren, "images/Bonus.png");
    if (bonusTexture == NULL)
    {
        errorcount++;
    }

    if (errorcount > 0)
    {
        return 1;
    }

    SDL_Event e_menu, e, paddleEvent, option, restart;
    Mix_PlayMusic(music, -1);

    while (!gameMenu)
    {
        mouse.update();
        // if (options == false)
        // {
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
                            gameMenu = true;
                        }
                        if (optiButton.isSelected)
                        {
                            Mix_PlayChannel(-1, sound, 0);
                            // options = true;
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
                SDL_SetRenderDrawColor(ren, BGmenu, BGmenu, BGmenu, max_color);
                SDL_RenderClear(ren);
                SDL_RenderCopy(ren, menuBackground, NULL, NULL);
                startButton.draw();
                optiButton.draw();
                exitButton.draw();
            }
        // }
        // else
        // {
        //     backButton.update(mouse);
        //     easeButton.update(mouse);
        //     hardButton.update(mouse);
        //     volumeButton.update(mouse);
        //     while (SDL_PollEvent(&option))
        //     {
        //         if (option.type == SDL_KEYUP)
        //         {
        //             if (option.key.keysym.sym == SDLK_ESCAPE)
        //             {
        //                 return 0;
        //             }
        //         }
        //         if (option.type == SDL_MOUSEBUTTONUP)
        //         {
        //             if (option.button.button == SDL_BUTTON_LEFT)
        //             {
        //                 if (backButton.isSelected)
        //                 {
        //                     Mix_PlayChannel(-1, sound, 0);
        //                     options = false;
        //                 }
        //             }
        //         }
        //         if (option.type == SDL_MOUSEBUTTONUP)
        //         {
        //             if (option.button.button == SDL_BUTTON_LEFT)
        //             {
        //                 if (easeButton.isSelected)
        //                 {
        //                     Mix_PlayChannel(-1, sound, 0);
        //                     ease = false;
        //                 }
        //                 if (hardButton.isSelected)
        //                 {
        //                     Mix_PlayChannel(-1, sound, 0);
        //                     paddleWidth = 64;
        //                 }
        //             }
        //         }
        //         if (option.type == SDL_MOUSEBUTTONUP)
        //         {
        //             if (option.button.button == SDL_BUTTON_LEFT)
        //             {
        //                 if (volumeButton.isSelected)
        //                 {
        //                     Mix_PlayChannel(-1, sound, 0);
        //                     countVolume++;
        //                     if (countVolume % 5 == 0)
        //                     {
        //                         Mix_VolumeMusic(32);
        //                     }
        //                     if (countVolume % 5 == 1)
        //                     {
        //                         Mix_VolumeMusic(64);
        //                     }
        //                     if (countVolume % 5 == 2)
        //                     {
        //                         Mix_VolumeMusic(96);
        //                     }
        //                     if (countVolume % 5 == 3)
        //                     {
        //                         Mix_VolumeMusic(128);
        //                     }
        //                     if (countVolume % 5 == 4)
        //                     {
        //                         Mix_VolumeMusic(0);
        //                     }
        //                 }
        //             }
        //         }
        //         SDL_SetRenderDrawColor(ren, BGmenu, BGmenu, BGmenu, max_color);
        //         SDL_RenderClear(ren);
        //         SDL_RenderCopy(ren, optionBackGround, NULL, NULL);
        //         backButton.draw();
        //         easeButton.draw();
        //         hardButton.draw();
        //         volumeButton.draw();
        //     }
        // }
        mouse.draw();
        SDL_RenderPresent(ren);
        SDL_Delay(10);
    }

    if (ease == true)
    {
        ballSpeed = 3;
    }
    if (ease == false)
    {
        ballSpeed = 1;
    }

    while (!gameeee)
    {
        restarts = false;
        win = 0;
        life = 2;
        quit = false;
        multiply = 10;
        magnet = true;
        SDL_PumpEvents();
        SDL_GetMouseState(&paddleCenter, NULL);
        paddleX = paddleCenter - paddleWidth / 2;
        ballX = paddleCenter - ballWidth / 2;
        ballY = paddleY - ballHight;
        int brick[15][20];
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                brick[i][j] = rand() % 2 + 1;
            }
        }
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (brick[i][j] == 1 && brick[i - 1][j] == 2 && brick[i + 1][j] == 2 && brick[i][j - 1] == 2 && brick[i][j + 1] == 2)
                {
                    brick[i - 1][j] = 1;
                }
                if (brick[i][j] == 2 && (brick[i - 1][j] == 2 || brick[i + 1][j] == 2 || brick[i][j - 1] == 2 || brick[i][j + 1] == 2))
                {
                    brick[i][j] = 1;
                }
                if (brick[i][j] == 1 && brick[i][j + 1] == 2 && brick[i][j - 1] == 1 && brick[i - 1][j] == 2)
                {
                    brick[i][j + 1] = 1;
                }
                if (i == 0 || j == 0 || j == 19)
                {
                    brick[i][j] = 0;
                }
                if(brick[i][j] == 1)
                {
                sumforwin += brick[i][j];
                }
            }
        }
        int gameover = 0;
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
                    }
                }

                SDL_RenderClear(ren);
                SDL_RenderCopy(ren, BGgame, NULL, NULL);
                // draw bricks and check for collision
                for (int i = 0; i < 15; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        SDL_Rect rectbrick = {j * brickWidth, i * brickHight, brickWidth - 1, brickHight - 1};
                        if (brick[i][j] == 1)
                        {
                            win++;
                            SDL_RenderCopy(ren, brickTexture, NULL, &rectbrick);
                            if (ballX + ballWidth - 1 >= j * brickWidth && ballX <= j * brickWidth + brickWidth && ballY + ballHight - 1 == i * brickHight && ballYDir == 1)
                            {
                                brick[i][j] = 0;
                                ballYDir = -1;
                                temprand = rand() % 100;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballX + ballWidth - 1 >= j * brickWidth && ballX <= j * brickWidth + brickWidth && ballY == i * brickHight + brickHight && ballYDir == -1)
                            {
                                brick[i][j] = 0;
                                ballYDir = 1;
                                temprand = rand() % 100;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballY + ballHight - 1 >= i * brickHight && ballY <= i * brickHight + brickHight && ballX + ballWidth - 1 == j * brickWidth && ballXDir == 1)
                            {
                                brick[i][j] = 0;
                                ballXDir = -1;
                                temprand = rand() % 100;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballY + ballHight - 1 >= i * brickHight && ballY <= i * brickHight + brickHight && ballX == j * brickWidth + brickWidth && ballXDir == -1)
                            {
                                brick[i][j] = 0;
                                ballXDir = 1;
                                temprand = rand() % 100;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                        }
                        if (brick[i][j] == 2)
                        {
                            SDL_RenderCopy(ren, unbrickTexture, NULL, &rectbrick);
                            if (ballY + ballHight - 1 >= i * brickHight && ballY <= i * brickHight + brickHight && ballX == j * brickWidth + brickWidth && ballXDir == -1)
                            {
                                ballXDir = 1;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballX + ballWidth - 1 >= j * brickWidth && ballX <= j * brickWidth + brickWidth && ballY + ballHight - 1 == i * brickHight && ballYDir == 1)
                            {
                                ballYDir = -1;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballX + ballWidth - 1 >= j * brickWidth && ballX <= j * brickWidth + brickWidth && ballY == i * brickHight + brickHight && ballYDir == -1)
                            {
                                ballYDir = 1;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                            if (ballY + ballHight - 1 >= i * brickHight && ballY <= i * brickHight + brickHight && ballX + ballWidth - 1 == j * brickWidth && ballXDir == 1)
                            {
                                ballXDir = -1;
                                Mix_PlayChannel(-1, sound4, 0);
                            }
                        }
                    }
                }

                if(win == sumforwin)
                {
                    game = false;
                    win = 0;
                    sumforwin = 0;
                }
                else
                {
                    win = 0;
                }

                if (temprand > 90)
                {
                    bonus = true;
                    bonusX = ballX;
                    bonusY = ballY;
                }
                if (bonus == true)
                {
                    temprand = 0;
                    bonusY += bonusYDir;
                    if (paddleX + paddleWidth >= bonusX && paddleX <= bonusX + bonusWidth && bonusY + bonusHight >= paddleY && bonusY + bonusHight <= screenHeight)
                    {
                        bonus = false;
                        magnet = true;
                    }
                    else if (bonusY >= screenHeight)
                    {
                        bonus = false;
                    }
                    SDL_Rect rectbonus = {bonusX, bonusY, bonusWidth, bonusHight};
                    SDL_RenderCopy(ren, bonusTexture, NULL, &rectbonus);
                }
                else
                {
                    bonusX = screenWidth + bonusWidth;
                    bonusY = 0;
                }

                SDL_PumpEvents();
                SDL_GetMouseState(&paddleCenter, NULL);
                paddleX = paddleCenter - paddleWidth / 2;
                if (magnet == true && ballX + ballWidth >= paddleX && ballX <= paddleX + paddleWidth && ballY + ballHight >= paddleY)
                {
                    while (magnet)
                    {
                        while (SDL_PollEvent(&e))
                        {
                            if (e.type == SDL_KEYUP)
                            {
                                if (e.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    return 0;
                                }
                            }
                            if (e.type == SDL_MOUSEBUTTONUP)
                            {
                                if (e.button.button == SDL_BUTTON_LEFT)
                                {
                                    magnet = false;
                                }
                            }
                        }

                        SDL_PumpEvents();
                        SDL_GetMouseState(&paddleCenter, NULL);
                        paddleX = paddleCenter - paddleWidth / 2;
                        ballX = paddleCenter - ballWidth / 2;
                        ballY = paddleY - ballHight;
                        ballYDir = -1;

                        for (int i = 0; i < 15; i++)
                        {
                            for (int j = 0; j < 20; j++)
                            {
                                SDL_Rect rectbrick = {j * brickWidth, i * brickHight, brickWidth - 1, brickHight - 1};
                                if (brick[i][j] == 1)
                                {
                                    SDL_RenderCopy(ren, brickTexture, NULL, &rectbrick);
                                }
                                if (brick[i][j] == 2)
                                {
                                    SDL_RenderCopy(ren, unbrickTexture, NULL, &rectbrick);
                                }
                            }
                        }
                        SDL_RenderPresent(ren);
                        SDL_Rect rectpaddle = {paddleX, paddleY, paddleWidth, paddleHight};
                        SDL_Rect rectball = {ballX, ballY, ballWidth, ballHight};
                        SDL_RenderCopy(ren, BGgame, NULL, NULL);
                        SDL_RenderCopy(ren, ballTexture, NULL, &rectball);
                        SDL_RenderCopy(ren, paddleTexture, NULL, &rectpaddle);
                    }
                }

                ballX += ballXDir;
                ballY += ballYDir;
                if (ballX <= wall)
                {
                    ballXDir = 1;
                    Mix_PlayChannel(-1, sound4, 0);
                }
                if (ballX >= screenWidth - ballWidth - wall)
                {
                    ballXDir = -1;
                    Mix_PlayChannel(-1, sound4, 0);
                }
                if (ballY == wall)
                {
                    ballYDir = 1;
                    Mix_PlayChannel(-1, sound4, 0);
                }
                if (ballY == screenHeight)
                {
                    ball = 0;
                    paddle = 0;
                }
                if (ballX + ballWidth >= paddleX && ballX <= paddleX + paddleWidth && ballY >= paddleY - ballHight)
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
                        // if (ballX + ballWidth / 2 < paddleCenter - 14)
                        // {
                        //     ballXDir = -2;
                        // }
                    }
                    else if (ballX + ballWidth / 2 > paddleCenter)
                    {
                        if (ballX + ballWidth / 2 > paddleCenter + 3)
                        {
                            ballXDir = 1;
                        }
                        // if (ballX + ballWidth / 2 > paddleCenter + 14)
                        // {
                        //     ballXDir = 2;
                        // }
                    }
                    ballYDir = -ballYDir;
                    Mix_PlayChannel(-1, sound4, 0);
                }

                // update screen
                if (ball == 1)
                {
                    SDL_Rect rectball = {ballX, ballY, ballWidth, ballHight};
                    SDL_RenderCopy(ren, ballTexture, NULL, &rectball);
                }
                if (paddle == 1)
                {
                    SDL_Rect rectpaddle = {paddleX, paddleY, paddleWidth, paddleHight};
                    SDL_RenderCopy(ren, paddleTexture, NULL, &rectpaddle);
                }
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

                
                SDL_Delay(ballSpeed * multiply);
            }
        }

        SDL_SetRenderDrawColor(ren, max_color, max_color, max_color, max_color);
        SDL_RenderClear(ren);
        if (life == 0 && paddle == 0)
        {
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
            Mix_PlayChannel(-1, sound3, 0);
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, gameWin, NULL, NULL);
            SDL_RenderPresent(ren);
            SDL_Delay(1000);
            SDL_DestroyTexture(gameWin);
            gameover = 2;
        }
        int backColor;
        if (gameover == 1)
        {
            backColor = BGlose;
        }
        else if (gameover == 2)
        {
            backColor = BGwin;
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
                            restarts = true;
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
            SDL_Delay(10);
        }
    }

    // clear window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(ren);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    return 0;
}