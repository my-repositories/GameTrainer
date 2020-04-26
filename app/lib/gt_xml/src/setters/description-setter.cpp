#include <cstring>

#include <gt_xml/setters/description-setter.hpp>

namespace gt::xml {
DescriptionSetter::DescriptionSetter(std::ifstream *file) : TableSetter(file) {}

DescriptionSetter::~DescriptionSetter() = default;

void DescriptionSetter::set(const std::string &buffer, CheatEntry &entry) {
    if (buffer.find("<Description>") == std::string::npos) {
        return;
    }

    size_t offset = buffer.find('>') + 2;
    size_t length = buffer.find('/') - offset - 2;

#ifdef OS_WINDOWS
    strcpy_s(entry.description,
             (char *)(buffer.substr(offset, length).c_str()));
#else
    strcpy(entry.description, (char *)(buffer.substr(offset, length).c_str()));
#endif
}
} // namespace gt::xml
