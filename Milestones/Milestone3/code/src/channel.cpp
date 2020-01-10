
/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * channel.cpp source file with all declarations for Channel struct
 *
 */


#include "../include/channel.hpp"


//------------------------------------------------------------------------------


auto rangencha = std::bind(std::uniform_real_distribution<>(-1.0, 1.0), std::default_random_engine());


//------------------------------------------------------------------------------


/**
 * Default constructor for struct 
 * Instantatiates 3 dimensional square tensor with random value
 * 
 * @param size is the same for 3 dimensions
 * 
 */
Channel::Channel(unsigned size)
    : tensor{size, size, size}
{
    for (auto k = 0ul; k < tensor.size (2); ++ k)
        for (auto j = 0ul; j < tensor.size (1); ++ j)
            for (auto i = 0ul; i < tensor.size (0); ++ i)
                tensor.at(i,j,k) = rangencha();
}

