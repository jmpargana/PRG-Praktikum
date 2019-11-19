/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * neuron.hpp header file with declaration of neuron class
 * 
 */


#ifndef NEURON_HPP
#define NEURON_HPP


#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <utility>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>		// for std::exp(double) function
#include <random>


//------------------------------------------------------------------------------


// this alias will save a lot of ink
using FunctionPointer = std::function<std::vector<double>(std::vector<double>)>;


/**
 * This class contains a the definition of a Perceptron 
 * it creates a neuron expecting a given input size from the previous layer
 * it has an function variable that activates the sum of weights and inputs
 * according to how it is defined. Its derivative to calculate the gradient
 * and a back propagation function to replace the weights with the new ones
 * 
 * @param size defined the expected input size from previous layer
 * @param activation_function is a pointer to a function that can be changed
 * @param derivative_function is a pointer to the activation function's derivative 
 * @param output_val stores the activated value to be corrected via gradient
 * @param weights contains a vector of the weights pointing to this neuron
 *
 */
class Neuron {
public:
    // constructors
    Neuron();			// default constructor
    Neuron(unsigned);		// size of next layer
    Neuron(unsigned, FunctionPointer);
    Neuron(unsigned, FunctionPointer, FunctionPointer);
    
    Neuron(const Neuron&) = default;		// copy constructor
    Neuron(Neuron&&)= default;		// move constructor
    Neuron& operator=(const Neuron&) = default; // assignment operator
    Neuron& operator=(Neuron&&) noexcept = default;

    ~Neuron() = default;			// destructor

    // getters and setters
    double& operator[](int);	// get and set weight value    
    double get_output_val();
    std::vector<double>* get_weights();

    void set_weights(std::vector<double>&);
    void set_output(double);

    // methods
    std::vector<double> activation(std::vector<double>&);    
    std::vector<double> derivative(std::vector<double>&);
    
    void calculate_gradients();
    void correct_weights();
    
    
private:
    FunctionPointer m_activation_function, m_derivative_function;
    std::vector<double> m_weights;
    double m_output_val;    
};


//------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream&, Neuron const&); // output stream
std::istream& operator>>(std::istream&, Neuron&); // input stream

std::ofstream& operator<<(std::ofstream&, Neuron const&); // output file stream
std::ifstream& operator>>(std::ifstream&, Neuron&); // input file stream


#endif
