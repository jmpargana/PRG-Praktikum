/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * muli_layer_perceptron.hpp header file with declaration of Kernel class
 * 
 */


#ifndef MULTI_LAYER_PERCEPTRON_HPP
#define MULTI_LAYER_PERCEPTRON_HPP


#include <boost/numeric/ublas/tensor.hpp>


//------------------------------------------------------------------------------


namespace bnu = boost::numeric::ublas;


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
class Kernel {
public:
    Kernel(std::vector<unsigned>&&); // default constructor
    
    Kernel(const Kernel&) = default; 	    // copy constructor
    Kernel(Kernel&&) = default; 	 	    // move constructor
    Kernel& operator=(const Kernel&) = default; // assignment operator
    Kernel& operator=(Kernel&&) noexcept = default;

    ~Kernel() = default;					    // destructor

private:
    bnu::tensor<double> tensor;

};


#endif
