#pragma once
#include "Core.h"

//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>

namespace Paopu {

    // Forward Declarations
    class Renderer;
    class PaopuWindow;

    class PAOPU_API Application {

        public:
            Application();
            virtual ~Application() = default;

            void run();

        private:
            /// The main application loop
            ///
            ///
            void main_loop();

            /// Call to clean up before being destroyed
            ///
            ///
            void free();


        private:
            Renderer* renderer;
            PaopuWindow* window;
    };

    // Defined by the client
    Application* create_application();
}