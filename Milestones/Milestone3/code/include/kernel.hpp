/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * kernel.hpp header file with declaration of Kernel struct
 * 
 */


#ifndef KERNEL_HPP
#define KERNEL_HPP


#include "../lib/ublas/tensor.hpp"
#include <random>
#include <cmath>


//------------------------------------------------------------------------------


namespace bnu = boost::numeric::ublas;


//------------------------------------------------------------------------------


/**
 * This struct instantiates a square 3 dimensional tensor
 * as described in the Plenartermine4
 * the get, set and clear operations are public
 * 
 * @param tensor contains the obj
 *
 */
struct Kernel {
    Kernel(unsigned); // default constructor
    
    Kernel(const Kernel&) = default; 	    // copy constructor
    Kernel(Kernel&&) = default; 	 	    // move constructor
    Kernel& operator=(const Kernel&) = default; // assignment operator
    Kernel& operator=(Kernel&&) noexcept = default;

    ~Kernel() = default;					    // destructor

    bnu::tensor<double> tensor;

};


#endif
