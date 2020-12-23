#pragma once
#include "PObject.h"

namespace Pine {
	class PLine
	{
		PLine();
		~PLine();

	private:
		float LineLength;
		float LineThickness;

	public:

		void SetLineLength(float m_LineLength)			{ LineLength = m_LineLength;       }
		void SetLineThickness(float m_LineThickness)   { LineThickness = m_LineThickness; }

		float GetLineLenght() { return LineLength; }

	};
}

