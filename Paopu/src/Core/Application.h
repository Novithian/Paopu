#pragma once
#include "Core.h"
namespace Paopu {

    class PAO_API Application {

        public:
            Application();
            virtual ~Application();

            void Run();
    };

    // Defined by the client
    Application* CreateApplication();
}