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


typedef std::vector<Neuron> Layer;


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
    
    Network(Network&);		// copy constructor
    Network(Network&&);		// move constructor
    Network& operator=(const Network&); // assignment operator
    Network& operator=(Network&&) noexcept;

    ~Network();			// destructor

    // member functions
    void feed_forward(const std::vector<double>&);
    void back_propagation(const std::vector<double>&);
    void read_output();
    void train(std::string&);
    void train(std::vector<std::string>&);

    // getter
    Layer& operator[](unsigned);
    
    
    
private:
    std::vector<Layer> m_layers;
    
};


//------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream&, Network const&); // output stream
std::istream& operator>>(std::istream&, Network&); // input stream

std::ofstream& operator<<(std::ofstream&, Network const&); // output file stream
std::ifstream& operator>>(std::ifstream&, Network&); // input file stream


#endif
