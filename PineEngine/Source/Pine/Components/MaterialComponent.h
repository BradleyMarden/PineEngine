#pragma once
#include "Component.h"
#include "Log.h"
#include "ComponentSystem.h"
namespace Pine
{
	class MaterialComponent : public Component
	{
	public:
		MaterialComponent(std::string p_Name) : Component(p_Name){}
		inline std::string GetMatName() { return m_MatName; }
		inline void SetMatName(std::string p_MatName) { m_MatName = p_MatName; }
	private:
		std::string m_MatName;

	};


}