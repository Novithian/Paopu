#include "Renderer.h"

#include <stdexcept>
#include <vector>
#include <iostream>

namespace Paopu {
    
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

    }

    void Renderer::cleanup() {
        vkDestroyInstance(m_Instance, nullptr);
    }

    // --------------------------------------------------------------------
    //                            - Vulkan -
    // --------------------------------------------------------------------

    void Renderer::initBackend() {
        createInstance();
    }

    void Renderer::createInstance() {
        // Optional, but may provide some useful information to the driver
        // in order to optimize our application. 
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Paopu Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.pEngineName = "Paopu";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Not optional. 
        // Tells the Vulkan driver which global extensions and balidation layers 
        // we want to use.
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "[Renderer]: Available extensions found:\n";

        for(const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '1';
        }


        if(vkCreateInstance(&createInfo, nullptr, &m_Instance)) {
            throw std::runtime_error("[Renderer]: Failed to create Vulkan Instance!");
        }

    
    }

}
