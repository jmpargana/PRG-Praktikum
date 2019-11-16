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
    m_activation_function = [this](double input) -> double
    {
	double sum = this->sum(this->m_weights);
	return std::exp(input) / sum;
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


/**
 * Copy constructor
 * 
 * @param other is another instance of the same class
 * 
 */
Neuron::Neuron(Neuron& other) :
    m_activation_function{other.m_activation_function}, m_weights{other.m_weights} { }


//------------------------------------------------------------------------------


/** 
 * Copy constructor for reference
 * 
 * @param other is another instance of same class
 * 
 */
Neuron::Neuron(Neuron&& other) :
    m_activation_function{std::move(other.m_activation_function)},
    m_weights{std::move(other.m_weights)}  { }


//------------------------------------------------------------------------------


/**
 * Assignment operation
 * 
 * @param lhs is another instance of the same class
 * 
 */
Neuron& Neuron::operator=(const Neuron& lhs)
{
    m_activation_function = lhs.m_activation_function;
    m_weights = lhs.m_weights;
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Assignment operation with reference
 * 
 * @param lhs is another instance of the same class
 * 
 */
Neuron& Neuron::operator=(Neuron&& lhs) noexcept
{
    m_activation_function = std::move(lhs.m_activation_function);
    m_weights = std::move(lhs.m_weights);
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Default destructor
 * doesn't need any special instructions, since pointer to lambda function 
 * and vector already have their default destructors to be called
 * 
 */
Neuron::~Neuron() { }


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
double Neuron::sum(const std::vector<double>& inpts)
{
    return std::inner_product(inpts.begin(), inpts.end(),
			      m_weights.begin(), 0.0);
}


//------------------------------------------------------------------------------


void Neuron::activate(const std::vector<double>& inputs)
{
    std::vector<double> inputs_with_weights;
    for (unsigned i_input=0; i_input<inputs.size(); ++i_input) {
	inputs_with_weights[i_input] = inputs[i_input] * m_weights[i_input];
    }
    // m_activation_function(inputs_with_weights);
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
