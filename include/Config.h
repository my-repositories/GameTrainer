#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

class Config {
public:
    std::string processName;

    struct cheats
    {
        bool exists;
        DWORD instructionAddress, returnAddress;
        std::string instructionModule, returnModule;
        std::vector<byte> original, inject, jump;
        cheats() : exists(false) {}
    } ohk, nr;

    struct entrys
    {
        std::string type;
        short size;
        std::string module;
        DWORD_PTR address;
        DWORD offsets[5];
        short count;
        entrys() : size(0), count(0) {}
    } health, data1n2, data2n1, data2n2, data2n3, money, experience;

    struct hot {
        struct keys
        {
            int code;
            std::string name;
            keys() : code(-1) {}
        } data1, data2, money, experience, ohk, nr;
    } hotkey;

    struct amount
    {
        union v
        {
            int i;
            float f;
            v() : i(0) {}
        } value;
        std::string type;
    } maxHealth, amountMoney, amountExperience;

    Config(std::string file);
    ~Config();
    static BOOL FileExists(LPCTSTR szPath);

private:
    size_t offset, size;
    std::string buff;
    std::ifstream ini, xml;

    void ParseIni(const std::string& fileName);
    void _ReadKey(hot::keys& hotkey);
    int _Key2code(const std::string& key);
    void _ReadAmount(amount& data, std::string& type);

    void ParseXml(std::string& fileName);
    void _ReadCheat(cheats& cheat);
    void _ReadInstruction(std::string& module, DWORD& address);
    void _ReadEntry(entrys& data);
    void _ReadType(entrys& data);
    void _ReadAddress(entrys& data);
    void _ReadOffsets(entrys& data);
    void _ReadValue(amount& amount);
    std::string _ReadSettings();
};
#endif
