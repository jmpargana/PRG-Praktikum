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


auto rangen = std::bind(std::uniform_real_distribution<>(0.0, 1.0), std::default_random_engine());


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates Layers of Neurons given a certain topology
 * first layer doesn't need to be instantiated since it contains only the inputs
 * @param topology list of int with size of each layer
 * 
 */
Layer::Layer(unsigned s_current_layer, unsigned s_prev_layer)
    : m_output{s_current_layer, 1},
      m_weights{s_current_layer, s_prev_layer},
      m_sum_z{s_current_layer, 1}
{
    m_activation = [](Layer*, const bnu::matrix<double>& input) -> bnu::matrix<double>
    	{
		 // https://stackoverflow.com/a/49212689
		 // fix overflow with e^input in softmax
		 double max = *std::max_element(input.begin1(), input.end1());
		 bnu::matrix<double> isoft(input.size1(), input.size2());
		 for (int i = 0; i < input.size1(); ++i) {
			 for (int j = 0; j < input.size2(); ++j) {
				 isoft(i, j) = input(i, j) - max;
			 }
		 }

    	 double sum=0.0; bnu::matrix<double> activated(input.size1(), input.size2());
    	 for (auto start=isoft.begin1(); start!=isoft.end1(); ++start)
    	     sum += std::exp(*start);
    	 for (unsigned i_row=0; i_row<isoft.size1(); ++i_row)
    	     activated(i_row, 0) = std::exp(isoft(i_row, 0)) / sum;
    	 return activated;
    	};

    m_derivative = [](Layer* l, const bnu::matrix<double>& input) -> bnu::matrix<double>
    	{
    	 bnu::matrix<double> derivated(input.size1(), input.size2());
    	 for (unsigned i_row=0; i_row<input.size1(); ++i_row) {
			 auto activated = l->m_activation(l, input);
    	     derivated(i_row, 0) = activated(i_row, 0) * (1 - activated(i_row, 0));
		 }
    	 return derivated;
    	};

    for (unsigned i_row=0; i_row<s_current_layer; ++i_row) // initialize matrix
    	for (unsigned i_col=0; i_col<s_prev_layer; ++i_col) // with random weights
    	    m_weights(i_row, i_col) = rangen();		  // from 0 to 1
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
      m_derivative{derivative},
      m_output{s_current_layer, 1},
      m_weights{s_current_layer, s_prev_layer},
      m_sum_z{s_current_layer, 1}
{
    for (unsigned i_row=0; i_row<s_current_layer; ++i_row) // initialize matrix
	for (unsigned i_col=0; i_col<s_prev_layer; ++i_col)// with random weights
	    m_weights(i_row, i_col) = rangen();		   // from 0 to 1    
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
    m_sum_z = bnu::prod(bnu::trans(m_weights), input);
    m_output = m_activation(this, m_sum_z);
}


//------------------------------------------------------------------------------


/**
 * multiply the target vector with this layer's sum's derivative
 * and store the gradients in the output matrix, so it can be 
 * used recursively and to update the weights
 * target contains the delta for the output layer and a multiplication
 * of the output layer with the weights matrix for the hidden layers
 * 
 * @param target is a one dimensional matrix
 * 
 */
void Layer::calculate_gradients(const bnu::matrix<double>& target)
{
    auto derivative = m_derivative(this, m_output);
    m_output = bnu::element_prod(target, derivative);
}


//------------------------------------------------------------------------------


/**
 * Update the weights matrix by substracting the "correct"
 * weights which can be calculated by multiplying the
 * output with the transposed input
 *
 * @param prev_output previous layer's output/gradients
 * 
 */
void Layer::update_weights(const bnu::matrix<double>& prev_output)
{
    m_weights -= bnu::prod(prev_output, bnu::trans(m_output));
}
