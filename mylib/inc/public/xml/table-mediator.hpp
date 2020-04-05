#ifndef GAMETRAINER_TABLE_MEDIATOR_HPP
#define GAMETRAINER_TABLE_MEDIATOR_HPP

#include <vector>

#include <xml/setters/description-setter.hpp>
#include <xml/setters/variable-type-setter.hpp>
#include <xml/setters/address-setter.hpp>
#include <xml/setters/offsets-setter.hpp>

namespace GameTrainer::mylib::xml
{
    class TableMediator
    {
    public:
        explicit TableMediator(std::ifstream* file);

        ~TableMediator();

        void setProps(const std::string& buffer, CheatEntry& entry);

    private:
        std::vector<TableSetter*> setters;
    };
}

#endif //GAMETRAINER_TABLE_MEDIATOR_HPP
