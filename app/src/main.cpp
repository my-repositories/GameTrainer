#include <trainer.hpp>

int main(int argc, char* argv[])
{
    GameTrainer::app::Trainer trainer(std::string(MY_PROJECT_NAME) + " " + MY_PROJECT_VERSION);

    // Allow only one instance of application.
    if (trainer.trainerIsRunning())
    {
        trainer.showOpenedWindow();

        return 0;
    }

#if !DEBUG
    system("color a");
#endif

    if (!trainer.chooseConfig())
    {
        return 1;
    }

    // Waiting for the game to start ...
    while (!trainer.gameIsRunning())
    {
        GameTrainer::mylib::win::sleep(1000);
    }

    trainer.start();

    return 0;
}
