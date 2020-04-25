#include <gt_xml/setters/table-setter.hpp>

namespace gt::xml {
TableSetter::TableSetter(std::ifstream *file) { this->file = file; }

TableSetter::~TableSetter() = default;
} // namespace gt::xml
