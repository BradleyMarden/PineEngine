#include "Log.h"
namespace Pine
{
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;//because its static in .h and not predefined, we need to define it here.
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	 void Log::Init()
	{

		 spdlog::set_pattern("%^[%T] %n: %v%$");//Color, Timestamp, Name of the Logger, Message
		 s_EngineLogger = spdlog::stdout_color_mt("Pine");
		 s_EngineLogger->set_level(spdlog::level::trace);
		 s_ClientLogger = spdlog::stdout_color_mt("Game");
		 s_ClientLogger->set_level(spdlog::level::trace);
	}
}




