/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * muli_layer_perceptron.hpp header file with declaration of MultiLayerPerceptron class
 * 
 */


#ifndef MULTI_LAYER_PERCEPTRON_HPP
#define MULTI_LAYER_PERCEPTRON_HPP


#include "./layer.hpp"
#include <vector>


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
class MultiLayerPerceptron {
public:
    MultiLayerPerceptron(std::vector<unsigned>&&); // default constructor
    
    MultiLayerPerceptron(const MultiLayerPerceptron&) = default; 	    // copy constructor
    MultiLayerPerceptron(MultiLayerPerceptron&&) = default; 	 	    // move constructor
    MultiLayerPerceptron& operator=(const MultiLayerPerceptron&) = default; // assignment operator
    MultiLayerPerceptron& operator=(MultiLayerPerceptron&&) noexcept = default;

    ~MultiLayerPerceptron() = default;					    // destructor

    bnu::matrix<double> forward_propagation(bnu::matrix<double>&&); 	    // member functions
    void back_propagation(bnu::matrix<double>&&, bnu::matrix<double>&&);
    Layer& operator[](unsigned); 					    // getter and setter
            
private:
    std::vector<Layer> m_layers;    
};


#endif
