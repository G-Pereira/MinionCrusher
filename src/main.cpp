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

	UI ui = UI(WINDOW_WIDTH, WINDOW_HEIGHT);

    // CREATE MAP FROM BLUEPRINT
    Map map("resources/blueprints/1.blueprint");
    map.towers.emplace_back(2, 2, 1, 1, 25, 3, 10, AmmoType{});

    //Initialize the map
    ui.setMap(&map);

    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(UPDATE_PERIOD, gameUpdate, &map);
    if (timer_id == 0) {
        cout << "SDL was unable to create a timer. " << endl;
    }

    bool quit = false;
    while (!quit) {
        ui.Render(ui.getRenderer());
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //Handle button events
            ui.HandleEvents(e);
            //User requests quit
            if (e.type == SDL_QUIT) {
                cout << "quitting" << endl;
				SDL_RemoveTimer(timer_id);
                quit = true;
            }
        }
    }
	
    return 0;
}


/** Move all minions in the right direction along the path */
void moveMinions(Map *map) { 
    bool finished;
    do {
        finished = true;
        for (Minion &minion : (map->minions)) {

            int dir = (int) map->path[(int) minion.moveCount].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + minion.getSpeed() * (-(dir == 1) + (dir == 4)),
                     minion.getCoordinates().y + minion.getSpeed() * (-(dir == 3) + (dir == 2))}
            );
            if (int(minion.moveCount) >= (int) map->path.size() - 1) {
                map->base.doDamage(map->minions.front().getDamage());
                map->minions.pop_front();
                finished = false;
                break;
            }
            minion.moveCount = minion.moveCount + minion.getSpeed();

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
        if(tower.getTicks() >= tower.getFirePeriod()){
            tower.setTicks(0);
        } else{
            tower.setTicks(tower.getTicks()+1);
            continue;
        }
        for (Minion &minion : map->minions) {
            if (minion.getCoordinates().isInRange(tower.getCoordinates(), tower.getRange())) {
                minion.setHealth(minion.getHealth() - tower.getDamage());
                if (minion.getHealth() <= 0)
                    map->minions.remove(minion);
                break;
            }
        }
    }
}