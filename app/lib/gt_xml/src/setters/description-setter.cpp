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

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    strcpy_s(entry.description,
             (char *)(buffer.substr(offset, length).c_str()));
#else
    strcpy(entry.description, (char *)(buffer.substr(offset, length).c_str()));
#endif
}
} // namespace gt::xml
