#pragma once

#include "spdlog/spdlog.h"

namespace Mewtle{
	class Log{
		public :
			static void init();
			
			inline static std::shared_ptr<spdlog::logger>& getCoreLogger(){ return s_coreLogger; }
			inline static std::shared_ptr<spdlog::logger>& getClientLogger(){ return s_clientLogger; }

		private :
			static std::shared_ptr<spdlog::logger> s_coreLogger;
			static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#ifdef MTL_BUILD_DLL
// Core log macros.
#define MTL_CORE_TRACE(...)  ::Mewtle::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MTL_CORE_INFO(...)   ::Mewtle::Log::getCoreLogger()->info(__VA_ARGS__)
#define MTL_CORE_WARN(...)   ::Mewtle::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MTL_CORE_ERROR(...)  ::Mewtle::Log::getCoreLogger()->error(__VA_ARGS__)
#define MTL_CORE_FATAL(...)  ::Mewtle::Log::getCoreLogger()->fatal(__VA_ARGS__)
#else
// Client log macros.
#define MTL_TRACE(...)       ::Mewtle::Log::getClientLogger()->trace(__VA_ARGS__)
#define MTL_INFO(...)        ::Mewtle::Log::getClientLogger()->info(__VA_ARGS__)
#define MTL_WARN(...)        ::Mewtle::Log::getClientLogger()->warn(__VA_ARGS__)
#define MTL_ERROR(...)       ::Mewtle::Log::getClientLogger()->error(__VA_ARGS__)
#define MTL_FATAL(...)       ::Mewtle::Log::getClientLogger()->fatal(__VA_ARGS__)
#endif

//#include "LoggingSystem/LoggingMacros.h"