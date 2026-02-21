#define GLFW_INCLUDE_VULKAN
#if defined (__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
#include <GLFW/glfw3.h>


//debug
#include <iostream>
#include <stdexcept>

//Provides the EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {

public:
    void run() {
        initWindow(); //glfw
        initVulkan();
        mainLoop();
        cleanUp();
    }

private:

    GLFWwindow* window = nullptr;


    void initWindow() {
        glfwInit(); //glfw header method

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//GLFW was originally designed to create an OpenGL context, we need to tell it to not create an OpenGL context with a later call:
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Because handling resized windows takes special care that we’ll look into later, disable it for now with another window hint call:

        // creating the actual window. initialize the window.
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr); //The fourth parameter allows you to optionally specify a monitor to open the window on, and the last parameter is only relevant to OpenGL.
    }


    void initVulkan(){

    }




    //loops and checks for events like pressing the X button until the user has closed the window.This is also the loop where we’ll later call a function to render a single frame.
    void mainLoop() { 
        while (!glfwWindowShouldClose(window)) //returns false as long as window is open
        { 
            glfwPollEvents();// checks the OS event queue and processes any pending events
        }
    }





    void cleanUp() { //clean up resources by destroying it and terminating GLFW itself
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

 

int main()
{
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
}