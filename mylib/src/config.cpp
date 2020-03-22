#include <config.hpp>

namespace GameTrainer::mylib
{
    Config::Config()
    {
        this->field = 24;
    }

    int Config::method(const int x) {
        this->field = x + this->field;
        return this->field;
    }
}
