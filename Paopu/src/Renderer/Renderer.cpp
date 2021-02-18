#include "Renderer.h"
#include "../Core/Window.h"
#include <stdexcept>
#include <cstring>
#include <set>

namespace Paopu {
 
    /// Creates the debug messenger
    VkResult CreateDebugUtilsMessengerEXT(  VkInstance instance,
                                            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                            const VkAllocationCallbacks* pAllocator,
                                            VkDebugUtilsMessengerEXT* pDebugMessenger ) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if(func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    /// Destroys the debug messenger
    void DestroyDebugUtilsMessengerEXT( VkInstance instance,
                                        VkDebugUtilsMessengerEXT debugMessenger,
                                        const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if(func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }   

    Renderer::Renderer() {

    }

    Renderer::~Renderer() {

    }

    void Renderer::free_renderer() {
        // See Device.h
        free_device(device);
        delete device;

        if(k_enable_validation_layers) {
            DestroyDebugUtilsMessengerEXT(instance, debug_messenger, nullptr);
        }

        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }

    // --------------------------------------------------------------------
    //                            - Vulkan -
    // --------------------------------------------------------------------

    void Renderer::init_backend(PaopuWindow* window) {
        device = new PaopuDevice();
        create_instance();
        setup_debug_messenger();
        create_surface(window);
        select_physical_device();
        create_logical_device();
    }

    bool Renderer::check_validation_layer_support() {
        uint32_t layer_count;

        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);

        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for(const char* layer_name : validation_layers) {
            bool layer_found = false;

            for(const auto& layer_properties : available_layers) {
                if(strcmp(layer_name, layer_properties.layerName) == 0) {
                    layer_found = true;
                    break;
                }
            }

            if(!layer_found) {
                return false;
            }

        }

        return true;
    }

    std::vector<const char*> Renderer::get_required_extensions() {
        uint32_t glfw_extension_count = 0;
        const char** glfw_extensions;

        glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

        std::vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_count);

        if(k_enable_validation_layers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        
        return extensions;
    }

    void Renderer::create_instance() {

        // Check to see if validations layers are supported
        if(k_enable_validation_layers && !check_validation_layer_support()) {
            throw std::runtime_error("[Renderer][Vulkan]: Requested Vulkan Validation Layers are not available!");
        }

        // Optional, but may provide some useful information to the driver
        // in order to optimize our application. 
        VkApplicationInfo app_info{};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Paopu Application";
        app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
        app_info.pEngineName = "Paopu";
        app_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        app_info.apiVersion = VK_API_VERSION_1_0;

        // Not optional. 
        // Tells the Vulkan driver which global extensions and balidation layers 
        // we want to use.
        VkInstanceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        auto extensions = get_required_extensions();
        create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        create_info.ppEnabledExtensionNames = extensions.data();
        
        VkDebugUtilsMessengerCreateInfoEXT debug_create_info;

        if(k_enable_validation_layers) {
            create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
            create_info.ppEnabledLayerNames = validation_layers.data();
            
            populate_debug_messenger_create_info(debug_create_info);
            create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_create_info;
        } else {
            create_info.enabledLayerCount = 0;
            create_info.pNext = nullptr;
        }

        if(vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to create Vulkan Instance!");
        }

    
    }

    void Renderer::select_physical_device() {
        uint32_t device_count = 0;

        vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

        if(device_count == 0) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(device_count);
        vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

        for(const auto& found_device : devices) {
            // See Device.h
            if(is_device_suitable(found_device, surface)) {
                device->physical_device = found_device;
                break;
            }
        }

        if(device->physical_device == VK_NULL_HANDLE) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to find a suitable GPU!");
        }

    }
    ///
    ///
    ///
    void Renderer::create_logical_device() {
        QueueFamilyIndices indices = find_queue_families(device->physical_device, surface);

        std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
        std::set<uint32_t> unique_queue_families = {indices.graphics_family.value(), indices.present_family.value()};



        float queue_priority = 1.0f;
        for(uint32_t queue_family : unique_queue_families) {
            VkDeviceQueueCreateInfo queue_create_info{};
            queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info.queueFamilyIndex = queue_family;
            queue_create_info.queueCount = 1;
            queue_create_info.pQueuePriorities = &queue_priority;
            queue_create_infos.push_back(queue_create_info);
        }

        VkPhysicalDeviceFeatures device_features{};

        VkDeviceCreateInfo create_info{};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
        create_info.pQueueCreateInfos = queue_create_infos.data();

        create_info.pEnabledFeatures = &device_features;

        create_info.enabledExtensionCount = 0;

        if(k_enable_validation_layers)	{
            create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
            create_info.ppEnabledLayerNames = validation_layers.data();
        } else {
            create_info.enabledLayerCount = 0;
        }

        if(vkCreateDevice(device->physical_device, &create_info, nullptr, &device->logical_device) != VK_SUCCESS) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to create logical device!");
        }

        vkGetDeviceQueue(device->logical_device, indices.graphics_family.value(), 0, &device->graphics_queue);
        vkGetDeviceQueue(device->logical_device, indices.present_family.value(), 0, &device->present_queue);

    }

    void Renderer::create_surface(PaopuWindow* window) {
        if(glfwCreateWindowSurface(instance, window->glfw_window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to create a window surface!");
        }
    }

    void Renderer::setup_debug_messenger() {
        
        if(!k_enable_validation_layers) return;
        
        VkDebugUtilsMessengerCreateInfoEXT create_info;
        populate_debug_messenger_create_info(create_info);
        
        if(CreateDebugUtilsMessengerEXT(instance, &create_info, nullptr, &debug_messenger) != VK_SUCCESS) {
            throw std::runtime_error("[Renderer][Vulkan]: Failed to setup debug messenger!");
        }
    }
            
    void Renderer::populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& create_info) {
        create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity =    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
                                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
                                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType =    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = debug_callback;
        create_info.pUserData = nullptr; // Optional
    }

}
