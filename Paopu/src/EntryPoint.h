#pragma once

#ifdef PAO_PLATFORM_WINDOWS

extern Paopu::Application* Paopu::CreateApplication();

int main(int argc, char** argv){
    printf("Paopu Framework Initializing...");
    auto app = Paopu::CreateApplication();
    app->Run();
    delete app;
}

#endif