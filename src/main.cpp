/*! \mainpage Minion Crusher
 * Minion Crusher is a tower defense game where the player builds and upgrades towers to defend his base from the enemy minions.
 *
 */

#include <iostream>
#include "UI.h"

using namespace std;

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr Uint32 UPDATE_FREQUENCY = 300;
constexpr Uint32 UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;

// Temporary location of minion spawn information

mutex test_mutex;
GameManager gameManager;

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void *m) {
    std::lock_guard<std::mutex> lock(test_mutex);
    Map *map = reinterpret_cast<Map *>(m);
    gameManager.update();
    return interval;
}

/**
* Updates screen
*/
//Uint32 uiUpdate(Uint32 interval, void *ptr) {
//    //std::lock_guard<std::mutex> lock(test_mutex);
//    UI *ui = (UI *) ptr;
//    ui->render();
//    return interval;
//}

int main(int argc, char *args[]) {
    if (argc > 1) {
        cout << "too many arguments: ";
        for (int i = 0; i < argc; i++) {
            cout << args[i] << " ";
        }
    }

    cout << "Create UI" << endl;
    // create the UI
	UIElement::gamemanager = &gameManager;
    UI ui = UI(WINDOW_WIDTH, WINDOW_HEIGHT);
    RenderElement::renderer = ui.getRenderer();
    cout << "Read map" << endl;

    // CREATE MAP FROM BLUEPRINT
    Map map("resources/blueprints/1.blueprint");
    gameManager.map = &map;

    cout << "Start updating gamestate" << endl;
    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(UPDATE_PERIOD, gameUpdate, &map);
    if (timer_id == 0) {
        cout << "SDL was unable to create a timer. " << endl;
    }
    //SDL_TimerID ui_timer_id = SDL_AddTimer(10, uiUpdate, &ui);
    //if (ui_timer_id == 0) {
    //    cout << "SDL was unable to create a timer. " << endl;
    //}

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                cout << "quitting" << endl;
                SDL_RemoveTimer(timer_id);
                //SDL_RemoveTimer(ui_timer_id);
                quit = true;
            }
        }
        ui.render();
    }

    return 0;
}

