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
 * first layer doesn't need to be instantiated since it contains only the inputs
 * @param topology list of int with size of each layer
 * 
 */
Network::Network(std::vector<unsigned>&& topology) // Network network() 
{
    for (unsigned i_layer_size=1; i_layer_size<topology.size(); ++i_layer_size) {
    	m_layers[i_layer_size] =
    	    std::vector<Neuron>(topology[i_layer_size], Neuron(topology[i_layer_size - 1]));
    }
}


//------------------------------------------------------------------------------


/**
 * This method implements the feed forward function of the network class
 * It takes a vector of inputs, which gets multiplied with a matrix of weights
 * by calling the weights_inputs_product member function
 * it then processes the whole vector via activation function, since the
 * whole layer needs to share the same one
 * each of the activated double is saved in the respective neuron's output member
 * The result gets saved in the new input vector, and all iterations are 
 * performed until less layer is reached.
 * It finally gets stored in the network's m_outputs member
 *
 * @param inputs is a vector of inputs from the starting input layer
 *
 */
void Network::forward_propagation(const std::vector<double>& inputs)
{
    if (inputs.size() != m_layers[0].size()) // error control for layer size
	throw std::runtime_error("Invalid input size");

    std::vector<double> inputs_outputs = inputs; // variable to perform loop

    for (unsigned i_layer=0; i_layer<m_layers.size(); ++i_layer) {
	// vectors are moove from functions to save allocating space
	std::vector<double> unactivated_outputs{weights_inputs_product(inputs, i_layer)};
	std::vector<double> outputs{m_layers[i_layer][0].activation(unactivated_outputs)};

	for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	    m_layers[i_layer][i_neuron].set_output(outputs[i_neuron]);
	}
	inputs_outputs = outputs;
    }
    m_outputs = inputs_outputs;
}


//------------------------------------------------------------------------------


void Network::back_propagation(const std::vector<double>& goal_values)
{
    if (goal_values.size() != m_outputs.size()) // error control
	throw std::runtime_error("Output size doesn't match goal vector");
    
    // calculate output layer gradients

    
    // Calculate gradients on hidden layers
    
    

    // update all the weights across the network
    
}


//------------------------------------------------------------------------------


/**
 * Getter function for last layer
 * used when prediction is performed
 */
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
    Matrix weights(m_layers[i_layer].size()); // containers to hold values
    std::vector<double> unactivated_outputs(m_layers[i_layer].size()); 

    // fill the weights matrix with the respenctive values
    for (unsigned i_neuron=0; i_neuron<m_layers[i_layer].size(); ++i_neuron) {
	weights.push_back(m_layers[i_layer][i_neuron].get_weights());
    }

    // run inner product for each row * input vector and save in the output one
    for (unsigned i_neuron=0; i_neuron<weights.size(); ++i_neuron) {
	unactivated_outputs.push_back(std::inner_product(weights[i_neuron]->begin(),
							 weights[i_neuron]->end(),
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
    
    // lhs.feed_forward(inputs);
    
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
