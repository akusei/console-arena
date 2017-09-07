#include "Global.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Game *g = new Game();

	g->Initialize();
	g->Run();

	SAFE_DELETE(g);

	return 0;
}

