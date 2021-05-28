#include "Shader.h"

namespace Pine {

	SourceShader Shader::LoadShader(const std::string& p_fileLocation)
	{
		std::ifstream stream(p_fileLocation);

		std::string currentLine;
		
		enum class ShaderType {NONE = -1, VERT = 0, FRAG = 1};
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (std::getline(stream, currentLine))
		{
			if (currentLine.find("#shader") != std::string::npos)
			{
				if (currentLine.find("vertex") != std::string::npos)
				{
					PINE_ENGINE_INFO("Found Vertex Shader");
					type = ShaderType::VERT;
				}
				else if (currentLine.find("fragment") != std::string::npos)
				{
					PINE_ENGINE_INFO("Found Fragment Shader");
					type = ShaderType::FRAG;
				}
			}
			else
			{
				ss[(int)type] << currentLine << '\n';
			}
		}
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShader(const std::string& source, unsigned int type) 
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		int result;

		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) 
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);

			std::string s = (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
			PINE_ENGINE_WARN("Failed to compile shader: " + s);

			PINE_ENGINE_WARN(message);
			std::cout << message << std::endl;
			
			glDeleteShader(id);
			return 0;
		
		}
		return id;
	}

	int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();

		unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
		unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
		
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}