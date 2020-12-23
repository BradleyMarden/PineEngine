#pragma once
#include <memory>//for shared pointers
#include "../Core/Core.h"
//#include "../Core/PineAPI.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Pine {
	class Log
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
		inline static std::shared_ptr<spdlog::logger>& GetServerLogger() { return s_ServerLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_ServerLogger;

		
	};
}


#ifdef DEBUG

#define	PINE_ENGINE_ERROR(...)   ::Pine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define	PINE_ENGINE_WARN(...)    ::Pine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define	PINE_ENGINE_CRITICAL(...)   ::Pine::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define	PINE_ENGINE_INFO(...)    ::Pine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define	PINE_ENGINE_TRACE(...)   ::Pine::Log::GetEngineLogger()->trace(__VA_ARGS__)

//For Server Logging
#define	PINE_SERVER_ERROR(...)   ::Pine::Log::GetServerLogger()->error(__VA_ARGS__)
#define	PINE_SERVER_WARN(...)    ::Pine::Log::GetServerLogger()->warn(__VA_ARGS__)
#define	PINE_SERVER_CRITICAL(...)   ::Pine::Log::GetServerLogger()->critical(__VA_ARGS__)
#define	PINE_SERVER_INFO(...)    ::Pine::Log::GetServerLogger()->info(__VA_ARGS__)
#define	PINE_SERVER_TRACE(...)   ::Pine::Log::GetServerLogger()->trace(__VA_ARGS__)

//For Client Logging
#define PINE_ERROR(...)          ::Pine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PINE_WARN(...)           ::Pine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PINE_CRITICAL(...)          ::Pine::Log::GetClientLogger()->critical(__VA_ARGS__)
#define PINE_INFO(...)           ::Pine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PINE_TRACE(...)          ::Pine::Log::GetClientLogger()->trace(__VA_ARGS__)

#else

#define	PINE_ENGINE_ERROR(...)
#define	PINE_ENGINE_WARN(...)
#define	PINE_ENGINE_CRITICAL(...)
#define	PINE_ENGINE_INFO(...)
#define	PINE_ENGINE_TRACE(...)

//For Server Logging
#define	PINE_SERVER_ERROR(...)
#define	PINE_SERVER_WARN(...)
#define	PINE_SERVER_CRITICAL(...)
#define	PINE_SERVER_INFO(...)
#define	PINE_SERVER_TRACE(...)

//For Client Logging
#define PINE_ERROR(...)
#define PINE_WARN(...)
#define PINE_CRITICAL(...) 
#define PINE_INFO(...)
#define PINE_TRACE(...)
#endif // !PINE_RELEASE




