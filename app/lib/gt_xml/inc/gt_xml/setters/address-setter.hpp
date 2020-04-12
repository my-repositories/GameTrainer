#ifndef GAMETRAINER_ADDRESS_SETTER_HPP
#define GAMETRAINER_ADDRESS_SETTER_HPP

#include <string>

#include <gt_xml/setters/table-setter.hpp>

namespace gt::xml
{
    class AddressSetter : public TableSetter
    {
    public:
        explicit AddressSetter(std::ifstream* file);

        ~AddressSetter() override;

        void set(const std::string& buffer, CheatEntry& entry) override;
    };
}

#endif //GAMETRAINER_ADDRESS_SETTER_HPP
