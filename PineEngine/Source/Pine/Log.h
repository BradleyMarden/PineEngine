#pragma once
#include <memory>//for shared pointers
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Pine {
	class PINE_API Log
	{
	public:
		Log();
		~Log();

		static void Init();

		/*returns shared ptr logger by reference, when this goes out of scope this ptr is destroyed, 
		however if an instance of the the ptr exists anywhere else the reference will still be avaliable, 
		untill no instances access the memory, at which point the mem will get cleared.*/
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() {return s_EngineLogger;}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};
}

//For Engine Logging
#define	PINE_ENGINE_ERROR(...) ::Pine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define	PINE_ENGINE_WARN(...) ::Pine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define	PINE_ENGINE_FATAL(...) ::Pine::Log::GetEngineLogger()->fatal(__VA_ARGS__)
#define	PINE_ENGINE_INFO(...) ::Pine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define	PINE_ENGINE_TRACE(...) ::Pine::Log::GetEngineLogger()->trace(__VA_ARGS__)

//For Client Logging
#define PINE_ERROR(...) ::Pine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PINE_WARN(...) ::Pine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PINE_FATAL(...) ::Pine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define PINE_INFO(...) ::Pine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PINE_TRACE(...) ::Pine::Log::GetClientLogger()->trace(__VA_ARGS__)
