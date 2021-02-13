#pragma once

#ifdef PAO_PLATFORM_WINDOWS

    extern Paopu::Application* Paopu::CreateApplication();

    int main(int argc, char** argv){
        
        Paopu::Logger::init();
        PAO_CORE_WARN("Logger initialized..");
        PAO_INFO("Client Logger connected..");

        printf("Paopu Framework Initializing...");
        auto app = Paopu::CreateApplication();
        app->Run();
        delete app;
    }

#endif