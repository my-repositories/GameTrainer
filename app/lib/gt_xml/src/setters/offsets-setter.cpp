#include <gt_xml/setters/offsets-setter.hpp>

namespace gt::xml
{
    OffsetsSetter::OffsetsSetter(std::ifstream* file)
            : TableSetter(file)
    {}

    OffsetsSetter::~OffsetsSetter() = default;

    void OffsetsSetter::set(const std::string& buffer, CheatEntry& entry)
    {
        if (buffer.find("<Offsets>") == std::string::npos)
        {
            return;
        }

        std::string localBuffer;

        while (getline(*this->file, localBuffer))
        {
            if (localBuffer.find("</Offsets>") != std::string::npos)
            {
                break;
            }

            size_t offset = localBuffer.find('>') + 1;
            size_t length = localBuffer.find('/') - offset - 1;

            auto value = localBuffer.substr(offset, length);
            entry.offsets[entry.offsetsCount] = std::stoul(value, nullptr, 16);
            ++entry.offsetsCount;
        }
    }
}
