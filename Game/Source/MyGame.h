#include <Pine.h>
#include <iostream>
using namespace Pine;
class myGame : public Pine::Game
{
public:
    myGame();
    ~myGame();

    Pine::Core *app;

    virtual void Start();
virtual void Initialize();
virtual void Update();
virtual void Terminate();
virtual void OnMouseClick();

};
