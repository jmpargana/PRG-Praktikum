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
#include <numeric>
#include <cmath>		// for std::exp(double) function


//------------------------------------------------------------------------------


/**
 * This class contains a the definition of a Perceptron
 * @see perceptron
 * 
 * @param activation_function is a pointer to a function that can be changed
 * @param inputs contains a list of all inputs which can be variable with their weights
 *
 */
class Neuron {
public:
    // constructors
    Neuron();			// default constructor
    Neuron(std::function<void(int, int)>);
    
    Neuron(Neuron&);		// copy constructor
    Neuron(Neuron&&);		// move constructor
    Neuron& operator=(const Neuron&); // assignment operator
    Neuron& operator=(Neuron&&) noexcept;

    ~Neuron();			// destructor

    // getters and setters
    Neuron& set_inputs(std::vector<std::pair<double, double>>&);
    Neuron& set_activation_function(std::function<void(int, int)>);
    std::vector<std::pair<double, double>>& get_inputs();
    const std::vector<std::pair<double, double>>& get_inputs() const;

    // operation overloads
    double sum(const std::vector<double>&);
    
    
    
private:
    std::function<void(int, int)> activation_function;
    std::vector<std::pair<double, double>> inputs;
    std::vector<double> weights;
    
};


//------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream&, Neuron const&); // output stream
std::istream& operator>>(std::istream&, Neuron&); // input stream

std::ofstream& operator<<(std::ofstream&, Neuron const&); // output file stream
std::ifstream& operator>>(std::ifstream&, Neuron&); // input file stream


#endif
