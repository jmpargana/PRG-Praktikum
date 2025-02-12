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
using Matrix = std::vector<std::vector<double>*>; // useful for multiplications


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
class Network {
public:
    // constructors
    Network(std::vector<unsigned>&&); // default constructor
    
    Network(const Network&) = default;		// copy constructor
    Network(Network&&) = default;		// move constructor
    Network& operator=(const Network&) = default; // assignment operator
    Network& operator=(Network&&) noexcept = default;

    ~Network() = default;			// destructor

    // member functions
    void forward_propagation(const std::vector<double>&, const std::vector<double>&);
    void back_propagation();
    
    void read_output();
    void train(std::string&);
    void train(std::vector<std::string>&);

    std::vector<double> weights_inputs_product(const std::vector<double>&, unsigned);

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
