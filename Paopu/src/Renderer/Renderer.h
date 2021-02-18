#pragma once
#include "../Core/Core.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//#include <Vulkan/vulkan.h>

#include "VulkanBackend/Device.h"

#include <vector>
#include <iostream>

namespace Paopu {
    struct PaopuWindow;
    class PAOPU_API Renderer {

        public: 
            Renderer();
            ~Renderer();
           
            /// Handles the initializing of our respective backend
            ///
            ///
            void init_backend(PaopuWindow* window);

            void free_renderer();
 
    // --------------------------------------------------------------------
    //                            - Vulkan -
    // --------------------------------------------------------------------
        private:
            /// Handles Vulkan Validation Layer calls, and determines if the application
            /// should abort based on the severity of the message severity.
            ///
            /// `messageSeverity` 
            ///     VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: Diagnostic message
            ///     VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: Informational message like 
            ///         the creation of a resource
            ///     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: Message about behavior
            ///         that is not necessarily and error, but very likely a bug in your app
            ///     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: Message about behavior 
            ///         that is invalid and may cause crashes
            ///
            /// `messageType`
            ///     VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: Some event has happened
            ///         that is unrelated to the specification or performance
            ///     VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: Something has happended
            ///         that violates the specification or indicates a possible mistake
            ///     VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: Potential non-optimal 
            ///         use of Vulkan
            ///
            /// `pCallbackData`
            ///     VkDebugUtilsMessengerCallbackDataEXT:
            ///         `pMessage`: The debug message as a null-terminated string
            ///         `pObjects`: Array of Vulkan object handles related to the message
            ///         `objectCount`: Number of objects in array
            ///
            /// `pUserData`: contains a pointer that was specified during the setup of the
            ///     callback and allows you to pass your own data to it.
            static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
                VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                VkDebugUtilsMessageTypeFlagsEXT message_type,
                const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                void* user_data ){
                std::cerr << "[Renderer][Validation Layer]: " << callback_data->pMessage << 'n';
                return VK_FALSE;
            }

            /// Sets up the Debug Messenger
            ///
            ///
            void setup_debug_messenger();

            /// Populates the debug messenger create info struct
            ///
            ///
            void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& create_info);

            /// Creates a Vulkan instance
            ///
            ///
            void create_instance();

            /// Checks to see if all of the requested Vulkan Validation
            /// Layers, via `m_ValidationLayers` are available 
            ///
            /// Returns true or false whether or not the requested Validation Layers
            /// are available.
            bool check_validation_layer_support();

            /// TODO: write description
            ///
            /// Returns a vector of const char*
            std::vector<const char*> get_required_extensions();

            /// Selects a graphics card in the running system that supports
            /// the features we need. Multiple graphics cards can be selected
            /// simultaneously. 
            void select_physical_device();

            /// Creates the logical device interface to communitcate
            /// to our physical device(gpus)
            ///
            void create_logical_device();

            ///
            ///
            ///
            void create_surface(PaopuWindow* window);
            

        private:
            VkInstance instance;
            VkSurfaceKHR surface;
            VkDebugUtilsMessengerEXT debug_messenger;
            PaopuDevice* device;

            const std::vector<const char*> validation_layers = {
                "VK_LAYER_KHRONOS_validation"
            };

            #ifdef NDEBUG
                const bool k_enable_validation_layers = false;
            #else
                const bool k_enable_validation_layers = true;
            #endif

    };



}