/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * layer.hpp header file with declaration of Layer class
 * 
 */


#ifndef LAYER_HPP
#define LAYER_HPP


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <random>
#include <cmath>


//------------------------------------------------------------------------------


namespace bnu = boost::numeric::ublas;
using FunctionPointer = std::function<bnu::matrix<double>(const bnu::matrix<double>&)>;


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
struct Layer {
    FunctionPointer m_activation, m_derivative; // public attributes
    bnu::matrix<double> m_output, m_weights, m_sum_z;

    // constructors
    Layer(unsigned, unsigned); // default constructor
    Layer(unsigned, unsigned, FunctionPointer, FunctionPointer);
    
    Layer(const Layer&) = default;		// copy constructor
    Layer(Layer&&) = default;		// move constructor
    Layer& operator=(const Layer&) = default; // assignment operator
    Layer& operator=(Layer&&) noexcept = default;

    ~Layer() = default;			// destructor

    // methods
    void feed_forward(const bnu::matrix<double>&);

    // getter and setter functions
    
    
};


#endif
