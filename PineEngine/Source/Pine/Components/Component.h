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

		virtual void Render() = 0;

		virtual void Update(float p_StepTime) = 0;

	protected:

	private:
		int m_InstanceID =0;
		std::string m_Name;
		
	};
}