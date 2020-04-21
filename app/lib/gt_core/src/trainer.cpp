#include <gt_core/trainer.hpp>

namespace gt::core
{
    Trainer::Trainer(std::string trainerTitle) :
            title(std::move(trainerTitle))
    {
        os::setConsoleTitle(this->title.c_str());
        this->windowManager = new os::WindowManager(this->title);
    }

    Trainer::~Trainer()
    {
        delete this->windowManager;
    }

    bool Trainer::trainerIsRunning() const
    {
        return this->windowManager->isOpened();
    }

    void Trainer::showOpenedWindow() const
    {
        this->windowManager->show();
    }

    void Trainer::start() const
    {
        lua::LuaWrapper lua;

        void (*lambada)(xml::CheatEntry*, float) = [](xml::CheatEntry* entry, float valueToAdd)
        {
            DWORD processId = os::getProcessIdByName("KillingFloor.exe");

            Game game(processId);
            game.updateValue(entry, valueToAdd);
        };

        lua.registerFunction("addValueTo", lambada);

        // TODO: remove unused parameter for stopMP3.
        lua.registerFunction("stopMP3", os::stopMP3);
        lua.registerFunction("playMP3", os::playMP3);
        lua.registerFunction("playWAV", os::playWAV);

        lua.registerFunction("readFile", lua::LuaWrapper::createUserData);

        loadLuaState(lua);

        const auto registeredKeys = lua.getVector<int>((char *) "registeredKeys");
        const char* processName = *lua.getValue<char*>((char *) "processName");
        std::cout << processName << std::endl;
        os::KeyboardWatcher keyboardWatcher(registeredKeys);

        for (;; os::sleep(50))
        {
            // TODO: remove it!
            if(keyboardWatcher.isKeyDown(VK_F13))
            {
                break;
            }

            // TODO: uncomment it!
            // Close Trainer IF GAME is NOT RUNNING
//            if (!gameIsRunning())
//            {
//                break;
//            }

            // TODO: uncomment it!
//        // Continue IF GAME is not active || PLAYER is DEAD
//        if (!GameOnFocus() || game->PlayerIsDead())
//        {
//            Sleep(1000);
//            continue;
//        }

//        // Rewrite data if FREEZE FLAG enabled
//        if (bGodMode)
//        {
//            game->UpdateData1();
//        }
//        if (bNoReload)
//        {
//            game->UpdateData2();
//        }

            for (const int key : registeredKeys)
            {
                if (keyboardWatcher.isKeyPressed(key))
                {
                    lua.callFunction(
                            "handleKey",
                            key,
                            keyboardWatcher.isKeyDown(VK_SHIFT),
                            keyboardWatcher.isKeyDown(VK_CONTROL),
                            keyboardWatcher.isKeyDown(VK_MENU)
                    );
                }
            }
        }
    }

    bool Trainer::chooseConfig() const
    {
        std::cout << "method 'Trainer::chooseConfig' is not implemented yet!" << std::endl;

        return true;
    }

    bool Trainer::gameIsRunning() const
    {
        std::cout << "method 'Trainer::gameIsRunning' is not implemented yet!" << std::endl;

        return true;
    }

    void loadLuaState(lua::LuaWrapper &lua)
    {
#if DEBUG
        constexpr char *script = (char *) R"(
keyCodes = {
	VK_F5 = 0x74,
	VK_F6 = 0x75,
	VK_F7 = 0x76,
	VK_F8 = 0x77,
	VK_F9 = 0x78
}
api = {
    playSound = playSound,
    addValueTo = addValueTo,
    readFile = readFile
}
processName = 'KillingFloor.exe'

entries = api.readFile('KillingFloor.CT')

registeredKeys = {
    keyCodes.VK_F6,
    keyCodes.VK_F7,
    keyCodes.VK_F8,
    keyCodes.VK_F9
}

function handleKey (key, shift, ctrl, alt)
    if key == keyCodes.VK_F6 then
        print('god mode')
        api.playSound('sounds/on.wav')
    elseif key == keyCodes.VK_F7 then
        print('no reload')
        api.playSound('sounds/on.wav')
    elseif key == keyCodes.VK_F8 then
        api.addValueTo(entries.money, 1000)
        print('increase money')
        api.playSound('sounds/money.wav')
    elseif key == keyCodes.VK_F9 and shift and ctrl and alt then
        print('level up for all perks')
        api.playSound('sounds/experience.wav')
    end
end

function tick()
    -- addValueTo(entries.armor, 100)
end
		)";
        lua.loadString(script);
#else
        lua.loadFile("scripts/KillingFloor.lua");
#endif
    }
}
