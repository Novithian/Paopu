#include <Paopu.h>

class SandboxApp : public Paopu::Application {
    public:
        SandboxApp(){
            
        }

        ~SandboxApp(){

        }

};

Paopu::Application* Paopu::CreateApplication(){
    return new SandboxApp();
}
