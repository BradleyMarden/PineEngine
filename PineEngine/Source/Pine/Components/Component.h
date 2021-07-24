#pragma once
#include <string>
namespace Pine
{

	//class ComponentSystem;

	class Component 
	{
	public:
		inline const int GetInstanceID() const { return m_InstanceID; }

		void SetID(int p_ID) { m_InstanceID = p_ID; }

		Component(std::string p_ComponentName);

		inline std::string GetName() { return m_Name; }

	protected:

	private:
		int m_InstanceID =0;
		std::string m_Name;
		
	};
}