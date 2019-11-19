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
    m_activation_function = [](std::vector<double> input) -> std::vector<double>
    {
     	double sum=0.0; std::vector<double> activated_output(input.size());
        for (double& i_input : input) sum += std::exp(i_input);
        for (double& i_input : input) activated_output.push_back(std::exp(i_input)/sum);
        return activated_output;
    };

    m_derivative_function = [this](std::vector<double> input) -> std::vector<double>
    {
     	std::vector<double> derivated_input(input.size());
	for (unsigned i_input=0; i_input<input.size(); ++i_input)
	    derivated_input[i_input] = m_activation_function(input)[i_input] *
		(1 - m_activation_function(input)[i_input]);
	return derivated_input;
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
 * @param size is the size of input weights to be initialized
 * @param other a function pointer like defined in neuron.hpp
 * 
 */
Neuron::Neuron(unsigned size, FunctionPointer other)
    : m_activation_function{other}
{
    m_derivative_function = [this](std::vector<double> input) -> std::vector<double>
    {
     	std::vector<double> derivated_input(input.size());
	for (unsigned i_input=0; i_input<input.size(); ++i_input)
	    derivated_input[i_input] = m_activation_function(input)[i_input] *
		(1 - m_activation_function(input)[i_input]);
	return derivated_input;
    };

    // instantiate all weights with random value
    std::uniform_real_distribution<double> random(0.0,1.0);
    std::default_random_engine generator;
    m_weights = std::vector<double>(size, random(generator));
}


//------------------------------------------------------------------------------


/**
 * Constructor for a special activation and derivative functionPointer
 * @param size is the size of input weights to be initialized 
 * @param activation is a function pointer for a special activation function
 * @param derivative is a function pointer for a special derivative function of its activation
 * 
 */
Neuron::Neuron(unsigned size, FunctionPointer activation, FunctionPointer derivative)
    : m_activation_function{activation}, m_derivative_function{derivative}
{
    // instantiate all weights with random value
    std::uniform_real_distribution<double> random(0.0,1.0);
    std::default_random_engine generator;
    m_weights = std::vector<double>(size, random(generator));    
}


//------------------------------------------------------------------------------


/** 
 * Subscritor for easy access of the input weights member vector
 * @param index is the vector index to be acessed
 * @return the indexed value
 */
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
 * Setter for output member.
 * this variable contains the output value after the activation function 
 * and is needed for next input and for to calculate the gradient
 * @param output a double value
 * @return void
 * 
 */
void Neuron::set_output(double output)
{
    m_output_val = output;
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


/** 
 * Load the activation function from the function pointer 
 * @param unactivated_outputs is a vector of sums from the weights matrix times input
 * @return returns the activated vector of sums
 */
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
 * Getter for weights
 * works as a pointer, to avoid allocating space everytime a matrix is created
 * for easy calculation
 * @return pointer to m_weights member vector in neuron 
 */
std::vector<double>* Neuron::get_weights()
{
    return &m_weights;
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
