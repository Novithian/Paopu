#pragma once
#include "Core.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

namespace Paopu {
    struct PaopuWindow {
        PaopuWindow() = default;
        PaopuWindow(const char* title) :
                window_title(title){}
        PaopuWindow(const char* title, GLFWwindow* g_window) :
                window_title(title),
                glfw_window(g_window){}
        ~PaopuWindow() = default;

        static const uint32_t WINDOW_WIDTH{1280};
        static const uint32_t WINDOW_HEIGHT{720};
        static constexpr const char* DEFAULT_TITLE{"Paopu Application"};

        const char* window_title{""}; 

        GLFWwindow* glfw_window{nullptr};

        
    };

	/// Initializes GLFW and creates the window
	///
	///
	inline void build_window(PaopuWindow* window) {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		if (window->window_title == "") {
			window->window_title = window->DEFAULT_TITLE;
		}

		window->glfw_window = glfwCreateWindow(window->WINDOW_WIDTH, window->WINDOW_HEIGHT, window->window_title, nullptr, nullptr);
	}

	/// Cleans up before being destroyed
	///
	///
	inline void free_window(PaopuWindow* window) {
		
		glfwDestroyWindow(window->glfw_window);
		glfwTerminate();
	}

	/// Sets the title of the window
	///
	///
	inline void set_window_title(PaopuWindow* window, const char* title) {
		window->window_title = title;
		if(window->glfw_window != nullptr) {
			glfwSetWindowTitle(window->glfw_window, window->window_title);
		}
	}
}