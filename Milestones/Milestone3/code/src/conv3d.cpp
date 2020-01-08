
/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * layer.cpp source file with all declarations for Layer class
 *
 */


#include "../include/conv3d.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates Layers of Neurons given a certain topology
 * first layer doesn't need to be instantiated since it contains only the inputs
 * @param topology list of int with size of each layer
 * 
 */
Conv3D::Conv3D(int particles, int size)
    : kernels{size, }
{
    activation_function = [](double input) double -> { return std::max(input, input*0.01); };
}


//------------------------------------------------------------------------------


Conv3D::Conv3D(int particles, int size, FunctionPointer activation_function)
    : kernels{size, particles}, activation_function{activation_function}
{

}


//------------------------------------------------------------------------------


double Conv3D::calculate_inner_product(bnu::tensor<double>& channel, 
                                       bnu::tensor<double>& kernel)
{
    double acc = 0.0;

    for (auto k = 0ul; k < channel.size (2); ++ k)
        for (auto j = 0ul; j < channel.size (1); ++ j)
            for (auto i = 0ul; i < channel.size (0); ++ i)
                acc += channel(i,j,k)*kernel(i,j,k);

    return activation_function(acc);
}
