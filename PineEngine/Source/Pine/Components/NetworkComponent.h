#pragma once
#include "Component.h"
#include "Log.h"
#include "ComponentSystem.h"

namespace Pine
{
	class NetworkComponent : public Component
	{
	public:
		NetworkComponent(std::string p_Name) : Component(p_Name) {};

		void Render() override;

		void Update(float p_StepTime)override;

		//void 

		
	};


}