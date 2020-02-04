/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * MaxPool3D.hpp header file with declaration of MaxPool3D class
 * 
 */


#ifndef MAXPOOL3D_HPP
#define MAXPOOL3D_HPP


#include <vector>
#include "./channel.hpp"
#include "./kernel.hpp"
#include <functional>



//------------------------------------------------------------------------------


/**
 * Struct that represents the max pool layer needed for the convolutional neural network
 * its only function is to feed forward the input and to the next layer simplifying the
 * channel to half the size
 *
 */
struct MaxPool3D {
    MaxPool3D() {  } // default constructor
    
    MaxPool3D(const MaxPool3D&) = default; 	    // copy constructor
    MaxPool3D(MaxPool3D&&) = default; 	 	    // move constructor
    MaxPool3D& operator=(const MaxPool3D&) = default; // assignment operator
    MaxPool3D& operator=(MaxPool3D&&) noexcept = default;

    ~MaxPool3D() = default;					    // destructor

    std::vector<Channel> feed_forward(const std::vector<Channel>&);
    double find_max(const bnu::tensor<double>*, unsigned, unsigned, unsigned);
};


#endif
