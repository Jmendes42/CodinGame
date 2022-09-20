#include <iostream>

int main()
{
    // game loop
    while (1) {
        std::string enemy_1; // name of enemy 1
        std::cin >> enemy_1; std::cin.ignore();
        int dist_1; // distance to enemy 1
        std::cin >> dist_1; std::cin.ignore();
        std::string enemy_2; // name of enemy 2
        std::cin >> enemy_2; std::cin.ignore();
        int dist_2; // distance to enemy 2
        std::cin >> dist_2; std::cin.ignore();

        if (dist_1 < dist_2)
            std::cout << enemy_1 << std::endl;
        else
            std::cout << enemy_2 << std::endl;
    }
}
