
/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * conv3d.cpp source file with all declarations for Conv3D class
 *
 */


#include "../include/conv3d.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates a vector of vector of Kernels (square 3 dimensional tensors of given size)
 * with the LReLu activation function
 *
 * @param tensor_size square size of 3 dimensional filters
 * @param particles size of 4th dimension
 * @param size amount of filters (Kernels)
 * 
 */
Conv3D::Conv3D(unsigned tensor_size, 
               unsigned particles, 
               unsigned size)
    : kernels{size, std::vector<Kernel>(particles, Kernel(tensor_size))}
{
    activation_function = [](double input) -> double { return std::max(input, input*0.01); };
}


//------------------------------------------------------------------------------


/**
 * Instantatiates a vector of vector of Kernels (square 3 dimensional tensors of given size)
 * with a given activation function
 *
 * @param tensor_size square size of 3 dimensional filters
 * @param particles size of 4th dimension
 * @param size amount of filters (Kernels)
 * @param activation_function lambda defined somewhere else
 * 
 */
Conv3D::Conv3D(unsigned tensor_size,
               unsigned particles,
               unsigned size,
               FunctionPointer activation_function)
    : kernels{size, std::vector<Kernel>(particles, Kernel(tensor_size))}
{
    this->activation_function = activation_function;
}


//------------------------------------------------------------------------------


/**
 * This function simplifies the calculation process of the inner product of both
 * tensors (channel and filter) in order to avoid a 5 nested for loop in the 
 * feed forward function
 *
 * @param channel is a 3 dimensional square tensor
 * @param kernel also
 *
 * @return activated value to be directly saved on the resulting channel
 *
 */
double Conv3D::calculate_inner_product(bnu::tensor<double>& channel, 
                                       bnu::tensor<double>& kernel)
{
    if (channel.size(2)!=kernel.size(2) || channel.size(1)!=kernel.size(1) || channel.size(0)!=kernel.size(0))
        throw std::runtime_error("Unmatching sizes on kernel and channel part");

    double acc = 0.0;
    for (auto k = 0ul; k < channel.size (2); ++ k)
        for (auto j = 0ul; j < channel.size (1); ++ j)
            for (auto i = 0ul; i < channel.size (0); ++ i)
                acc += channel.at(i,j,k) * kernel.at(i,j,k);

    return activation_function(acc);
}


//------------------------------------------------------------------------------


/**
 * Feed Forward for a convolutional layer 
 * Iterate over all filters in the kernels list
 * Append zeros to the missing vectors on all four dimensions (Padding in filtering)
 * Iterate then over all the 4 dimensions retaining each of the tensors
 * Iterate over the tensors and performe the inner product with a matching size 
 * of each of the tensors saving the result on a new Channel which gets appended to a vector
 *
 * @param channels is a list of square 3 dimensional tensors
 *
 * @return the resulting tensors for the next convolutional layer
 *
 */
std::vector<Channel>& Conv3D::feed_forward(std::vector<Channel>& channels)
{
    
}




