#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

template<typename T>
void    msg(const T &msg) {
    std::cerr << msg << std::endl;
}

// \\\\\\\\\\\\\\\ COORDINATES ///////////////
class Coordinates {
    int _x;
    int _y;
    
    void    _swap(Coordinates &);
    public:
                        Coordinates() = default;
                        Coordinates(const int &x, const int &y): _x(x), _y(y) {}
                        Coordinates(Coordinates &&rhs) noexcept: 
                            _x(std::move(rhs._x)),  _y(std::move(rhs._y)) {rhs._reset();}

        Coordinates&    operator = (Coordinates) noexcept;
        bool            operator == (const Coordinates &) const;
        bool            operator <= (const Coordinates &) const;


        int             _getX() const;
        int             _getY() const;
        void            _reset();
};

void    Coordinates::_reset() {
    _x = 0;
    _y = 0;
    }

void    Coordinates::_swap(Coordinates &rhs) {
    std::swap(rhs._x, _x);
    std::swap(rhs._y, _y);
    }

Coordinates&    Coordinates::operator = (Coordinates rhs) noexcept {
    _swap(rhs);
    rhs._reset();
    return *this;
    }

bool            Coordinates::operator == (const Coordinates &rhs) const {
    if (_x == rhs._x && _y == rhs._y)
        return true;
    else
        return false;
    }

bool            Coordinates::operator <= (const Coordinates &rhs) const {
    if ((_x - rhs._x) * (_x - rhs._x) +
        (_y - rhs._y) * (_y - rhs._y) <= 2000 * 2000)
            return true;
    else
        return false;
    }

int    Coordinates::_getX() const {
            return _x;
    }

int    Coordinates::_getY() const {
            return _y;
        }
//

//\\\\\\\\\\\\\\\ CHARACTERS ///////////////
class Character {
    int             _id;
    Coordinates     _position;
    bool            _lifeStatus;
    
    Character();

    protected:
        Character(const int &id, const unsigned &x, const unsigned &y) :
             _id(id), _lifeStatus(true), _position(Coordinates(x, y)) {};

        Character(Character && rhs) noexcept: 
            _id(std::move(rhs._getId())), _position(std::move(rhs._getPosition())), _lifeStatus(true) {}

        void            _printPosition();
        virtual void            _swap(Character &);

        public:

            Character       &operator = (Character ) noexcept;

            virtual void    _reset();
            virtual void    _print() const;
            int             _getId() const;
            bool            _getStatus() const;                              
            Coordinates     &_getPosition() ;
            void            _setStatus(const bool &);                              
            void            _setPosition(Coordinates &);
            void            _setPosition(const int &, const int &);
};

Character   &Character::operator = (Character rhs) noexcept {
    _swap(rhs);
    rhs._reset();
    return *this;
    }

void    Character::_swap(Character &rhs)  {
    std::swap(_id, rhs._id);
    std::swap(_position, rhs._position);
    std::swap(_lifeStatus, rhs._lifeStatus);
    }

void    Character::_reset() {
    msg("GETS HERE");
    _id = -1;
    _lifeStatus = false;
    _position = Coordinates(-1, -1);
    }

std::ostream    &operator << (std::ostream &output, const Coordinates &coordinates) {
    output << coordinates._getX() << ' ' << coordinates._getY();
    return output;
    }

std::ostream    &operator << (std::ostream &output, Character &character) {
    output << "Human " << character._getId() << character._getPosition() << std::endl;
    return output;
    }

void    Character::_setStatus(const bool &status) {
    _lifeStatus = status;
    }

bool    Character::_getStatus() const {
    return _lifeStatus;
    }

Coordinates     &Character::_getPosition()  {
    return _position;
    }

void    Character::_setPosition(Coordinates &coordinates) {
    _position = std::move(coordinates);
    }

void    Character::_printPosition() {
    std::cerr << this;
    }

int            Character::_getId() const {
            return _id;
    }

void            Character::_setPosition(const int &x, const int &y) {
    _position = std::move(Coordinates(x, y));
    }

void    Character::_print() const {
    std::cerr << "ID " << _id << " Position "<< _position << " Status " << _lifeStatus << std::endl;
}
//

//\\\\\\\\\\\\\\\ HUMANS ///////////////

class Human: public Character {

    public:
        Human(Human && rhs) noexcept: 
            Character(std::move(rhs)) {}

        Human(const unsigned &id, const unsigned &x, const unsigned &y):
            Character(id, x, y) {}

        Human   &operator = (Human rhs) noexcept;
};

Human   &Human::operator = (Human rhs) noexcept {
    _swap(rhs);
    rhs._reset();
    return *this;
    }


// 

// \\\\\\\\\\\\\\\ ZOMBIES ///////////////
class Zombie: public Character {
    Coordinates _nextMove;

    void    _swap(Zombie &);

    public:

        Zombie(Zombie && rhs) noexcept: 
                Character(std::move(rhs)), _nextMove(std::move(rhs._nextMove)) {msg("ZOMBIE SWAP");}

        Zombie(const unsigned &id, const unsigned &x, const unsigned &y):
            Character(id, x, y) {}

        Zombie   &operator = (Zombie) noexcept;

        void        _reset();
        Coordinates &_getNext();
        void        _setNext(const int &, const int &);
        void        _setNext(Coordinates &);
        void    _kill(std::vector<Human> &);
        void    _print() ;
};

void    Zombie::_print()  {
    std::cerr << "ID " << _getId() << " Position "<< _getPosition() << " Next " << _nextMove << std::endl;
}

void        Zombie::_setNext( Coordinates &rhs) {
    _nextMove = std::move(rhs);
}

void    Zombie::_swap(Zombie &rhs)  {
    Character::_swap(rhs);
    std::swap(_nextMove, rhs._nextMove);
    rhs._reset();
    }

Zombie   &Zombie::operator = (Zombie rhs) noexcept {
    _swap(rhs);
    return *this;
    }

void    Zombie::_kill(std::vector<Human> &human) {
    std::vector<Human>::iterator it;

    it = human.begin();
    for (int i = 0; i < human.size(); i++) {
        //std::cerr << "Z " << _getPosition() << " H " << human[i]._getPosition() << std::endl;
        if (_getPosition() == human[i]._getPosition()) {
            std::cerr << "Human " << human[i]._getId() << " was just _killed by zombie " << _getId() << std::endl;
            human.erase(it + i);
        }
    }
    }

void    Zombie::_reset() {
    _setStatus(false);
    _setNext(-1, -1);
    _setPosition(-1, -1);
    }

void    Zombie::_setNext(const int &x, const int &y) {
    _nextMove = Coordinates(x, y);
    }

Coordinates &Zombie::_getNext() {
    return _nextMove;
    }
//


//\\\\\\\\\\\\\\\ ASH ///////////////
class Ash {
    const std::string   _id;
    Coordinates         _position;
    
    public:
        Ash(): _id("Ash") {}

        Coordinates &_getPosition();
        void        _setPosition(const int &, const int &);
        int        _kill(std::vector<Zombie> &, const int &) const;
};


Coordinates &Ash::_getPosition() {
    return _position;
    }

void        Ash::_setPosition(const int &x, const int &y) {
    _position = Coordinates(x, y);
    }

/*int    Ash::_kill(std::vector<Zombie> &zombie) const {
    int ret = 1;
    std::vector<Zombie>::iterator it;

    it = zombie.begin();
    while (ret == 1) {
        ret = 2;
        for (int i = 0; i < zombie.size(); i++) {
            //std::cerr << "A " << _position << " Z " << zombie[i]._getPosition() << " Next " << zombie[i]._getNext() << std::endl;
            if (zombie[i]._getPosition() <= _position || zombie[i]._getNext() <= _position) {
                ret = 1;
                std::cerr << "Ash killed Zombie " << zombie[i]._getId() << " in " << zombie[i]._getPosition()
                    << " next move " << zombie[i]._getNext() << std::endl;
                zombie.erase(it + i);
            }
        }
    }
    return ret;
    }*/


int    Ash::_kill(std::vector<Zombie> &zombie, const int &i) const {
    int ret = 1;
    std::vector<Zombie>::iterator it;

    it = zombie.begin();
    //std::cerr << "A " << _position << " Z " << zombie[i]._getPosition() << " Next " << zombie[i]._getNext() << std::endl;
    if (zombie[i]._getPosition() <= _position || zombie[i]._getNext() <= _position) {
        ret = 1;
        std::cerr << "Ash killed Zombie " << zombie[i]._getId() << " in " << zombie[i]._getPosition()
            << " next move " << zombie[i]._getNext() << std::endl;
        zombie.erase(it + i);
    }
    return ret;
}


//

// \\\\\\\\\\\\\\\ GAME ///////////////

void    zombies(std::vector<Zombie> &zombie, unsigned zombie_count, const int &turn, const Ash &ash) {
    static unsigned lock;
    if (!lock)
        lock = 1;
    for (unsigned i = 0; i < zombie_count; i++) {
        unsigned zombie_id;
        unsigned zombie_x;
        unsigned zombie_y;
        unsigned zombie_xnext;
        unsigned zombie_ynext;
        std::cin >> zombie_id >> zombie_x >> zombie_y >> zombie_xnext >> zombie_ynext; std::cin.ignore();

        
        /*if (turn > 1)
            ash._kill(zombie, i);*/

        if (lock == 1) {
            zombie.push_back(Zombie(zombie_id, zombie_x, zombie_y));
        }
        else if (lock > 1) {
            /*std::cerr << "ZOMBIE ID " << zombie[i]._getId() << " && " << i <<
                 " Next " << zombie_xnext << ' ' << zombie_ynext << std::endl;*/
            zombie[i]._setNext(zombie_xnext, zombie_ynext);
            zombie[i]._setPosition(zombie_x, zombie_y);
        }
        if (turn > 1)
            ash._kill(zombie, i);
    }
    if (lock)
        lock++;
}

void    humans(std::vector<Human> &human, unsigned human_count) {
    static unsigned lock;

    if (!lock)
        lock = 1;
    for (unsigned i = 0; i < human_count; i++) {
        unsigned human_x;
        unsigned human_y;
        unsigned human_id;
        std::cin >> human_id >> human_x >> human_y; std::cin.ignore();

        
        if (lock == 1) {
            human.push_back(Human(human_id, human_x, human_y));
        }
        else if (!lock || lock > 1) 
            human[i]._setPosition(human_x, human_y);
    }
    if (lock)
        lock++;
}

void    verifyDeads(std::vector<Human> &human, std::vector<Zombie> &zombie, const Ash &ash,
    const unsigned &human_count, const unsigned &zombie_count) {
        for (int i = 0; i < zombie.size(); i++) {
            zombie[i]._kill(human);
        }
}

int main()
{
    unsigned            x;
    unsigned            y;
    Ash                 ash;
    static unsigned     lock;
    unsigned            turn;
    std::vector<Human>  human;
    std::vector<Zombie> zombie;
    unsigned            human_count;
    unsigned            zombie_count;

    turn = 0;
    while (1) {
        if (!lock)
            lock = 0;
        std::cin >> x >> y; std::cin.ignore();
        std::cin >> human_count; std::cin.ignore();
        //std::cerr << "HUMANS " << human_count << std::endl;
        ash._setPosition(x, y);

        /*if (turn > 1)
            ash._kill(zombie);*/

        if (turn == 0)
            human.reserve(human_count);
        humans(human, human_count);

        std::cin >> zombie_count; std::cin.ignore();
        //std::cerr  << "ZOMBIES " << zombie_count << std::endl;

        


        if (turn == 0)
            zombie.reserve(zombie_count);
        zombies(zombie, zombie_count, turn, ash);

        /*if (turn > 1)
            ash._kill(zombie);*/
            

        std::cout << human[0]._getPosition() << std::endl;

        /*if (turn > 0)
            ash._kill(zombie);*/

        turn++;
        if (turn > 0)
            verifyDeads(human, zombie, ash, human_count, zombie_count);






        msg("COUNTING HUMAN");        
        for (int i = 0; i < human.size(); i++)
            human[i]._print();
        msg("COUNTING ZOMBIE"); 
        for (int i = 0; i < zombie.size(); i++)
            zombie[i]._print();       
    }
}
