#pragma once
#include "../../Core/Core.h"

//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
#include <Vulkan/vulkan.h>

#include <vector>
#include <optional>

namespace Paopu {
	///
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
	inline PAOPU_API QueueFamilyIndices find_queue_families(VkPhysicalDevice found_device, VkSurfaceKHR& surface) {
		QueueFamilyIndices indices;

		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(found_device, &queue_family_count, nullptr);

		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(found_device, &queue_family_count, queue_families.data());

		int i =0;   
		for(const auto& queue_family : queue_families) {
			if(queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphics_family = i;
			}

			VkBool32 present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(found_device, i, surface, &present_support);

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
	inline PAOPU_API bool is_device_suitable(VkPhysicalDevice found_device, VkSurfaceKHR& surface) {
		return find_queue_families(found_device, surface).is_complete();
	}
}
