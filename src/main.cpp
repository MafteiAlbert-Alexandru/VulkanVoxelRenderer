#include "config.hpp"
#include "voxelengine.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
    Config config {
        .window_width=800,
        .window_height=600,
        .window_title="VulkanVoxelRenderer"
    };
    VoxelEngine engine(config);

    try{
        engine.run();
    }catch(std::exception&e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;


    return 0;
}