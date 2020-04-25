#include <cstring>

#include <gt_xml/setters/address-setter.hpp>

namespace gt::xml {
AddressSetter::AddressSetter(std::ifstream *file) : TableSetter(file) {}

AddressSetter::~AddressSetter() = default;

void AddressSetter::set(const std::string &buffer, CheatEntry &entry) {
    if (buffer.find("<Address>") == std::string::npos ||
        !strcmp(entry.variableType, (char *)"Auto Assembler Script")) {
        return;
    }

    // set Module
    size_t offset = buffer.find('>') + 2;
    size_t length = buffer.find('+') - offset - 1;

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    strcpy_s(entry.module, (char *)(buffer.substr(offset, length).c_str()));
#else
    strcpy(entry.module, (char *)(buffer.substr(offset, length).c_str()));
#endif

    // set Address
    offset = buffer.find('+') + 1;
    length = buffer.find('/') - offset - 1;
    entry.address = std::stoul(buffer.substr(offset, length), nullptr, 16);
}
} // namespace gt::xml
