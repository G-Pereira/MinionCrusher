/*! \mainpage Minion Crusher
 * Minion Crusher is a tower defense game where the player builds and upgrades towers to defend his base from the enemy minions.
 *
 */

#include <mutex>
#include <iostream>
#include "UI.h"

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr Uint32 UPDATE_FREQUENCY = 300;
constexpr Uint32 UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;


/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void *m) {
    //std::lock_guard<std::mutex> guard(key);
    GameManager *gameManager = (GameManager *) m;
    gameManager->update();
    return interval;
}

/**
* Updates screen
*/
Uint32 uiUpdate(Uint32 interval, void *ptr) {
    UI *ui = (UI *) ptr;
    ui->render();
    return interval;
}

int main(int argc, char *args[]) {
    if (argc > 1) {
        std::cout << "too many arguments: ";
        for (int i = 0; i < argc; i++) {
            std::cout << args[i] << " ";
        }
    }

    std::cout << "Initialize Game Manager" << std::endl;
    GameManager gameManager;

    std::cout << "Create UI" << std::endl;
    // create the UI
	UIElement::gamemanager = &gameManager;
    UI ui = UI(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderElement::renderer = ui.getRenderer();
    std::cout << "Read level" << std::endl;

    // CREATE MAP FROM BLUEPRINT
    Level level("resources/blueprints/1.blueprint");
    gameManager.map = &level;

    std::cout << "Start updating game state" << std::endl;
    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(5, gameUpdate, &gameManager);
    if (timer_id == 0) {
        std::cout << "SDL was unable to create a timer. " << std::endl;
    }
    SDL_TimerID ui_timer_id = SDL_AddTimer(5, uiUpdate, &ui);
    if (ui_timer_id == 0) {
        std::cout << "SDL was unable to create a timer. " << std::endl;
    }

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                std::cout << "quitting" << std::endl;
                SDL_RemoveTimer(timer_id);
                SDL_RemoveTimer(ui_timer_id);
                quit = true;
            }
        }
    }

    return 0;
}

