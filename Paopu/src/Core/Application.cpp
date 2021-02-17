#include "Application.h"

#include <stdexcept>

namespace Paopu {
    
    Application::Application() {
        m_Renderer = new Renderer();
    }
    

    void Application::initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Paopu Application", nullptr, nullptr);

    }

    void Application::run() {
         initWindow();
         m_Renderer->initBackend();
         mainLoop();
         cleanup();     
    }

    void Application::cleanup() {
        m_Renderer->cleanup();

        glfwDestroyWindow(m_Window);
        glfwTerminate();

        delete m_Renderer;
    }

    void Application::mainLoop() {
        while(!glfwWindowShouldClose(m_Window)) {
            glfwPollEvents();
        }

    }


}
