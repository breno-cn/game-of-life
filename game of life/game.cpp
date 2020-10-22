#include <iostream>
#include <memory>
#include <cstring>
#include <ctime>
#include <random>
#include <stdio.h>

#include "game.hpp"

Game::Game()
{
    state  = std::make_unique<int[]>(WIDHT * HEIGHT);
    output = std::make_unique<int[]>(WIDHT * HEIGHT);

    std::memset(state.get(), 0, WIDHT * HEIGHT);
    std::memset(output.get(), 0, WIDHT * HEIGHT);
    std::srand(std::time(0));

    for (int i = 0; i < WIDHT * HEIGHT; i++)
        state[i] = std::rand() % 2;

    std::cout << "Game created!" << std::endl;
}

Game::~Game() 
{
    std::cout << "Game destroyed!" << std::endl;
}

int Game::get_output(int x, int y)
{
    if (x == -1) x = WIDHT - 1;
    else if (x == WIDHT) x = 0;

    if (y == -1) y = HEIGHT - 1;
    else if (y == HEIGHT) y = 0;

    return output[y*WIDHT + x];
}

void Game::update()
{
    n_cells = 0;
    std::memcpy(output.get(), state.get(), WIDHT * HEIGHT * sizeof(int));

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDHT; x++)
        {
            int neighbour = get_output(x - 1, y - 1) + get_output(x + 0, y - 1) + get_output(x + 1, y - 1) +
                            get_output(x - 1, y + 0) +            0             + get_output(x + 1, y + 0) +
                            get_output(x - 1, y + 1) + get_output(x + 0, y + 1) + get_output(x + 1, y + 1);

            int index = y * WIDHT + x;
            if (get_output(x, y) == 1)
            {
                state[index] =  neighbour == 2 || neighbour == 3;
                n_cells++;
            }
            else
                state[index] = neighbour == 3;

        }
    }
}
