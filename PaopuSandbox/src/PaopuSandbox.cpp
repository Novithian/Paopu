#include <Paopu.h>


class SandboxApp : public Paopu::Application {
    public:
        SandboxApp(){
            // PAO_WARN("Eat shit brub");
        }

        ~SandboxApp(){

        }

};

Paopu::Application* Paopu::CreateApplication(){
    return new SandboxApp();
}


