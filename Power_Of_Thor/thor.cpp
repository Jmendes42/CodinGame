#include <iostream>

class Light       // Light/objective position class
{
    int _light_x; // the X position of the light of power
    int _light_y; // the Y position of the light of power

    public:
        Light();

        int getX() const;
        int getY() const;
};


// Light/objective class methods
Light::Light() {
    std::cin >> _light_x >> _light_y; std::cin.ignore();
}

int Light::getX() const {
    return _light_x;
}

int Light::getY() const {
    return _light_y;
}



class Thor           // Thor class
{
    int _initial_tx; // Thor's starting X position
    int _initial_ty; // Thor's starting Y position

    public:
        Thor();
        
        void operator < (const Light &light);
        void operator > (const Light &light);
};


// Thor class methods
Thor::Thor() {
    std::cin >> _initial_tx >> _initial_ty; std::cin.ignore();
}

void Thor::operator < (const Light &light) {
    if (_initial_ty < light.getY()) {
        _initial_ty ++;
        std::cout << "S";
    }
    if (_initial_tx < light.getX()) {
        _initial_tx++;
        std::cout << "E";
    }
}

void    Thor::operator > (const Light &light) {
    if (_initial_ty > light.getY()) {
        _initial_ty--;
        std::cout << "N";
    }
    if (_initial_tx > light.getX()) {
        _initial_tx--;
        std::cout << "W";
    }
}

int main()
{
    Light light;
    Thor thor;

    // game loop
    while (1) {
        thor < light;
        thor > light;
        std::cout << std::endl;
    }
}
