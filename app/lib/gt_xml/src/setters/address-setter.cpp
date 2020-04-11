#include <setters/address-setter.hpp>

namespace GameTrainer::mylib::xml
{
    AddressSetter::AddressSetter(std::ifstream* file)
            : TableSetter(file)
    {}

    AddressSetter::~AddressSetter() = default;

    void AddressSetter::set(const std::string& buffer, CheatEntry& entry)
    {
        if (buffer.find("<Address>") == std::string::npos
        || !strcmp(entry.variableType, (char*)"Auto Assembler Script"))
        {
            return;
        }

        // set Module
        size_t offset = buffer.find('>') + 2;
        size_t length = buffer.find('+') - offset - 1;
        strcpy_s(entry.module, (char*) (buffer.substr(offset, length).c_str()));

        // set Address
        offset = buffer.find('+') + 1;
        length = buffer.find('/') - offset - 1;
        entry.address = std::stoul(buffer.substr(offset, length), nullptr, 16);
    }
}
