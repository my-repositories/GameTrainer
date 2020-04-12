#ifndef GAMETRAINER_DESCRIPTION_SETTER_HPP
#define GAMETRAINER_DESCRIPTION_SETTER_HPP

#include <string>

#include <gt_xml/setters/table-setter.hpp>

namespace gt::xml
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
