/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * layer.cpp source file with all declarations for Layer class
 *
 */


#include "../include/kernel.hpp"


//------------------------------------------------------------------------------


auto rangen = std::bind(std::uniform_real_distribution<>(0.0, 1.0), std::default_random_engine());


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates Layers of Neurons given a certain topology
 * first layer doesn't need to be instantiated since it contains only the inputs
 * @param topology list of int with size of each layer
 * 
 */
Kernel::Kernel(int momentum, int azimuth, int inclination)
    : tensor{momentum, azimuth, inclination}
{
    for (auto k = 0ul; k < t.size (2); ++ k)
        for (auto j = 0ul; j < t.size (1); ++ j)
            for (auto i = 0ul; i < t.size (0); ++ i)
                t.at(i,j,k) = rangen();
}

