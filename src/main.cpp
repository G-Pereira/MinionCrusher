#include <iostream>
#include <Map.h>
#include "UI.h"

using namespace std;

UI ui = UI(1280, 720);

// Temporary location of minion spawn information
CartesianCoordinates spawnLocation = {0, 1};
int ticksToNextMinion = 3;
int tickCount = 2;

/**
* Updates position of all mapobjects in the game on a fixed interval. This includes all towers, minions etc.
*/
Uint32 gameUpdate(Uint32 interval, void *m) {
    Map *map = reinterpret_cast<Map *>(m);


    // Move all minions in the right direction
    bool finished;
    do {
        finished = true;
        for (Minion &minion : (map->minions)) {

            int dir = (int) map->path[minion.moveCount].getType();
            minion.setCoordinates(
                    {minion.getCoordinates().x + -(dir == 1) + (dir == 4),
                     minion.getCoordinates().y + -(dir == 3) + (dir == 2)}
            );
            if (minion.moveCount == (int) map->path.size() - 1) {
                map->minions.pop_front();
                finished = false;
                break;
            }
            minion.moveCount = minion.moveCount + 1;

            //cout << "moveCount: " << minion.moveCount << " Direction: " << dir << endl;
        }
    } while (!finished);
    // Add minions to the battlefield on an interval
    if (tickCount >= ticksToNextMinion) {
        tickCount = 0;
        Minion minion = Minion(spawnLocation.x, spawnLocation.y, 1, 1, 100, 1, 1);
        map->minions.push_back(minion);
    } else {
        tickCount++;
    }

    // For each tower: Check if it can fire by checking its ticks.
    // If yes: Find closest minion. If in range: damage it. Set ticks back to firing period.
    // If no: reduce tower ticks by one.
    return interval;
}

void BuildingButtonhandleEvent(UIButton &self, SDL_Event &e);

int main(int argc, char *args[]) {
    if (argc > 1) {
        cout << "too many arguments: ";
        for (int i = 0; i < argc; i++) {
            cout << args[i] << " ";
        }
    }
    // CREATE MAP FROM BLUEPRINT
    Map map("resources/blueprints/simple.blueprint");

    // INITIALIZE THE TIMER FUNCTION OF SDL
    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        cout << "SDL could not initialize timers" << endl;
    }
    // INITIALIZE THE CALLBACK TIMER
    SDL_TimerID timer_id = SDL_AddTimer(1000, gameUpdate, &map);
    if (timer_id == 0) {
        cout << "SDL was unable to create a timer. " << endl;
    }

    // INITIALIZE THE USER INTERFACE
    try {
        ui.init();
    } catch (std::exception &e) {
        std::cout << e.what();
    }
    ui.SetMap(&map);

    // add some buttons
    SDL_Texture *temptextu = ui.loadTexture("resources/sprites/tower1_tile.bmp");

    ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{20, 20, 100, 100}, temptextu, BuildingButtonhandleEvent);
    ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{140, 20, 100, 100}, temptextu, BuildingButtonhandleEvent);
    ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{20, 140, 100, 100}, temptextu, BuildingButtonhandleEvent);
    ui.AddButton(UI::viewPorts::buildingsview, SDL_Rect{140, 140, 100, 100}, temptextu, BuildingButtonhandleEvent);


    bool quit = false;
    while (!quit) {
        //update screen
        ui.Render(/*MapObjects*/);
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                cout << "quitting" << endl;
                quit = true;

            }

            //Handle button events
            ui.HandleButtons(e);
        }
    }

    return 0;
}


void BuildingButtonhandleEvent(UIButton &self, SDL_Event &e) {
    //If mouse event happened
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        // add the offset of the viewport
        x -= ui.getBuildingViewport().x;
        y -= ui.getBuildingViewport().y;
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < self.rect.x) {
            inside = false;
        }
            //Mouse is right of the button
        else if (x > self.rect.x + self.rect.w) {
            inside = false;
        }
            //Mouse above the button
        else if (y < self.rect.y) {
            inside = false;
        }
            //Mouse below the button
        else if (y > self.rect.y + self.rect.h) {
            inside = false;
        }

        //Mouse is outside button
        if (!inside) {
            self.current = self.mouse_off;
        }
            //Mouse is inside button
        else {
            //Set mouse over sprite
            switch (e.type) {
                case SDL_MOUSEMOTION:
                    //cout << "SDL_MOUSEMOTION" << endl;
                    self.current = self.mouse_on;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    cout << "SDL_MOUSEBUTTONDOWN" << endl;
                    self.current = self.button_pressed;
                    break;

                case SDL_MOUSEBUTTONUP:
                    cout << "SDL_MOUSEBUTTONUP" << endl;
                    self.current = self.button_pressed;
                    break;
            }
        }
    }
}