#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Paopu {

    std::shared_ptr<spdlog::logger> Logger::s_core_logger;
    std::shared_ptr<spdlog::logger> Logger::s_client_logger;

    void Logger::init(){
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_core_logger = spdlog::stdout_color_mt("Paopu");
        s_core_logger->set_level(spdlog::level::trace);

        s_client_logger = spdlog::stdout_color_mt("App");
        s_client_logger->set_level(spdlog::level::trace);
    }
}