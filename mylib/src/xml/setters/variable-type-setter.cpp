#include <xml/setters/variable-type-setter.hpp>

namespace GameTrainer::mylib::xml
{
    VariableTypeSetter::VariableTypeSetter(std::ifstream* file)
            : TableSetter(file)
    {}

    VariableTypeSetter::~VariableTypeSetter() = default;

    void VariableTypeSetter::set(const std::string& buffer, CheatEntry& entry)
    {
        if (buffer.find("<VariableType>") == std::string::npos)
        {
            return;
        }

        size_t offset = buffer.find('>') + 1;
        size_t length = buffer.find('/') - offset - 1;

        strcpy_s(entry.variableType, (char*) (buffer.substr(offset, length).c_str()));

        if (!strcmp(entry.variableType, "Byte"))
        {
            entry.size = 1;
        }
        else if (!strcmp(entry.variableType, "2 Bytes"))
        {
            entry.size = 2;
        }
        else
        {
            entry.size = 4;
        }
    }
}
