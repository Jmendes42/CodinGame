#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



// \\\\\\\\\\\\\\\ COORDINATES ///////////////
class Coordinates {
    unsigned _y;
    unsigned _x;
    
    public:
                        Coordinates() = default;
                        //~Coordinates();
                        Coordinates(const unsigned y, const unsigned x);

        Coordinates&    operator = (const Coordinates &coordinates);


        unsigned        getY() const;
        unsigned        getX() const;
};

Coordinates::Coordinates(unsigned y, unsigned x) {
    _y = y;
    _x = x;
    }

Coordinates&    Coordinates::operator = (const Coordinates &coordinates) {
    _y = coordinates.getY();
    _x = coordinates.getX();
    return *this;
    }

unsigned    Coordinates::getY() const {
            return _y;
        }

unsigned    Coordinates::getX() const {
            return _x;
    }





// 


//\\\\\\\\\\\\\\\ CHARACTERS ///////////////

class Character {
    protected:
        char  _id;
        Coordinates _position;

    public:
                                //Character();
                                //~Character();
        Coordinates     getPosition();
        void            printPosition();
        char            getId();
        void            setPosition(const Coordinates &coordinates);
};

Coordinates     Character::getPosition() {
    return _position;
    }

std::ostream    &operator << (std::ostream &output, const Coordinates &coordinates) {
    output << coordinates.getX() << ' ' << coordinates.getY();
    return output;
    }

std::ostream    &operator << (std::ostream &output, Character &character) {
    output << "Human " << character.getId() << character.getPosition() << std::endl;
    return output;
    }

void    Character::printPosition() {
    std::cerr << this;
    }

char            Character::getId() {
            return _id;
    }

void            Character::setPosition(const Coordinates &coordinates) {
    _position = coordinates;
    }
//




//\\\\\\\\\\\\\\\ HUMANS ///////////////

class Human: public Character {
    public:
        Human();
        Human(char id, const Coordinates &position);
        //~Human();
        Coordinates getPosition();

        const Human*   operator = (Human *human) const {
            return human;
        }

};

Human::Human(const char id, const Coordinates &position) {
    _id = id;
    _position = position;
}

Coordinates Human::getPosition() {
    return _position;
}


class Ash: public Character {
    const std::string _id;
    
    void    move();

    public:
            Ash();
            //~Ash();
            Ash(const Coordinates &position);
};

Ash::Ash(const Coordinates &position): _id("Ash") {
    _position = position;
}


// \\\\\\\\\\\\\\\ ZOMBIES ///////////////
class Zombie: public Character {
    unsigned         _closerH;

    public:
        Zombie(char id, const Coordinates &position) {
            _id = id;
            _position = position;
        }
        //~Zombie();

};

void    humans(Character *human, unsigned human_count) {
    static unsigned lock;
    static unsigned count;
    static unsigned counter;

    if (human_count > 1 && !lock && !counter && !count) {
        std::cerr << "LOCK" << std::endl;
        lock = 1;
        counter = 0;
        count = human_count;
    }
    for (unsigned i = 0; i < human_count; i++) {
        std::cerr << "passa aqui" << std::endl;
        char     human_id;
        unsigned human_x;
        unsigned human_y;
        std::cin >> human_id >> human_x >> human_y; std::cin.ignore();
        if (!counter && !lock) 
            human[i] = Human(human_id, Coordinates(human_y, human_x));
        else if (counter < count / 2 && lock == 1) {
            human[i] = Human(human_id, Coordinates(human_y, human_x));
            counter++;
        }
        else if (counter > count / 2 && lock == 2) {
            human[i] = Human(human_id, Coordinates(human_y, human_x));
            counter++;
        }
        else if (!lock || lock > 2)
            human[i].setPosition(Coordinates(human_y, human_x));
    }
    if (lock)
        lock++;
}

void    zombies(Character *zombie, unsigned zombie_count) {
    for (unsigned i = 0; i < zombie_count; i++) {
        char zombie_id;
        unsigned zombie_x;
        unsigned zombie_y;
        unsigned zombie_xnext;
        unsigned zombie_ynext;
        std::cin >> zombie_id >> zombie_x >> zombie_y >> zombie_xnext >> zombie_ynext; std::cin.ignore();
        zombie[i] = Zombie(zombie_id, Coordinates(zombie_y, zombie_x));
        std::cerr << zombie_id << ' ' << zombie_count <<  std::endl;
    }
}

int main()
{
    unsigned    x;
    unsigned    y;
    Character   human[20];
    Character   zombie[90];
    unsigned    human_count;
    unsigned    zombie_count;

    while (1) {
        std::cin >> x >> y; std::cin.ignore();
        Character ash = Ash(Coordinates(x, y));

        std::cin >> human_count; std::cin.ignore();
        std::cerr << "HUMANS " << human_count << std::endl;
        humans(human, human_count);

        std::cin >> zombie_count; std::cin.ignore();
        zombies(zombie, zombie_count);
        std::cout << human[0].getPosition() << std::endl;
    }
}
