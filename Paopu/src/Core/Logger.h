#pragma once
#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Paopu {
    
    class PAOPU_API Logger {

        public:
            static void init();

            inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_core_logger; }
            inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_client_logger; }
        private:
            static std::shared_ptr<spdlog::logger> s_core_logger;
            static std::shared_ptr<spdlog::logger> s_client_logger;
    };

}

// Core logger macros
#define PAO_CORE_FATAL(...) ::Paopu::Logger::get_core_logger()->fatal(__VA_ARGS__)
#define PAO_CORE_ERROR(...) ::Paopu::Logger::get_core_logger()->err(__VA_ARGS__)
#define PAO_CORE_WARN(...)  ::Paopu::Logger::get_core_logger()->warn(__VA_ARGS__)
#define PAO_CORE_INFO(...)  ::Paopu::Logger::get_core_logger()->info(__VA_ARGS__)
#define PAO_CORE_TRACE(...) ::Paopu::Logger::get_core_logger()->trace(__VA_ARGS__)

// Clinet logger macros
#define PAO_FATAL(...) ::Paopu::Logger::get_client_logger()->fatal(__VA_ARGS__)
#define PAO_ERROR(...) ::Paopu::Logger::get_client_logger()->err(__VA_ARGS__)
#define PAO_WARN(...)  ::Paopu::Logger::get_client_logger()->warn(__VA_ARGS__)
#define PAO_INFO(...)  ::Paopu::Logger::get_client_logger()->info(__VA_ARGS__)
#define PAO_TRACE(...) ::Paopu::Logger::get_client_logger()->trace(__VA_ARGS__)