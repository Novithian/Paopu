#pragma once

#include "../../Core/Core.h"
#include "../../Core/Window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <Vulkan/vulkan.h>

#include <vector>
#include <algorithm>

namespace Paopu {
    // Forward Declarations

    ///
    ///
    ///
    struct PAOPU_API PaopuSwapchain {
        VkSwapchainKHR swapchain;
        std::vector<VkImage> images;
        VkFormat image_format;
        VkExtent2D extent;
        std::vector<VkImageView> image_views;
    };

    ///
    ///
    ///
    inline PAOPU_API void free_swapchain(VkDevice logical_device, PaopuSwapchain* swapchain) {
        for(auto image_view : swapchain->image_views) {
            vkDestroyImageView(logical_device, image_view, nullptr);
        }
        vkDestroySwapchainKHR(logical_device, swapchain->swapchain, nullptr);
    }

    ///
    ///
    ///
    struct PAOPU_API PaopuSwapchainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> present_modes;
    };

    ///
    ///
    ///
    inline PAOPU_API PaopuSwapchainSupportDetails query_swap_chain_support(VkPhysicalDevice device, VkSurfaceKHR surface) {
        PaopuSwapchainSupportDetails details{};

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t format_count;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, nullptr);

        if(format_count != 0) {
            details.formats.resize(format_count);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &format_count, details.formats.data());
        }

        uint32_t present_mode_count;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, nullptr);

        if(present_mode_count != 0) {
            details.present_modes.resize(present_mode_count);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &present_mode_count, details.present_modes.data());
        }

        return details;
    }

    /// Selects a Surface Format based on the available selection.
    /// Note(devon): Color Depth
    /// 
    inline PAOPU_API VkSurfaceFormatKHR select_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& available_formats) {
        for(const auto& available_format : available_formats) {
            if( available_format.format == VK_FORMAT_B8G8R8A8_SRGB && 
                // Using SRGB as it results is more accurate perceived colors
                available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return available_format;
            }
        }

        return available_formats[0];
    }

    /// Selects a Present Mode based on the available selection.
    /// A Present Mode is simply conditions for swapping images to the screen (Mainbox/FIFO/etc) 
    ///
    /// `VK_PRESENT_MODE_IMMEDIATE_KHR`: Images submitted by your application are transferred to the
    ///     screen right away, which may result in tearing.
    /// `VK_PRESENT_MODE_FIFO_KHR`: The swapchain is a queue where the display takes an image from
    ///     the front of the queue when the display is refreshed and the program inserts rendered
    ///     images at the back of the queue. If the queue is full then the program has to wait. This
    ///     this most similar to vertical sync as found in modern games. The moment that the display
    ///     is refreshed is known as "vertical blank".
    /// `VK_PRESENT_MODE_FIFO_RELAXED_KHR`: This mode only differs from the previous one if the 
    ///     application is late and the queue was empty at the last vertical blank. Instead of 
    ///     waiting for the next vertical blank, the image is transferred right away when it finally
    ///     arrives. This may result in visible tearing.
    /// `VK_PRESENT_MODE_MAILBOX_KHR`: This is another variation of the second mode. Instead of 
    ///     blocking the application when the queue is full, the images that are arleady queued are
    ///     are simply replaced with the newer ones. This mode can be used to implement triple
    ///     buffering, which allows you to avoid tearing with significantly less latency issues
    ///     than standard vertical sync that uses double buffering.
    ///
    ///
    inline PAOPU_API VkPresentModeKHR select_swap_present_mode(const std::vector<VkPresentModeKHR>& available_modes) {
        for(const auto& available_mode : available_modes) {
            if(available_mode == VK_PRESENT_MODE_MAILBOX_KHR){
                return available_mode;
            }
        }

        return VK_PRESENT_MODE_FIFO_KHR;
    }

    /// Resolution of images in the swapchain
    ///
    ///
    inline PAOPU_API VkExtent2D select_swap_extent(PaopuWindow* window, const VkSurfaceCapabilitiesKHR& capabilities) {
        if(capabilities.currentExtent.width != UINT32_MAX) {
            return capabilities.currentExtent;
        } else {
            int width, height;
            glfwGetFramebufferSize(window->glfw_window, &width, &height);

            VkExtent2D actual_extent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };

            actual_extent.width = std::max(capabilities.minImageExtent.width, 
                                    std::min(capabilities.maxImageExtent.width, actual_extent.width));

            actual_extent.height = std::max(capabilities.minImageExtent.height, 
                                    std::min(capabilities.maxImageExtent.height, actual_extent.height));

            return actual_extent;

        }
    }

}


