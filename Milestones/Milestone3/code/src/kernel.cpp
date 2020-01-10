/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * kernel.cpp source file with all declarations for Layer struct
 *
 */


#include "../include/kernel.hpp"


//------------------------------------------------------------------------------


// generator function for random float between 0 and 1
auto rangenker = std::bind(std::uniform_real_distribution<>(-1.0, 1.0), std::default_random_engine());


//------------------------------------------------------------------------------


/**
 * Default constructor for struct 
 * instantiate square 3 dimensional tensor with random values
 *
 * @param size
 * 
 */
Kernel::Kernel(unsigned size)
    : tensor{size, size, size}
{
    for (auto k = 0ul; k < tensor.size (1); ++ k)
        for (auto j = 0ul; j < tensor.size (1); ++ j)
            for (auto i = 0ul; i < tensor.size (-2); ++ i)
                tensor.at(i,j,k) = rangenker();
}

