#pragma once
#include "../Core/Core.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

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
            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData ){
                std::cerr << "[Renderer][Validation Layer]: " << pCallbackData->pMessage << 'n';
                return VK_FALSE;
            }

            /// Sets up the Debug Messenger
            ///
            ///
            void setupDebugMessenger();

            /// Populates the debug messenger create info struct
            ///
            ///
            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

            /// Creates a Vulkan instance
            ///
            ///
            void createInstance();

            /// Checks to see if all of the requested Vulkan Validation
            /// Layers, via `m_ValidationLayers` are available 
            ///
            /// Returns true or false whether or not the requested Validation Layers
            /// are available.
            bool checkValidationLayerSupport();

            /// TODO: write description
            ///
            /// Returns a vector of const char*
            std::vector<const char*> getRequiredExtensions();

        private:
            VkInstance m_Instance;
            VkDebugUtilsMessengerEXT m_DebugMessenger;

            const std::vector<const char*> m_ValidationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

            #ifdef NDEBUG
                const bool m_EnableValidationLayers = false;
            #else
                const bool m_EnableValidationLayers = true;
            #endif

    };



}