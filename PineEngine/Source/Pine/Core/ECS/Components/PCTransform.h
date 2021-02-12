#pragma once
#include "../PComponent.h"
#include "../../../Maths/PMaths.h"
namespace Pine {
	template<typename t>
	class PCTransform : public PComponent
	{
	public:
		//Pass type of X and Y.
		//PCTransform(t p_X, t p_Y)
			
		PCTransform();
		~PCTransform();

	protected:
		void Start();
		void Update();
		//PVector2f m_Vector;
		//PVector m_Vector<t>;
	};
}

