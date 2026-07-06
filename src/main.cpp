#define GLFW_INCLUDE_VULKAN
#if defined (__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

#include <iostream>
#include <stdexcept>

#include <SDL3/SDL.h> //platform specific extension stuff window/input
#include <SDL3/SDL_vulkan.h> 

//Provides the EXIT_SUCCESS and EXIT_FAILURE macros
#include <cstdlib>


VkInstance instance{ VK_NULL_HANDLE };

//error handling. Most Vulkan functions can fail in different ways and return a VkResult value. 
//this return the return the result. do this in more sophisticated way in future.
static inline void chk(VkResult result) {
    if (result != VK_SUCCESS) {
        std::cerr << "Vulkan call returned an error (" << result << ")\n";
        exit(result);
    }
}

class TBCApplication {

    public:
        void run(int argc, char* argv[]) 
        { 
            //create instance > select device 
            initVulkan();
            selectDeviceVulkan(argc, argv);

        }

    private:
        void initVulkan()
            {
            VkApplicationInfo appInfo {  //structure type
                    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO, //.sType = a structure member 
                    .pApplicationName = "TBCApplication",
                    .apiVersion = VK_API_VERSION_1_3
            };

            //for platform specific window/input helper. no more need to do VK_KHR_win32_surface / GLFW etc. 
            uint32_t instanceExtensionsCount{ 0 };
            char const* const* instanceExtensions{ SDL_Vulkan_GetInstanceExtensions(&instanceExtensionsCount) };
            
            //now connect the application to Vulkan
            VkInstanceCreateInfo instanceCI{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pApplicationInfo = &appInfo,
                .enabledExtensionCount = instanceExtensionsCount,
                .ppEnabledExtensionNames = instanceExtensions,
            };
            chk(vkCreateInstance(&instanceCI, nullptr, &instance)); //calling vkCreateInstance creates our instance.
        }

        void selectDeviceVulkan(int argc, char* argv[])
        {
            uint32_t deviceCount{ 0 };
            chk(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr)); //ask how many device exists
            std::vector<VkPhysicalDevice> devices(deviceCount); //allocate enough storage
            chk(vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data())); //ask Vulkan to fill that storage

            uint32_t deviceIndex{ 0 };
            if (argc > 1) {
                deviceIndex = std::stoi(argv[1]);
                assert(deviceIndex < deviceCount); //error handling/ to make sure its in available range.
            }

            //output selected device
            VkPhysicalDeviceProperties2 deviceProperties{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
            vkGetPhysicalDeviceProperties2(devices[deviceIndex], &deviceProperties);
            std::cout << "Selected device: " << deviceProperties.properties.deviceName <<  "\n";
        }



};

int main(int argc, char* argv[])
{
    TBCApplication app;

    try {
        app.run(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
}