#pragma once
#include "../Core/Core.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Paopu {

    class PAOPU_API Renderer {

        public: 
            Renderer();
            ~Renderer();
           
            /// Handles the initializing of our respective backend
            ///
            ///
            void initBackend();

            void cleanup();
 
        private:
            /// Creates a Vulkan instance
            ///
            ///
            void createInstance();


        private:
            VkInstance m_Instance;

    };
}