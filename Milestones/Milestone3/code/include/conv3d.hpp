
/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * muli_layer_perceptron.hpp header file with declaration of Conv3D class
 * 
 */


#ifndef MULTI_LAYER_PERCEPTRON_HPP
#define MULTI_LAYER_PERCEPTRON_HPP


#include <vector>
#include "./channel.hpp"
#include "./kernel.hpp"
#include <functional>


//------------------------------------------------------------------------------


using FunctionPointer = std::function<double(double)>;


//------------------------------------------------------------------------------


/**
 * This class contains a neural network
 * It has a two dimenstional vector of neurons which transmits layer to layer
 * the matrix multiplication with each neuron's weights and performs back
 * propagation to correct its predictions
 * It can also be used to predict, once the weights are properly defined
 * 
 * @param layers contains a list of all neurons in each layer
 * @param outputs contains the last layers activated vector 
 * @param and errors contains the target value
 *
 */
class Conv3D {
public:
    Conv3D(int); // default constructor
    
    Conv3D(const Conv3D&) = default; 	    // copy constructor
    Conv3D(Conv3D&&) = default; 	 	    // move constructor
    Conv3D& operator=(const Conv3D&) = default; // assignment operator
    Conv3D& operator=(Conv3D&&) noexcept = default;

    ~Conv3D() = default;					    // destructor

    std::vector<Channel>& feed_forward(std::vector<Channel>&);
    double calculate_inner_product(bnu::tensor<double>&, bnu::tensor<double>&);

private:
    std::vector<Kernel> kernels;
    FunctionPointer activation_function;

};


#endif
