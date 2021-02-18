#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>


#ifdef PAO_PLATFORM_WINDOWS

    extern Paopu::Application* Paopu::create_application();

    int main(int argc, char** argv){
        
        Paopu::Logger::init();
        PAO_CORE_INFO("Logger initialized..");
        PAO_INFO("Client Logger connected..");
        // Comment
        /// <summary>
        
        PAO_CORE_INFO("Paopu Framework Initializing...");
        auto app = Paopu::create_application();

        try {
            app->run();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        delete app;

        return EXIT_SUCCESS;
    }

#endif