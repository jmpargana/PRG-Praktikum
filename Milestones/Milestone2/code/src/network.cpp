/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * network.cpp source file with all declarations for network class
 *
 */


#include "../include/network.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates Layers of Neurons given a certain topology
 * @param topology list of int with size of each layer
 * 
 */
Network::Network(std::vector<unsigned>& topology) 
{
    for (unsigned i_layer_size=0; i_layer_size<topology.size(); ++i_layer_size) {
    	unsigned input_layer_size =
    	    (i_layer_size == 0) ? 1 : topology[i_layer_size - 1];
    	m_layers[i_layer_size] =
    	    std::vector<Neuron>(topology[i_layer_size], Neuron(input_layer_size));
    }
}


//------------------------------------------------------------------------------


void Network::new_feed_forward(const std::vector<double>& inputs)
{
    if (inputs.size() != m_layers[0].size()) // error control for layer size
	throw std::runtime_error("Invalid input size");

    std::vector<double> inputs_outputs = inputs;

    for (unsigned i_layer=0; i_layer<m_layers.size(); ++i_layer) {
	std::vector<double> unactivated_outputs = weights_inputs_product(inputs, i_layer);
	std::vector<double> outputs = m_layers[i_layer][0].activation(unactivated_outputs);

	for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	    m_layers[i_layer][i_neuron].set_output(outputs[i_neuron]);
	}
	inputs_outputs = outputs;
    }
    m_outputs = inputs_outputs;
}


//------------------------------------------------------------------------------


/**
 * This method implments the feed forward function of the network class
 * It takes a vector of inputs, which gets processed by each of the neurons in a layer
 * saves the result to an output vector and iterates all layers with the new input
 * the result gets saved in the m_output member vector of the network class
 * 
 * @param inputs is a vector of input values
 * 
 */
void Network::feed_forward(const std::vector<double>& inputs)
{
    if (inputs.size() != m_layers[0].size()) // error control for layer size
	throw std::runtime_error("Invalid input size");

    // each layer takes a vector of inputs, processes the predict function
    // in each neuron, and for each neuron, saves a double to the output vector
    // which will be used in the next layer as input
    std::vector<double> inputs_outputs = inputs, hidden_outputs;

    for (unsigned i_layer=0; i_layer<m_layers.size(); ++i_layer) {
	// calculate the sum of layer inputs and weights or Z_i to be applied in softmax
	double softmax_sum = sum_of_layer(i_layer, inputs_outputs);
	// initiate vector with next layers' size
	std::vector<double> hidden_outputs(m_layers[i_layer].size());
    	for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	    // first layer takes only one element per input
	    if (i_layer == 0) 
		m_layers[i_layer][i_neuron]
		    .activate(std::vector<double>(1, inputs_outputs[i_neuron]), softmax_sum);
	    else
		// process the input vector and save the result in the output for next layer
		m_layers[i_layer][i_neuron].activate(inputs_outputs, softmax_sum);
	    hidden_outputs.push_back(m_layers[i_layer][i_neuron].get_output_val());
    	}
	// save current output vector as next layers' input
	inputs_outputs = hidden_outputs;
    }
    m_outputs = inputs_outputs;	// save last output vector as result from neural network
}


//------------------------------------------------------------------------------


void Network::back_propagation(const std::vector<double>& goal_values)
{
    if (goal_values.size() != m_outputs.size()) // error control
	throw std::runtime_error("Output size doesn't match goal vector");
    
    // calculate output layer gradients
    std::vector<double> output_errors(goal_values.size());
    for (unsigned i_output=0; i_output<m_outputs.size(); ++i_output) {
	// error = (expected - output) * derivative(output) where derivative is defined in neuron
	output_errors.push_back((goal_values[i_output] - goal_values[i_output]) *
				m_layers[m_layers.size() - 1][i_output]
				.derivative(m_outputs[i_output]));
    }

    // Calculate gradients on hidden layers
    
    

    // update all the weights across the network
    
}


//------------------------------------------------------------------------------


double Network::sum_of_layer(unsigned i_layer, std::vector<double>& inputs)
{
    double sum = 0.0;
    for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	sum += std::exp(m_layers[i_layer][i_neuron].calculate_sum(inputs));
    }
    return sum;
}


//------------------------------------------------------------------------------


void Network::read_output()
{
    for (Neuron& i_neuron : m_layers[m_layers.size() - 1]) {
	std::cout << i_neuron << std::endl;
    }
}


//------------------------------------------------------------------------------


/**
 * This method opens an input file stream with a file name
 * and inputs the buffer to the instance of the class
 * what will read an input vector from the file and initiate the
 * feed forward function
 * @param file_name a string containing a file name
 *
 */
void Network::train(std::string& file_name)
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("File wasn't found");

    ist >> *this;		// input from file to instance
}


//------------------------------------------------------------------------------


/**
 * This method deals with a vector of strings
 * it calls the same method for each of the strings in the vector
 * @param batches contains multiple file names
 *
 */
void Network::train(std::vector<std::string>& batches)
{
    for (std::string& i_file_name : batches) {
	train(i_file_name);
    }
}


//------------------------------------------------------------------------------


/**
 * This method runs a matrix multiplication between all the weights in a layer
 * times the inputs in a NxM * N = M format. The resulting vector will be 
 * activated with the respective activation function in the given layer
 * 
 * @param inputs is a reference to the inputs in the layer
 * @param i_layer is the index of the current layer to be calculated
 * @return unactivated_outputs a vector of double with the matrix results 
 *
 */
std::vector<double> Network::weights_inputs_product(const std::vector<double>& inputs,
						    unsigned i_layer)
{
    Matrix weights; std::vector<double> unactivated_outputs; // containers to hold values

    // fill the weights matrix with the respenctive values
    for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	weights.push_back(m_layers[i_layer][i_neuron].get_weights());
    }

    // run inner product for each row * input vector and save in the output one
    for (unsigned i_neuron=0; i_neuron<weights.size(); ++i_neuron) {
	unactivated_outputs.push_back(std::inner_product(weights[i_neuron].begin(),
							 weights[i_neuron].end(),
							 inputs.begin(), 0.0));
    }
    return unactivated_outputs;	// return to be saved in a new variable
}


//------------------------------------------------------------------------------


/**
 * Operator[] overload for indexing each layer in network
 * @param i_layer contains the layer's index
 */
Layer& Network::operator[](unsigned i_layer)
{
    return m_layers[i_layer];
}


//------------------------------------------------------------------------------


/**
 * Output stream operator overload 
 * 
 * @param os is an instance of the standard output stream class
 * @param lhs is an instance of the Network class
 * 
 * @return the same output stream
 * 
 */
std::ostream& operator<<(std::ostream& os, Network const& lhs)
{
    
    return os;
}


//------------------------------------------------------------------------------


/** 
 * Input stream operator overload
 * it reads the input vector the the file and runs the feed_forward
 * method from the network class
 * 
 * @param is is an instance of the standard input stream class
 * @param lhs is an instance of the Network class
 * 
 * @return the same input stream
 * 
 */
std::istream& operator>>(std::istream& is, Network& lhs)
{
    // read inputs from file    
    std::vector<double> inputs;
    // is >> inputs;
    
    lhs.feed_forward(inputs);
    
    return is;
}


//------------------------------------------------------------------------------


/**
 * Output file stream operator overload
 * 
 * @param os is an instance of the standard output file stream 
 * @param lhs is an instance of the Network class
 * 
 * @return the same output file stream
 * 
 */
std::ofstream& operator<<(std::ofstream& os, Network const& lhs)
{

    return os;
}


//------------------------------------------------------------------------------


/**
 * Input file stream operator overload
 * 
 * @param is is an instance of the standard input file stream
 * @param lhs is an instance of the Network class
 * 
 * @return the same input file stream
 * 
 */
std::ifstream& operator>>(std::ifstream& is, Network& lhs)
{

    return is;
}
