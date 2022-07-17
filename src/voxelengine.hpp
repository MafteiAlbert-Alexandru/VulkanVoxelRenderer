#pragma once
#define VULKAN_HPP_NO_CONSTRUCTORS
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include "config.hpp"
class VoxelEngine
{

public:
    VoxelEngine(Config config) : config_(config)
    {

        glfwInit();

        // Because GLFW was originally designed to create an OpenGL context,
        // we need to tell it to not create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // TODO: Implement resizing

        window_ = glfwCreateWindow(config_.window_width, config_.window_height, config_.window_title.c_str(), nullptr, nullptr);
        vk::ApplicationInfo application_info{
            .pApplicationName = config_.window_title.c_str(),
            .pEngineName = "VoxelEngine",
            .engineVersion = VK_MAKE_VERSION(0, 0, 0),
            .apiVersion = VK_API_VERSION_1_0};

        vk::InstanceCreateInfo create_info{
            .pApplicationInfo = &application_info};

        uint32_t glfw_extension_count = 0;
        const char **glfw_extensions;
        glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
        std::vector<const char *> extensions = std::vector<const char *>(glfw_extensions, glfw_extensions + glfw_extension_count);

        if(config_.validation_layers.empty())
        {
            create_info.enabledLayerCount=0;
        }else {
            uint32_t layer_count;
            vk::enumerateInstanceLayerProperties(&layer_count, nullptr);
            std::vector<vk::LayerProperties> available_layers(layer_count);
            vk::enumerateInstanceLayerProperties(&layer_count, available_layers.data());
            for(const char *layer_name: config_.validation_layers)
            {
                if(std::find_if(available_layers.begin(), available_layers.end(), [layer_name](vk::LayerProperties const &properties) {
                    return strcmp(layer_name, properties.layerName)==0;
                })==available_layers.end())
                {
                    throw std::runtime_error("");
                }
                
            }
            create_info.enabledLayerCount=static_cast<uint32_t>(config_.validation_layers.size());
            create_info.ppEnabledLayerNames=config_.validation_layers.data();
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        create_info.ppEnabledExtensionNames = extensions.data();
        create_info.enabledLayerCount = 0;

        instance_=vk::createInstance(create_info, nullptr, &instance_);
        if(!config_.validation_layers.empty())
        {
            vk::DebugUtilsMessengerCreateInfoEXT debug_create_info {
                .messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eGeneral | vk::DebugUtilsMessageSeverityFlagBitsEXT::ePerformance | vk::DebugUtilsMessageSeverityFlagBitsEXT::eValidation,
                .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DE  BUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
                .pfnUserCallback = debugCallback,
                .pUserData=nullptr
            };
            vk::DispatchLoaderDynamic wtf;
            instance_.createDebugUtilsMessengerEXT();
        }

    }

    ~VoxelEngine()
    {
        glfwDestroyWindow(window_);
        glfwTerminate();
    }

    void run()
    {
        while (!glfwWindowShouldClose((GLFWwindow *)window_))
        {
            glfwPollEvents();
        }
    }

private:
    const Config config_;
    GLFWwindow *window_;
    vk::Instance instance_;
    vk::DebugUtilsMessengerEXT debugMessenger_;
    vk::PhysicalDevice device;

    vk::SurfaceKHR surface_;

};
