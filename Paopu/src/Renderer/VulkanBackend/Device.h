#pragma once
#include "../../Core/Core.h"
#include "Swapchain.h"
//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
#include <Vulkan/vulkan.h>

#include <vector>
#include <set>
#include <optional>
#include <string>

namespace Paopu {
	
	static const std::vector<const char*> s_device_extensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	/// Container for the Vulkan backend's devices and queues
	///
	///
    struct PAOPU_API PaopuDevice {
        VkPhysicalDevice physical_device{VK_NULL_HANDLE};
		VkDevice logical_device;
		VkQueue graphics_queue;
		VkQueue present_queue;
		
    };

	/// 
	///
	///
    struct PAOPU_API QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
		std::optional<uint32_t> present_family;

        bool is_complete() {
            return graphics_family.has_value() && present_family.has_value();
        }
    
    };

	///
	///
	///
	inline PAOPU_API void free_device(PaopuDevice* device) {
		vkDestroyDevice(device->logical_device, nullptr);
	}
    
	///
	///
	///
	inline PAOPU_API QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR& surface) {
		QueueFamilyIndices indices;

		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

		int i =0;   
		for(const auto& queue_family : queue_families) {
			if(queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphics_family = i;
			}

			VkBool32 present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);

			if(present_support) {
				indices.present_family = i;
			}

			if(indices.is_complete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	///
	///
	///
	inline PAOPU_API bool check_device_extension_support(VkPhysicalDevice& device) {
		uint32_t extension_count;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, nullptr);

		std::vector<VkExtensionProperties> available_extensions(extension_count);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count, available_extensions.data());

		std::set<std::string> required_extensions(s_device_extensions.begin(), s_device_extensions.end());

		for(const auto& extension : available_extensions) {
			required_extensions.erase(extension.extensionName);
		}

		return required_extensions.empty();
	}

	///
	///
	///
	inline PAOPU_API bool is_device_suitable(VkPhysicalDevice device, VkSurfaceKHR& surface) {
		QueueFamilyIndices indices = find_queue_families(device, surface);
		bool extensions_supported = check_device_extension_support(device);

		bool swapchain_adaquate = false;
		if(extensions_supported) {
			PaopuSwapchainSupportDetails swapchain_support = query_swap_chain_support(device, surface);
			swapchain_adaquate = !swapchain_support.formats.empty() && !swapchain_support.present_modes.empty();
		}


		return indices.is_complete() && extensions_supported && swapchain_adaquate;
	}

	
}
