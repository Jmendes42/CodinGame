#include <iostream>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n; std::cin.ignore();
    int horses[n];

    for (int i = 0; i < n; i++) 
        std::cin >> horses[i]; std::cin.ignore();

    std::sort(horses, horses + n);

    int min = horses[1] - horses[0];

    for (int index = 0; index + 1 < n; index++){
        if (horses[index + 1] - horses[index] < min)
            min = horses[index + 1] - horses[index];
    }
    std::cout << min << std::endl;
}
