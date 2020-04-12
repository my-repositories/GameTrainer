#include <gt_xml/table-reader.hpp>

namespace gt::xml
{
    TableReader::TableReader(const char *filePath)
    {
        this->filePath = (char*)filePath;
        this->file.open(this->filePath);
        this->tableMediator = new TableMediator(&this->file);
    }

    TableReader::~TableReader()
    {
        delete this->tableMediator;
        this->file.close();
    }

    std::vector<CheatEntry> TableReader::read(const char* fileName)
    {
        std::vector<CheatEntry> entries;
        char filePath[MAX_PATH];

        GetCurrentDirectory(sizeof(filePath), filePath);
        lstrcat(filePath, "\\cheat-tables\\");
        lstrcat(filePath, fileName);

        if (!std::filesystem::exists(filePath))
        {
            std::cout << "file '" << fileName << "' not found." << std::endl;

            return entries;
        }

        TableReader reader(filePath);

        return reader.readEntries();
    }

    std::vector<CheatEntry> TableReader::readEntries()
    {
        std::string buffer;
        std::vector<CheatEntry> entries;

        while (getline(this->file, buffer))
        {
            if (buffer.find("<CheatEntries>") != std::string::npos)
            {
                while (getline(this->file, buffer))
                {
                    if (buffer.find("</CheatEntries>") != std::string::npos)
                    {
                        break;
                    }

                    entries.push_back(this->readEntry());
                }
            }
        }

        return entries;
    }

    CheatEntry TableReader::readEntry()
    {
        std::string buffer;
        CheatEntry entry{};

        while (getline(this->file, buffer))
        {
            if (buffer.find("</CheatEntry>") != std::string::npos)
            {
                break;
            }

            this->tableMediator->setProps(buffer, entry);
        }

        return entry;
    }
}
