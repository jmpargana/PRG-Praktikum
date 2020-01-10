
/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * conv3d.hpp header file with declaration of Conv3D class
 * 
 */


#ifndef CONV3D_HPP
#define CONV3D_HPP


#include <vector>
#include "./channel.hpp"
#include "./kernel.hpp"
#include <functional>


//------------------------------------------------------------------------------


using FunctionPointer = std::function<double(double)>;


//------------------------------------------------------------------------------


/**
 * This class contains the declaration of the Conv3D class
 * which represents a convolutional layer where a vector of tensor (channels)
 * is received as input from the previous layer and fed forward after all the calculations
 * with a vector of Kernels or filters
 * 
 * @param kernels is a vector of 4 dimensional tensors (or list of 3 dimensional tensors)
 * @param activation_function is set to LReLu as default
 *
 */
class Conv3D {
public:
    Conv3D(unsigned, unsigned, unsigned); // default constructor
    Conv3D(unsigned, unsigned, unsigned, FunctionPointer);  // constructor with given act function
    
    Conv3D(const Conv3D&) = default; 	    // copy constructor
    Conv3D(Conv3D&&) = default; 	 	    // move constructor
    Conv3D& operator=(const Conv3D&) = default; // assignment operator
    Conv3D& operator=(Conv3D&&) noexcept = default;

    ~Conv3D() = default;					    // destructor

    bnu::tensor<double> create_sub_channel(bnu::tensor<double>&, unsigned, 
                                           unsigned, unsigned, unsigned, unsigned);
    bnu::tensor<double> pad_channel(bnu::tensor<double>&, unsigned, unsigned);
    std::vector<Channel> feed_forward(std::vector<Channel>&);
    double calculate_inner_product(bnu::tensor<double>&, 
                                   bnu::tensor<double>&);

private:
    std::vector<std::vector<Kernel>> kernels;
    FunctionPointer activation_function;

};


#endif
