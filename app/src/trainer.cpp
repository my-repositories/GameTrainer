#include <trainer.hpp>

namespace GameTrainer::app
{
    Trainer::Trainer(std::string trainerTitle) :
            title(std::move(trainerTitle))
    {
        GameTrainer::mylib::win::setConsoleTitle(this->title.c_str());
        this->windowManager = new GameTrainer::mylib::WindowManager(this->title);
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
        GameTrainer::mylib::LuaWrapper lua;
        loadLuaState(lua);

        lua.registerFunction("writeMemory", [](const char *mem)
        {
            std::cout << "write memory: " << mem << std::endl;
        });

        lua.registerFunction("playSound", GameTrainer::mylib::win::playSound);

        const auto registeredKeys = lua.getVector<int>((char *) "registeredKeys");
        const auto begin = registeredKeys.begin();
        const auto end = registeredKeys.end();

        for (;; GameTrainer::mylib::win::sleep(50))
        {
            // Close Trainer IF GAME is NOT RUNNING
            if (!gameIsRunning())
            {
                break;
            }

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
                if (GameTrainer::mylib::win::ifKeyPressed(key))
                {
                    lua.callFunction("handleKey", key);
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

    void loadLuaState(GameTrainer::mylib::LuaWrapper &lua)
    {
#if DEBUG
        constexpr char *script = (char *) R"(
key_codes = {
	VK_F5 = 0x74,
	VK_F6 = 0x75,
	VK_F7 = 0x76
}
processName = 'KillingFloor.exe'
maxHealth = 100
registeredKeys = {
    key_codes.VK_F6,
    key_codes.VK_F7
}

function handleKey (key)
	if key == key_codes.VK_F6 then
		print('many many')
		playSound('sounds/money.wav')
	elseif key == key_codes.VK_F7 then
		print('off')
		playSound('sounds/off.wav')
	else
		print('unknown key')
	end
end
		)";
        lua.loadString(script);
#else
        lua.loadFile("scripts/KillingFloor.lua");
#endif
    }
}
