#include <iostream>
#include <SDL.h>
#undef main

#include "../include/UI.h"


using namespace std;

Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
	cout << "Test" << endl;
	return interval;
}

int main() {
	cout << "Hi" << endl;
	SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));
	UI ui;
	int hoi;
	cin >> hoi;
	return 0;
}