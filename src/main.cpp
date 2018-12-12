/*! \mainpage Minion Crusher
 * Minion Crusher is a tower defense game where the player builds and upgrades towers to defend his base from the enemy minions.
 *
 */

#include <iostream>

#include "Map.h"
#include "UI.h"

using namespace std;

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr Uint32 UPDATE_FREQUENCY = 300;
constexpr Uint32 UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;

// Temporary location of minion spawn information
CartesianCoordinates spawnLocation = {0, 1};
int ticksToNextMinion = 3;
int tickCount = 2;

void moveMinions(Map *map);

void addMinions(Map *map);

void shootTowers(Map *map);

void UIInit(SDL_Window *&window, SDL_Renderer *&renderer);

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void *m) {
    Map *map = reinterpret_cast<Map *>(m);
    std::lock_guard<std::mutex> lock(map->getMutex());

    moveMinions(map);

    addMinions(map);

    shootTowers(map);

    return interval;
}


int main(int argc, char *args[]) {
    if (argc > 1) {
        cout << "too many arguments: ";
        for (int i = 0; i < argc; i++) {
            cout << args[i] << " ";
        }
    }

    // CREATE MAP FROM BLUEPRINT
    Map map("resources/blueprints/1.blueprint");
    map.towers.push_back(Tower(2, 2, 1, 1, 25, 3, 10, AmmoType{}));

    // INITIALIZE THE USER INTERFACE
    SDL_Window *window;
    SDL_Renderer *renderer;
    try {
        UIInit(window, renderer);
    }
    catch (std::exception &e) {
        std::cout << e.what();
    }
    UI ui = UI(WINDOW_WIDTH, WINDOW_HEIGHT, window, renderer);
    //Initialize the map
    ui.setMap(&map);

    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(UPDATE_PERIOD, gameUpdate, &map);
    if (timer_id == 0) {
        cout << "SDL was unable to create a timer. " << endl;
    }

    bool quit = false;
    while (!quit) {
        //update screen
        ui.Render();
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //Handle button events
            ui.HandleEvents(e);
            //User requests quit
            if (e.type == SDL_QUIT) {
                cout << "quitting" << endl;
                quit = true;

            }
        }
    }
    return 0;
}

void UIInit(SDL_Window *&window, SDL_Renderer *&renderer) {
    // INITIALIZE THE USER INTERFACE

// Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("SDL could not initialize!");

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        throw std::runtime_error("Warning: Linear texture filtering not enabled!");

    // Create a Window in the middle of the screen
    window = SDL_CreateWindow("MinionCrusher", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        throw std::runtime_error("Window could not be created!");

    // Create a new renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        throw std::runtime_error("Renderer could not be created!");
}

/** Move all minions in the right direction along the path */
void moveMinions(Map *map) { 
    bool finished;
    do {
        finished = true;
        for (Minion &minion : (map->minions)) {

            int dir = (int) map->path[(int) minion.traversedDistance].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + minion.getSpeed() * (-(dir == 1) + (dir == 4)),
                     minion.getCoordinates().y + minion.getSpeed() * (-(dir == 3) + (dir == 2))}
            );
            if (int(minion.traversedDistance) >= (int) map->path.size() - 1) {
                map->base.doDamage(map->minions.front().getDamage());
                map->minions.pop_front();
                finished = false;
                break;
            }
            minion.traversedDistance = minion.traversedDistance + minion.getSpeed();

            //cout << "moveCount: " << minion.moveCount << " Direction: " << dir << endl;
        }
    } while (!finished);
}

/** Spawn new minions on a timed interval */
void addMinions(Map *map) {
    // Add minions to the battlefield on an interval
    static float speed = 0.1F;
    if (speed * tickCount >= ticksToNextMinion) {
        tickCount = 0;
        Minion minion = Minion(map->spawnPos.x, map->spawnPos.y, 1, 1, 100, 1, 0.02F);
        map->minions.push_back(minion);
        speed = minion.getSpeed();
    } else {
        tickCount++;
    }
}

/** Check for all towers if they are allowed to shoot and check whether they have a minion in range */
void shootTowers(Map *map) {
    for (Tower &tower : map->towers) {
		tower.towerUpdate(map->minions);
    }
}