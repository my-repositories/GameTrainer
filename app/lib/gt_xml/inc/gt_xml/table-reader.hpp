#ifndef GAMETRAINER_TABLE_READER_HPP
#define GAMETRAINER_TABLE_READER_HPP

#include <filesystem>
#include <iostream>

#include <gt_xml/table-mediator.hpp>

namespace gt::xml
{
    class TableReader
    {
    public:
        static std::vector<CheatEntry> read(const char* fileName);

    private:
        explicit TableReader(const char* filePath);

        ~TableReader();

        char* filePath;
        std::ifstream file;
        TableMediator* tableMediator;

        [[nodiscard]] std::vector<CheatEntry> readEntries();

        [[nodiscard]] CheatEntry readEntry();
    };
}

#endif //GAMETRAINER_TABLE_READER_HPP
