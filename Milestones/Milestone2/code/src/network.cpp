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
    // // for (unsigned i_layer_size=0; i_layer_size<topology.size(); ++i_layer_size) {
    // m_layers[i_layer_size] = std::vector<Neuron>(topology[i_layer_size]);
    // // }
}


//------------------------------------------------------------------------------


/**
 * Copy constructor
 * 
 * @param other is another instance of the same class
 * 
 */
Network::Network(Network& other) : m_layers{other.m_layers} { }


//------------------------------------------------------------------------------


/** 
 * Copy constructor for reference
 * 
 * @param other is another instance of same class
 * 
 */
Network::Network(Network&& other) : m_layers{std::move(other.m_layers)} { }


//------------------------------------------------------------------------------


/**
 * Assignment operation
 * 
 * @param lhs is another instance of the same class
 * 
 */
Network& Network::operator=(const Network& lhs)
{
    m_layers = lhs.m_layers;
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Assignment operation with reference
 * 
 * @param lhs is another instance of the same class
 * 
 */
Network& Network::operator=(Network&& lhs) noexcept
{
    m_layers = std::move(lhs.m_layers);
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Default destructor
 * doesn't need any special instructions, since pointer to lambda function 
 * and vector already have their default destructors to be called
 * 
 */
Network::~Network() { }


//------------------------------------------------------------------------------


void Network::feed_forward(const std::vector<double>& inputs)
{
    
}


//------------------------------------------------------------------------------


void Network::back_propagation(const std::vector<double>& goal_values)
{
    
}


//------------------------------------------------------------------------------


void Network::read_output()
{
    for (Neuron& i_neuron : m_layers[m_layers.size() - 1]) {
	std::cout << i_neuron << std::endl;
    }
}


//------------------------------------------------------------------------------


void Network::train(std::string& file_name)
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("File wasn't found");
    
}


//------------------------------------------------------------------------------


void Network::train(std::vector<std::string>& batches)
{
    for (std::string& i_file_name : batches) {
	train(i_file_name);
    }
}


//------------------------------------------------------------------------------


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
 * 
 * @param is is an instance of the standard input stream class
 * @param lhs is an instance of the Network class
 * 
 * @return the same input stream
 * 
 */
std::istream& operator>>(std::istream& is, Network& lhs)
{

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
