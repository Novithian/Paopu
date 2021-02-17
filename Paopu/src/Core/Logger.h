#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Paopu {
    
    class PAOPU_API Logger {

        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

// Core logger macros
#define PAO_CORE_FATAL(...) ::Paopu::Logger::GetCoreLogger()->fatal(__VA_ARGS__)
#define PAO_CORE_ERROR(...) ::Paopu::Logger::GetCoreLogger()->err(__VA_ARGS__)
#define PAO_CORE_WARN(...)  ::Paopu::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define PAO_CORE_INFO(...)  ::Paopu::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define PAO_CORE_TRACE(...) ::Paopu::Logger::GetCoreLogger()->trace(__VA_ARGS__)

// Clinet logger macros
#define PAO_FATAL(...) ::Paopu::Logger::GetClientLogger()->fatal(__VA_ARGS__)
#define PAO_ERROR(...) ::Paopu::Logger::GetClientLogger()->err(__VA_ARGS__)
#define PAO_WARN(...)  ::Paopu::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define PAO_INFO(...)  ::Paopu::Logger::GetClientLogger()->info(__VA_ARGS__)
#define PAO_TRACE(...) ::Paopu::Logger::GetClientLogger()->trace(__VA_ARGS__)