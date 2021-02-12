#pragma once
#include "PGameObject.h"


namespace Pine {
	class PGameObject;
	class PComponent
	{
	public:
		PComponent();
		~PComponent();
		virtual void Update();
		virtual void Start();
		//virtual void Initialize();
		//void SetGameObject(PGameObject& p_PGO);
		PGameObject* m_PGO;

	protected:
	};
}

