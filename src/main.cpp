#include <iostream>
#include <SDL.h>
#undef main

using namespace std;

Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
	cout << "Test" << endl;
	return interval;
}

int main() {
	cout << "Hi" << endl;
	SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

	return 0;
}