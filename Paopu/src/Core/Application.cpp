#include "Application.h"

#include "Window.h"
#include "../Renderer/Renderer.h"

namespace Paopu {
    
    Application::Application() {
        renderer = new Renderer();
        
    }
    

    void Application::run() {

        // Create our window
        window = new PaopuWindow("Sandbox");
        
        // See Window.h
        build_window(window);

        renderer->init_backend(window);

        main_loop();

        free();     
    }

    void Application::free() {
        renderer->free_renderer();
        
        // See Window.h
        free_window(window);

        delete window;
        delete renderer;

    }

    void Application::main_loop() {
        while(!glfwWindowShouldClose(window->glfw_window)) {
            glfwPollEvents();
        }

    }


}
