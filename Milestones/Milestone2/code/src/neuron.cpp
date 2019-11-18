/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * neuron.cpp source file with all declarations for neuron class
 *
 */


#include "../include/neuron.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Assigns the default activation function (softmax)
 * @param size is amount of inputs from previous layer
 */
Neuron::Neuron(unsigned size) 
{
    // TODO: not sure about softmax implementation
    m_activation_function = [](std::vector<double> input) -> std::vector<double>
    {
        double sum=0.0; std::vector<double> activated_output;
        for (double& i_input : input) sum += std::exp(i_input);
        for (double& i_input : input) activated_output.push_back(std::exp(i_input)/sum);
        return activated_output;
    };

    // TODO: check indices of input and weight in vector
    m_derivative_function = [](std::vector<double> input) -> std::vector<double>
    {
	// // kronecker delta is one if indices are the same
	// unsigned delta_i_j = (input == this->m_weights[input]) ? 1 : 0;
	// return m_activation_function(input) * (delta_i_j - m_activation_function(input));
    };

    // instantiate all weights with random value
    std::uniform_real_distribution<double> random(0.0,1.0);
    std::default_random_engine generator;
    m_weights = std::vector<double>(size, random(generator));
}


//------------------------------------------------------------------------------


/* 
 * Constructor for a specific activation function
 * only works if given activation function has the same type as softmax or sigmoid
 * @param other a function pointer like defined in neuron.hpp
 * 
 */
Neuron::Neuron(FunctionPointer other)
    : m_activation_function{other} { }


//------------------------------------------------------------------------------


/**
 *
 */
Neuron::Neuron(FunctionPointer activation, FunctionPointer derivative)
    : m_activation_function{activation}, m_derivative_function{derivative} { }


//------------------------------------------------------------------------------


double& Neuron::operator[](int index)
{
    return m_weights[index];
}


//------------------------------------------------------------------------------


/**
 * Setter function for activation lambda function
 * @param other new lambda function 
 * @return void
 * 
 */
void Neuron::set_activation_function(FunctionPointer other)
{
    this->m_activation_function = other;
}


//------------------------------------------------------------------------------


/**
 * Sum function performs the same as accumulate function from the numeric
 * library it iterates over inputs and increments its value * weigth
 * @return result sum of inputs * weigths
 *
 */
double Neuron::calculate_sum(const std::vector<double>& inputs)
{
    return std::inner_product(inputs.begin(), inputs.end(),
			      m_weights.begin(), 0.0);
}


//------------------------------------------------------------------------------


std::vector<double> Neuron::activation(std::vector<double>& unactivated_outputs)
{
    return m_activation_function(unactivated_outputs);
}


//------------------------------------------------------------------------------


void Neuron::calculate_gradients()
{
    // check if neuron belongs to output or hidden layer

    // calculate
    
}


//------------------------------------------------------------------------------


/**
 * Output stream operator overload 
 * 
 * @param os is an instance of the standard output stream class
 * @param lhs is an instance of the Neuron class
 * 
 * @return the same output stream
 * 
 */
std::ostream& operator<<(std::ostream& os, Neuron const& lhs)
{
    
    return os;
}


//------------------------------------------------------------------------------


/** 
 * Input stream operator overload
 * 
 * @param is is an instance of the standard input stream class
 * @param lhs is an instance of the CellularAutomaton class
 * 
 * @return the same input stream
 * 
 */
std::istream& operator>>(std::istream& is, Neuron& lhs)
{

    return is;
}


//------------------------------------------------------------------------------


/**
 * Output file stream operator overload
 * 
 * @param os is an instance of the standard output file stream 
 * @param lhs is an instance of the CellularAutomaton class
 * 
 * @return the same output file stream
 * 
 */
std::ofstream& operator<<(std::ofstream& os, Neuron const& lhs)
{

    return os;
}


//------------------------------------------------------------------------------


/**
 * Input file stream operator overload
 * 
 * @param is is an instance of the standard input file stream
 * @param lhs is an instance of the CellularAutomaton class
 * 
 * @return the same input file stream
 * 
 */
std::ifstream& operator>>(std::ifstream& is, Neuron& lhs)
{

    return is;
}
