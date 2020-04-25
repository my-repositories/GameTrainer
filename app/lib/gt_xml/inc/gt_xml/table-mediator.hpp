#ifndef GAMETRAINER_TABLE_MEDIATOR_HPP
#define GAMETRAINER_TABLE_MEDIATOR_HPP

#include <vector>

#include <gt_xml/setters/address-setter.hpp>
#include <gt_xml/setters/description-setter.hpp>
#include <gt_xml/setters/offsets-setter.hpp>
#include <gt_xml/setters/variable-type-setter.hpp>

namespace gt::xml {
class TableMediator {
  public:
    explicit TableMediator(std::ifstream *file);

    ~TableMediator();

    void setProps(const std::string &buffer, CheatEntry &entry);

  private:
    std::vector<TableSetter *> setters;
};
} // namespace gt::xml

#endif // GAMETRAINER_TABLE_MEDIATOR_HPP
