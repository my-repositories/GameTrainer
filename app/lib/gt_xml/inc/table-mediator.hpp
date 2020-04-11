#ifndef GAMETRAINER_TABLE_MEDIATOR_HPP
#define GAMETRAINER_TABLE_MEDIATOR_HPP

#include <vector>

#include <setters/description-setter.hpp>
#include <setters/variable-type-setter.hpp>
#include <setters/address-setter.hpp>
#include <setters/offsets-setter.hpp>

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
