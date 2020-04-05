#ifndef GAMETRAINER_TABLE_READER_HPP
#define GAMETRAINER_TABLE_READER_HPP

#include <filesystem>
#include <iostream>

#include <xml/table-mediator.hpp>

namespace GameTrainer::mylib::xml
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

        std::vector<CheatEntry> readEntries();

        CheatEntry readEntry();
    };
}

#endif //GAMETRAINER_TABLE_READER_HPP
