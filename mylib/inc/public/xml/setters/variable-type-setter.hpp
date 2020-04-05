#ifndef GAMETRAINER_VARIABLE_TYPE_SETTER_HPP
#define GAMETRAINER_VARIABLE_TYPE_SETTER_HPP

#include <string>

#include <xml/setters/table-setter.hpp>

namespace GameTrainer::mylib::xml
{
    class VariableTypeSetter : public TableSetter
    {
    public:
        explicit VariableTypeSetter(std::ifstream* file);

        virtual ~VariableTypeSetter();

        void set(const std::string& buffer, CheatEntry& entry) override;
    };
}

#endif //GAMETRAINER_VARIABLE_TYPE_SETTER_HPP
