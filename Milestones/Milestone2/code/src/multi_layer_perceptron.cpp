/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * multi_layer_perceptron.cpp source file with all declarations for MultiLayerPerceptron class
 *
 */


#include "../include/multi_layer_perceptron.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * @param topology list of unsigneds with size of each layer
 * 
 */
MultiLayerPerceptron::MultiLayerPerceptron(std::vector<unsigned>&& topology)
{
    for (unsigned i_layer=1; i_layer<topology.size(); ++i_layer)
	m_layers.push_back(Layer(topology[i_layer - 1], topology[i_layer]));
}


//------------------------------------------------------------------------------


/**
 * Getter for m_layer member variable
 * subscript operator overload
 * return the indexed layer instance
 * @param index 
 * @param Layer class
 * 
 */
Layer& MultiLayerPerceptron::operator[](unsigned index)
{
    return m_layers[index];
}


//------------------------------------------------------------------------------


/** 
 * This method performs the forward propagation 
 * by receiving one input from the user and multiplying it layer by layer
 * with each of its weights and returning the result which gets handled
 * outside of the class by the batch controlling function
 * meanwhile all the sums and outputs to perform back propagation 
 * get saved in the Layer class member attributes when calling the feed_forward method
 * 
 * @param input is a moved variable which gets cleaned when function reaches end 
 * @return it returns the result to the function controlling the batch+
 * 
 */
bnu::matrix<double> MultiLayerPerceptron::forward_propagation(bnu::matrix<double>&& input)
{
    bnu::matrix<double> inputs_outputs = input; // temporary variable that changes each iteration
    for (Layer& i_layer : m_layers) {
	i_layer.feed_forward(std::move(inputs_outputs));
	inputs_outputs = i_layer.m_output;
    }
    return inputs_outputs;
}


//------------------------------------------------------------------------------


void MultiLayerPerceptron::back_propagation(bnu::matrix<double>&& target)
{
    unsigned i_layer = m_layers.size() - 1; 
    Layer* c_layer = &m_layers[i_layer]; // for easier reading of code

    // calculate output layer's gradients
    c_layer->m_output = bnu::prod(c_layer->m_output - target,
				  c_layer->m_derivative(c_layer->m_output));
    m_layers[i_layer].m_weights -= ();
}
