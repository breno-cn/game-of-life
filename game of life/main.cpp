#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <SDL2/SDL.h>

#include "game.hpp"

int main(int argc, char *argv[])
{
    Game game;
    char title[50];

    int width = 1024;
    int height = 768;
    // Criação e inicialização de janela
    SDL_Window *window = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::cout << "Erro na inicializacao de janela: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "Game of Life",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr)
    {
        std::cout << "Erro na criacao de janela: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Criação de renderizador e texturas
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, width, height);

    SDL_Texture *texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDHT,
        HEIGHT
    );

    uint32_t pixels[WIDHT * HEIGHT];
    while (true)
    {
        game.update();
        //g.draw();
        SDL_Event e;

        while (SDL_PollEvent(&e));

        if (e.type == SDL_QUIT) return 0;
            
        for (int i = 0; i < WIDHT * HEIGHT; i++)
        {
            int pixel = game.output[i];
            pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
        }

        SDL_UpdateTexture(texture, nullptr, pixels, WIDHT * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        sprintf(title, "Game of Life\tliving cells: %d", game.n_cells);
        SDL_SetWindowTitle(window, title);

        //std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

    return 0;
}