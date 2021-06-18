#pragma once
#include <fstream>
#include <iostream>
//#include <string>
#include <sstream>
#include "Core.h"
#include "Pine/Logging/Log.h"
namespace Pine {

	struct SourceShader
	{
		std::string VertexSource;
		std::string FragmentSource;
	};
	class Shader
	{
	public:
		static SourceShader LoadShader(const std::string&  p_fileLocation);
		static int CreateShader(const std::string& vs, const std::string& fs);
		static unsigned int CompileShader(const std::string& source, unsigned int type);


	};
}