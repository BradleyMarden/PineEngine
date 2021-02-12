#include "PGameObject.h"

namespace Pine
{
	PGameObject::PGameObject() 
	{
	
	}

	PGameObject::~PGameObject()
	{

	}

	void PGameObject::Update()
	{
		 for (auto& c : Components)
		 {
			c->Update();
		 }
	}

	bool PGameObject::CheckDestroyed()
	{
		if (IsAlive() == false)
		{
			PINE_ENGINE_ERROR("You are attempting to access a destoryed PGameObject. This will have no effect.");
			//PINE_ENGINE_ERROR("OPENGL NO INITIALIZED!");

			return true;
		}
		return false;
	}
	
}