/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * channel.hpp header file with declaration of Channel struct
 * 
 */


#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <boost/numeric/ublas/tensor.hpp>
#include <random>
#include <cmath>


//------------------------------------------------------------------------------


namespace bnu = boost::numeric::ublas;


//------------------------------------------------------------------------------


/**
 * This struct implements the concept of Channel which holds the value
 * of a 3 dimensional square tensor with the representation of the particles 
 * as explained in the Plenartermine4
 * its a struct, since it only contains an attribute which should be easily
 * manipulated (get, set, clear, etc.)
 * 
 * @param tensor holds the three
 *
 */
struct Channel {
    Channel(unsigned); // default constructor
    
    Channel(const Channel&) = default; 	    // copy constructor
    Channel(Channel&&) = default; 	 	    // move constructor
    Channel& operator=(const Channel&) = default; // assignment operator
    Channel& operator=(Channel&&) noexcept = default;

    ~Channel() = default;					    // destructor

    bnu::tensor<double> tensor;

};


#endif
