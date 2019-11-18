/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * network.hpp header file with declaration of network class
 * 
 */


#ifndef NETWORK_HPP
#define NETWORK_HPP


#include "./neuron.hpp"


//------------------------------------------------------------------------------


using Layer = std::vector<Neuron>; // very useful alias for class definition


/**
 * This class contains a the definition of a Perceptron
 * @see perceptron
 * 
 * @param activation_function is a pointer to a function that can be changed
 * @param inputs contains a list of all inputs which can be variable with their weights
 *
 */
class Network {
public:
    // constructors
    Network(std::vector<unsigned>&); // default constructor
    
    Network(Network&) = default;		// copy constructor
    Network(Network&&) = default;		// move constructor
    Network& operator=(const Network&) = default; // assignment operator
    Network& operator=(Network&&) noexcept = default;

    ~Network() = default;			// destructor

    // member functions
    void feed_forward(const std::vector<double>&);
    void back_propagation(const std::vector<double>&);
    double sum_of_layer(unsigned, std::vector<double>&);
    
    void read_output();
    void train(std::string&);
    void train(std::vector<std::string>&);

    // getter
    Layer& operator[](unsigned);
    
    
    
private:
    std::vector<Layer> m_layers;
    std::vector<double> m_outputs, m_errors;
    
};


//------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream&, Network const&); // output stream
std::istream& operator>>(std::istream&, Network&); // input stream

std::ofstream& operator<<(std::ofstream&, Network const&); // output file stream
std::ifstream& operator>>(std::ifstream&, Network&); // input file stream


#endif
