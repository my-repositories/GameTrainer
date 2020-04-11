#include <setters/table-setter.hpp>

namespace GameTrainer::mylib::xml
{
    TableSetter::TableSetter(std::ifstream *file)
    {
        this->file = file;
    }

    TableSetter::~TableSetter() = default;
}
