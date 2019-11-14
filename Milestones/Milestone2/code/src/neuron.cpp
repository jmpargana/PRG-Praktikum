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
 */
Neuron::Neuron() 
{
    std::function<std::vector<double>(std::vector<double>)> softmax =
    	[](std::vector<double> inpts)
	{
	    std::vector<double> outputs; double sum=0.0;
	    for (auto& val : inpts) sum+=std::exp(val);
	    for (auto& val : inpts) outputs.push_back(val/sum);
	    return outputs;
	};
}


//------------------------------------------------------------------------------


/* 
 * Constructor for square matrix with given size
 * @param second
 * 
 */
Neuron::Neuron(std::function<std::vector<double>(std::vector<double>)> other)
{
    
}


//------------------------------------------------------------------------------


/**
 * Copy constructor
 * 
 * @param other is another instance of the same class
 * 
 */
Neuron::Neuron(Neuron& other) :
    activation_function{other.activation_function}, inputs{other.inputs}  { }


//------------------------------------------------------------------------------


/** 
 * Copy constructor for reference
 * 
 * @param other is another instance of same class
 * 
 */
Neuron::Neuron(Neuron&& other) :
    activation_function{std::move(other.activation_function)},
    inputs{std::move(other.inputs)}  { }


//------------------------------------------------------------------------------


/**
 * Assignment operation
 * 
 * @param lhs is another instance of the same class
 * 
 */
Neuron& Neuron::operator=(const Neuron& lhs)
{
    activation_function = lhs.activation_function;
    inputs = lhs.inputs;
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
    activation_function = std::move(lhs.activation_function);
    inputs = std::move(lhs.inputs);
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
    inputs = values;
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
 * Getter function for inputs attribute that can assign
 * @return vector of inputs and weights
 */
std::vector<std::pair<double, double>>& Neuron::get_inputs()
{
    return this->inputs;
}


//------------------------------------------------------------------------------


/**
 * Getter function for const values only for reading
 * @return vector of inputs and weights
 */
const std::vector<std::pair<double, double>>& Neuron::get_inputs() const
{
    return this->inputs;
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
    double result = 0;
    for (unsigned i=0; i<inpts.size(); ++i){
	result += inpts[i] * this->weights[i];
    }
    return result;
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
