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
    m_activation_function = [=](double input) -> double
    {
	return std::exp(input) / softmax_sum;
    };

    // TODO: check indices of input and weight in vector
    m_derivative_function = [this](double input) -> double
    {
	// kronecker delta is one if indices are the same
	unsigned delta_i_j = (input == this->m_weights[input]) ? 1 : 0;
	return m_activation_function(input) * (delta_i_j - m_activation_function(input));
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
 * Assign a value of inputs with their correspondent weights to the
 * inputs variable of the Neuron
 * 
 * @param values contains vector of pair of doubles (inputs and weights)
 * @return void
 * 
 */
Neuron& Neuron::set_inputs(std::vector<std::pair<double, double>>& values)
{
    // inputs = values;
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Setter function for activation lambda function
 *  
 * @param first
 * @param second
 * @param other new lambda function
 * 
 * @return void
 * 
 */
Neuron& Neuron::set_activation_function(std::function<void(int first, int second)> other)
{
    // this->activation_function = other;
    return *this;
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


void Neuron::activate(const std::vector<double>& inputs, double softmax_sum)
{
    double sum = calculate_sum(inputs);
    m_output_val = m_activation_function(sum);
}


//------------------------------------------------------------------------------


void Neuron::derive(std::vector<double>& inputs)
{
    // m_derivative_function(inputs);
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
