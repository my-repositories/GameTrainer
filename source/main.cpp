#include <Trainer.h>

int main(int argc, char* argv[])
{
    // Only One Instance of Application
    if (Trainer::TrainerIsRun())
    {
        return 0;
    }

    Trainer trainer;
    if (!trainer.ChooseConfig())
    {
        return 1; // EXIT_FAILURE
    }

    // Waiting for Start a GAME... 
    while (!trainer.GameIsRun())
    {
        Sleep(1000);
    }

    trainer.Start();
    return 0;
}