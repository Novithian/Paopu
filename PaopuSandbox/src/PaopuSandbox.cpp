#include <Paopu.h>


class SandboxApp : public Paopu::Application {
    public:
        SandboxApp(){
            // PAO_WARN("Eat shit brub");
        }

        ~SandboxApp(){

        }

};

Paopu::Application* Paopu::create_application(){
    return new SandboxApp();
}


