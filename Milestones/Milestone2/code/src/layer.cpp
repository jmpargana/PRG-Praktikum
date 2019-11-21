/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * layer.cpp source file with all declarations for Layer class
 *
 */


#include "../include/layer.hpp"


//------------------------------------------------------------------------------


std::uniform_real_distribution<double> ran(0.0,1.0);
std::default_random_engine gen;


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates Layers of Neurons given a certain topology
 * first layer doesn't need to be instantiated since it contains only the inputs
 * @param topology list of int with size of each layer
 * 
 */
Layer::Layer(unsigned s_current_layer, unsigned s_prev_layer)
{
    m_activation = [](bnu::matrix<double> input) -> bnu::matrix<double>
	{
	 double sum=0.0; bnu::matrix<double> activated(input.size1(), input.size2());
	 for (auto start=input.begin1(); start!=input.end1(); ++start)
	     sum += std::exp(*start);
	 for (unsigned i_row=0; i_row<input.size1(); ++i_row)
	     activated(i_row, 1) = std::exp(input(i_row, 1)) / sum;
	 return activated;
	};

    m_derivative = [this](bnu::matrix<double> input) -> bnu::matrix<double>
	{
	 bnu::matrix<double> derivated(input.size1(), input.size2());
	 for (unsigned i_row=0; i_row<input.size1(); ++i_row) 
	     derivated(i_row, 1) = m_activation(input)(i_row, 1) * (1 - m_activation(input)(i_row, 1));
	 return derivated;
	};
    
    m_sum_z(s_current_layer, 1); m_output(s_current_layer, 1); // one dimensional matrices
    m_weights(s_current_layer, s_prev_layer);		   // matrix of weights NxN-1

    for (unsigned i_row=0; i_row<s_current_layer; ++i_row) // initialize matrix
	for (unsigned i_col=0; i_col<s_prev_layer; ++i_col) // with random weights
	    m_weights(i_row, i_col) = ran(gen);		  // from 0 to 1
}


//------------------------------------------------------------------------------


/**
 * Full constructor with all give parameters
 * @param s_current_layer size of current layer
 * @param s_prev_layer size of previous layer
 * @param activation lambda of activation function
 * @param derivative lambda of derivative of activation function
 * 
 */
Layer::Layer(unsigned s_current_layer,
	     unsigned s_prev_layer,
	     FunctionPointer activation,
	     FunctionPointer derivative)
    : m_activation{activation},
      m_derivative{derivative}
{
    m_output(s_current_layer, 1); 			   // one dimensional matrices
    m_sum_z(s_current_layer, 1);
    m_weights(s_current_layer, s_prev_layer);		   // matrix of weights NxN-1

    for (unsigned i_row=0; i_row<s_current_layer; ++i_row) // initialize matrix
	for (unsigned i_col=0; i_col<s_prev_layer; ++i_col)// with random weights
	    m_weights(i_row, i_col) = ran(gen);		   // from 0 to 1    
}


//------------------------------------------------------------------------------


/**
 * Feed forward multiplies the weights matrix with the input vector and 
 * assigns for each of the "neuron" its sum which then gets activated
 * by the member variable activation function
 * 
 * @param input is a vector of the same size as the row of weights matrix
 * 
 */
void Layer::feed_forward(const bnu::matrix<double>& input)
{
    m_sum_z = bnu::prod(m_weights, input);
    m_output = m_activation(m_sum_z);
}
