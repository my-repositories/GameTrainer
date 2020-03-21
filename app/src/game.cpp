#include <game.hpp>

//namespace GameTrainer::mylib
//{
    Game::Game() {
        this->field = 21;
    }

    int Game::method(const int x) {
        this->field = x + this->field;
        return this->field;
    }
//}

