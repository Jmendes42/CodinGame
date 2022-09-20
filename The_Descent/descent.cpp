#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/

int main()
{
    int index;
    int height;

    // game loop
    while (1) {
        height = 0;

        for (int i = 0; i < 8; i++) {
            int mountain_h; // represents the height of one mountain.
            std::cin >> mountain_h; std::cin.ignore();
            if (height < mountain_h) {
                index = i;
                height = mountain_h;
            }
        }
        std::cout << index << std::endl; // The index of the mountain to fire on.
    }
}
