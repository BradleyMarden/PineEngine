#include <Pine.h>

class PMyGame : public Pine::Application
{

public:
	PMyGame()
	{
	
	}

	~PMyGame()
	{
	
	
	}

};

Pine::Application* Pine::CreateApplication()
{
	return new PMyGame();
}
