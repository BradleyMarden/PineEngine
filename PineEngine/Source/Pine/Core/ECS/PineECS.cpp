#include "PineECS.h"

namespace Pine {
	
	PECS::PECS()
	{
	}

	PECS::~PECS()
	{
	}

	PGameObject& PECS::CreateGameObject()
	{
		//Create raw ptr on the heap
		PGameObject* l_PGO = new PGameObject();

		//create a unique ptr, and transfer ownership to it. This is done so that if we delete the unique ptr, the raw ptr does not need to be deleted.
		//Allows for less management on the user side.
		std::unique_ptr<PGameObject> uptr{ l_PGO };

		//Add to the end of the vector, and return a reference of the new game object. when the gameobject is removed from the m_PGameObjects vector, the reference will now reference unused mem.
		m_PGameObjects.emplace_back(std::move(uptr));
		return *l_PGO;
	
	}

	void PECS::Update()
	{
		Refresh();

		for (auto& PGO : m_PGameObjects)
		{
			PGO->Update();
		}
	}

	void PECS::Refresh()
	{
		for (size_t i = 0; i < m_PGameObjects.size(); i++)
		{
			m_PGameObjects.erase(std::remove_if(std::begin(m_PGameObjects), std::end(m_PGameObjects), [](const std::unique_ptr<PGameObject>& p_PGO)
				{
					return !p_PGO->IsAlive();
				}), std::end(m_PGameObjects));
		}
	}
}
