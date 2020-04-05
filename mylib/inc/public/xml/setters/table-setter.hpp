#ifndef GAMETRAINER_TABLE_SETTER_HPP
#define GAMETRAINER_TABLE_SETTER_HPP

#include <fstream>

#include <xml/cheat-entry.hpp>

namespace GameTrainer::mylib::xml
{
    class TableSetter
    {
    public:
        explicit TableSetter(std::ifstream *file);

        virtual ~TableSetter();

        virtual void set(const std::string &buffer, CheatEntry &entry) = 0;

    protected:
        std::ifstream *file;
    };

}

#endif //GAMETRAINER_TABLE_SETTER_HPP
