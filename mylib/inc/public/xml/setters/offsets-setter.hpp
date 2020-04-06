#ifndef GAMETRAINER_OFFSETS_SETTER_HPP
#define GAMETRAINER_OFFSETS_SETTER_HPP

#include <string>

#include <xml/setters/table-setter.hpp>

namespace GameTrainer::mylib::xml
{
    class OffsetsSetter : public TableSetter
    {
    public:
        explicit OffsetsSetter(std::ifstream* file);

        ~OffsetsSetter() override;

        void set(const std::string& buffer, CheatEntry& entry) override;
    };
}

#endif //GAMETRAINER_OFFSETS_SETTER_HPP
