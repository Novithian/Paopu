#pragma once
#include "Core.h"

#include "../Renderer/Renderer.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Paopu {

    // Forward Declarations
    class Renderer;

    class PAOPU_API Application {

        public:
            Application();
            virtual ~Application() = default;

            void run();

        private:
            /// Handles the initializing of the window
            ///
            ///
            void initWindow();
            
            /// The main application loop
            ///
            ///
            void mainLoop();

            /// 
            ///
            ///
            void cleanup();


        private:
            const uint32_t WINDOW_WIDTH = 1280;
            const uint32_t WINDOW_HEIGHT = 720;

            GLFWwindow* m_Window;
            Renderer* m_Renderer;
    };

    // Defined by the client
    Application* CreateApplication();
}