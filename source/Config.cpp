#include <Config.h>
#include <sstream>

Config::Config(std::string fileName)
{
    ParseXml(fileName);
    ParseIni("settings.ini");
}

Config::~Config() {}

void Config::ParseIni(const std::string& fileName)
{
    char szPath[MAX_PATH];
    GetCurrentDirectory(sizeof(szPath), szPath);
    lstrcat(szPath, "\\");
    lstrcat(szPath, fileName.c_str());

    if (!FileExists(szPath))
    {
        return;
    }

    ini.open(fileName);
    while (getline(ini, buff))
    {
        if (buff.find("KEY_GODMODE") != std::string::npos)
        {
            _ReadKey(hotkey.data1);
        }
        if (buff.find("KEY_NORELOAD") != std::string::npos)
        {
            _ReadKey(hotkey.data2);
        }
        if (buff.find("KEY_MONEY") != std::string::npos)
        {
            _ReadKey(hotkey.money);
        }
        if (buff.find("KEY_EXPERIENCE") != std::string::npos)
        {
            _ReadKey(hotkey.experience);
        }
        if (buff.find("KEY_CHEAT_ONEHITKILL") != std::string::npos)
        {
            _ReadKey(hotkey.ohk);
        }
        if (buff.find("KEY_CHEAT_NORELOAD") != std::string::npos)
        {
            _ReadKey(hotkey.nr);
        }
        if (buff.find("AMOUNT_MONEY") != std::string::npos)
        {
            _ReadAmount(amountMoney, money.type);
        }
        if (buff.find("AMOUNT_EXPERIENCE") != std::string::npos)
        {
            _ReadAmount(amountExperience, experience.type);
        }
    }
    ini.close();
}

void Config::_ReadAmount(amount& data, std::string& type)
{
    offset = buff.find("=") + 1;
    buff = buff.substr(offset);
    buff = buff.substr(buff.find_first_not_of(' '));

    if (type == "Float")
    {
        data.value.f = stof(buff);
    }
    else
    {
        data.value.i = stoi(buff);
    }
    data.type = type;
}

void Config::_ReadKey(hot::keys& hotkey)
{
    offset = buff.find("=") + 1;
    buff = buff.substr(offset);
    hotkey.name = buff.substr(buff.find_first_not_of(' '));
    hotkey.code = _Key2code(hotkey.name);
}

int Config::_Key2code(const std::string& key)
{
    size_t len = key.length();
    switch (len)
    {
    case 1: return VkKeyScan(key[0]) & 0xff;
    case 2:
    case 3: return VK_F1 - 1 + atoi(key.substr(1).c_str());
    case 4:
    case 5: return VK_NUMPAD0 + atoi(key.substr(3).c_str());
    case 7:
    case 8: return VK_NUMPAD0 + atoi(key.substr(6).c_str());
    }
    return -1;
}

void Config::ParseXml(std::string& file)
{
    xml.open(file);
    while (getline(xml, buff))
    {
        if (buff.find("<Description>\"HEALTH") != std::string::npos)
        {
            _ReadEntry(health);
        }
        if (buff.find("<Description>\"DATA1N2") != std::string::npos)
        {
            _ReadEntry(data1n2);
        }
        if (buff.find("<Description>\"DATA2N1") != std::string::npos)
        {
            _ReadEntry(data2n1);
        }
        if (buff.find("<Description>\"DATA2N2") != std::string::npos)
        {
            _ReadEntry(data2n2);
        }
        if (buff.find("<Description>\"DATA2N3") != std::string::npos)
        {
            _ReadEntry(data2n3);
        }
        if (buff.find("<Description>\"MONEY") != std::string::npos)
        {
            _ReadEntry(money);
        }
        if (buff.find("<Description>\"EXPERIENCE") != std::string::npos)
        {
            _ReadEntry(experience);
        }
        if (buff.find("<Description>\"MAXHEALTH") != std::string::npos)
        {
            _ReadValue(maxHealth);
        }
        if (buff.find("<Description>\"PROCESSNAME") != std::string::npos)
        {
            processName = _ReadSettings();
        }
        if (buff.find("<Description>\"CHEAT_ONEHITKILL") != std::string::npos)
        {
            _ReadCheat(ohk);
        }
        if (buff.find("<Description>\"CHEAT_NORELOAD") != std::string::npos)
        {
            _ReadCheat(nr);
        }
    }
    xml.close();
}

void Config::_ReadCheat(cheats& cheat)
{
    std::string opcode;
    std::stringstream ss;

    while (getline(xml, buff))
    {
        if (buff.find("//Alt: db ") != std::string::npos)
        {
            ss << buff.substr(10);
            while (ss >> opcode)
            {
                cheat.original.push_back(static_cast<byte>(strtoul(opcode.c_str(), NULL, 16)));
            }
        }
        if (buff.find("instructionAddress") != std::string::npos)
        {
            _ReadInstruction(cheat.instructionModule, cheat.instructionAddress);
        }
        if (buff.find("returnAddress") != std::string::npos)
        {
            _ReadInstruction(cheat.returnModule, cheat.returnAddress);
            break;
        }
    }
    getline(xml, buff);
    while (getline(xml, buff))
    {
        if (buff.find("}") != std::string::npos)
        {
            break;
        }

        ss.str(std::string());
        ss.clear();
        ss << buff;
        while (ss >> opcode)
        {
            cheat.inject.push_back(static_cast<byte>(strtoul(opcode.c_str(), NULL, 16)));
        }
    }

    cheat.jump.push_back(0xE9);
    for (size_t i = 1; i < 5; i++)
    {
        cheat.jump.push_back(0);
    }
    for (size_t i = 5; i < cheat.original.size(); i++)
    {
        cheat.jump.push_back(0x90);
    }
    cheat.exists = true;
}

void Config::_ReadInstruction(std::string& module, DWORD& address)
{
    // read Module
    offset = buff.find(":") + 3;
    size = buff.find("+") - offset - 1;
    module = buff.substr(offset, size);

    // read Base Address
    offset = buff.find("+") + 1;
    address = std::stoul(buff.substr(offset), nullptr, 16);
}

void Config::_ReadEntry(entrys& data)
{
    while (getline(xml, buff))
    {
        if (buff.find("<VariableType>") != std::string::npos)
        {
            _ReadType(data);
        }
        if (buff.find("<Address>") != std::string::npos)
        {
            _ReadAddress(data);
        }
        if (buff.find("<Offsets>") != std::string::npos)
        {
            _ReadOffsets(data);
            break;
        }
    }
}

void Config::_ReadType(entrys& data)
{
    offset = buff.find(">") + 1;
    size = buff.find("/") - offset - 1;
    data.type = buff.substr(offset, size);

    if (data.type == "Byte")
    {
        data.size = 1;
    }
    else if (data.type == "2 Bytes")
    {
        data.size = 2;
    }
    else
    {
        data.size = 4;
    }
}

void Config::_ReadAddress(entrys& data)
{
    // read Module
    offset = buff.find(">") + 2;
    size = buff.find("+") - offset - 1;
    data.module = buff.substr(offset, size);

    // read Base Address
    offset = buff.find("+") + 1;
    size = buff.find("/") - offset - 1;
    data.address = std::stoul(buff.substr(offset, size), nullptr, 16);
}

void Config::_ReadOffsets(entrys& data)
{
    while (getline(xml, buff))
    {
        if (buff.find("</Offsets>") != std::string::npos)
        {
            break;
        }

        offset = buff.find(">") + 1;
        size = buff.find("/") - offset - 1;
        data.offsets[data.count] = std::stoul(buff.substr(offset, size), nullptr, 16);
        ++data.count;
    }
    --data.count;
}

void Config::_ReadValue(amount& amount)
{
    while (getline(xml, buff))
    {
        if (buff.find("<VariableType>") != std::string::npos)
        {
            offset = buff.find(">") + 1;
            size = buff.find("/") - offset - 1;
            amount.type = buff.substr(offset, size);

            if ("Float" == amount.type)
            {
                amount.value.f = stof(_ReadSettings());
            }
            else
            {
                amount.value.i = stoi(_ReadSettings());
            }
            return;
        }
    }
}

std::string Config::_ReadSettings()
{
    while (getline(xml, buff))
    {
        if (buff.find("<Address>") != std::string::npos)
        {
            offset = buff.find(">") + 1;
            size = buff.find("/") - offset - 1;
            return buff.substr(offset, size);
        }
    }
    return NULL;
}

BOOL Config::FileExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES
        && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
