#include <gt_core/trainer.hpp>

// TODO: move this logic to gt_console.lib
int main(int argc, char *argv[]) {
    std::string title =
        std::string(GT_PROJECT_NAME) + " " + GT_PROJECT_VERSION;

    gt::core::Trainer trainer(std::move(title), &gt::os::OsApi::getInstance());

    // Allow only one instance of application.
    if (trainer.trainerIsRunning()) {
        trainer.showOpenedWindow();

        return 0;
    }

#if !DEBUG
    system("color a");
#endif

    if (!trainer.chooseConfig()) {
        return 1;
    }

    // Waiting for the game to start ...
    while (!trainer.gameIsRunning()) {
        gt::os::sleep(1000);
    }

    trainer.start();

    return 0;
}
