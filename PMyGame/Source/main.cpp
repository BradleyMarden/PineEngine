#include <Pine.h>
#include "PMyGameApp.h"
using namespace Pine;

int main()
{
	//PWindow* Gamewindow = new PWindow("Test Window", 600,400);
	Core* App = new Core();
	PMyGame* game = new PMyGame();
	
	App->PineOpenWindow("test", 600, 500);
	if (!App->PineInit(game))//if return false
	{
		App->PineCloseWindow();

	}
	App->PineStart();

	App->PineCloseWindow();

	delete App;
	delete game;
	return 0;
}