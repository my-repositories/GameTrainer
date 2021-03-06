#ifndef GAMETRAINER_TABLE_SETTER_HPP
#define GAMETRAINER_TABLE_SETTER_HPP

#include <fstream>

#include <gt_xml/cheat-entry.hpp>

namespace gt::xml {
class TableSetter {
  public:
    explicit TableSetter(std::ifstream *file);

    virtual ~TableSetter();

    virtual void set(const std::string &buffer, CheatEntry &entry) = 0;

  protected:
    std::ifstream *file;
};

} // namespace gt::xml

#endif // GAMETRAINER_TABLE_SETTER_HPP
