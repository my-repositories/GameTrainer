#ifndef GAMETRAINER_DESCRIPTION_SETTER_HPP
#define GAMETRAINER_DESCRIPTION_SETTER_HPP

#include <string>

#include <setters/table-setter.hpp>

namespace GameTrainer::mylib::xml
{
    class DescriptionSetter : public TableSetter
    {
    public:
        explicit DescriptionSetter(std::ifstream* file);

        ~DescriptionSetter() override;

        void set(const std::string& buffer, CheatEntry& entry) override;
    };
}

#endif //GAMETRAINER_DESCRIPTION_SETTER_HPP
