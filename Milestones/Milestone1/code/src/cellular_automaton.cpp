/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * Aufgabe1 src file for c) d) and e) containing the cellular automaton class
 *
 */


#include "../include/cellular_automaton.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * takes no arguments and initiates two square matrices with size 30
 */
CellularAutomaton::CellularAutomaton()
    : current{Matrix(30, 30)}, next{Matrix(30, 30)}, timer{1} { }


//------------------------------------------------------------------------------


/* 
 * Constructor for square matrix with given size
 * 
 * @param size is number of rows and columns
 */
CellularAutomaton::CellularAutomaton(const int size)
    : current{Matrix(size, size)}, next{Matrix(size, size)},
      timer{1} { }


//------------------------------------------------------------------------------


/*
 * Contructor for any matrix with given sizes
 * 
 * @param rows is number of rows
 * @param cols is number of columns
 * 
 */
CellularAutomaton::CellularAutomaton(const int rows, const int cols)
    :current{Matrix(rows, cols)}, next{Matrix(rows, cols)},
     timer{1} { }


//------------------------------------------------------------------------------


/**
 * Constructor with all given values
 * 
 * @param rows is number of rows
 * @param cols is number of cols
 * @param timer is value in seconds for timer 
 *
 */
CellularAutomaton::CellularAutomaton(const int rows,
				     const int cols,
				     const int timer)
    : current{Matrix(rows, cols)},
      next{Matrix(rows, cols)},
      timer{timer} { }


//------------------------------------------------------------------------------


/**
 * Copy constructor
 * 
 * @param ca is another instance of the same class
 * 
 */
CellularAutomaton::CellularAutomaton(CellularAutomaton& ca)
    : current{ca.current}, next{ca.next}, timer{ca.timer} { }


//------------------------------------------------------------------------------


/** 
 * Copy constructor for reference
 * 
 * @param ca is another instance of same class
 * 
 */
CellularAutomaton::CellularAutomaton(CellularAutomaton&& ca)
    : current{std::move(ca.current)}, next{std::move(ca.next)}, timer{std::move(ca.timer)} { }


//------------------------------------------------------------------------------


/**
 * Assignment operation
 * 
 * @param ca is another instance of the same class
 * 
 */
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& ca)
{
    current = ca.current;
    next = ca.next;
    timer = ca.timer;
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Assignment operation with reference
 * 
 * @param ca is another instance of the same class
 * 
 */
CellularAutomaton& CellularAutomaton::operator=(CellularAutomaton&& ca) noexcept
{
    current = std::move(ca.current);
    next = std::move(ca.next);
    timer = std::move(ca.timer);
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Subscript operation overload
 * 
 * @param index is index of rows in current matrix
 * 
 * @return vector of bools which isthe whole row
 *
 */
std::vector<bool>& CellularAutomaton::operator[](int index)
{
    return this->current[index];
}


//------------------------------------------------------------------------------


/**
 * Subscript operation overload for const reading
 * 
 * @param index is index of rows in current matrix
 * 
 * @return vector of bools which is the whole row
 * 
 */
const std::vector<bool>& CellularAutomaton::operator[](int index) const
{
    return this->current[index];
}


//------------------------------------------------------------------------------


// getter functions
int CellularAutomaton::get_rows() const { return this->current.get_row_size(); }
int CellularAutomaton::get_cols() const { return this->current.get_col_size(); }


//------------------------------------------------------------------------------


/**
 * Getter function to output the current matrix
 * 
 * @return matrix of bools
 * 
 */
Matrix CellularAutomaton::get_matrix() { return this->current; }


//------------------------------------------------------------------------------


/**
 * Output stream operator overload 
 * 
 * @param os is an instance of the standard output stream class
 * @param ca is an instance of the CellularAutomaton class
 * 
 * @return the same output stream
 * 
 */
std::ostream& operator<<(std::ostream& os, CellularAutomaton const& ca)
{
    char temp;			// save result from boolean
    for (int row=0; row<ca.get_rows(); ++row) {
    	for (int col=0; col<ca.get_cols(); ++col) {
    	    temp = (ca[row][col]) ? '*' : 'o';
    	    os << temp;
    	}
    	os << '\n';
    }
    return os;
}


//------------------------------------------------------------------------------


/** 
 * Input stream operator overload
 * 
 * @param is is an instance of the standard input stream class
 * @param ca is an instance of the CellularAutomaton class
 * 
 * @return the same input stream
 * 
 */
std::istream& operator>>(std::istream& is, CellularAutomaton& ca)
{
    char temp;			// save input character in this variable
    for (int row=0; row<ca.get_rows(); ++row) {
	for (int col=0; col<ca.get_cols(); ++col) {
	    is >> temp;			  // input to variable
	    ca[row][col] = (temp == '*'); // save via ternary
	}
    }
    return is;
}


//------------------------------------------------------------------------------


/**
 * Setter function for timer
 * 
 * @param new_timer integer value to be set
 * 
 * @return void
 * 
 */
void CellularAutomaton::set_timer(int new_timer)
{
    this->timer = new_timer;
}


//------------------------------------------------------------------------------


/**
 * Output file stream operator overload
 * 
 * @param os is an instance of the standard output file stream 
 * @param ca is an instance of the CellularAutomaton class
 * 
 * @return the same output file stream
 * 
 */
std::ofstream& operator<<(std::ofstream& os, CellularAutomaton const& ca)
{
    std::string temp;
    os << std::to_string(ca.get_rows()) << std::endl
       << std::to_string(ca.get_cols()) << std::endl; // output dimensions of cellular automaton

    for (int row=0; row<ca.get_rows(); ++row) {
	for (int col=0; col<ca.get_cols(); ++col) {
	    temp = (ca[row][col]) ? "*" : "o";
	    os << temp;
	}
	os << std::endl;
    }
    return os;
}


//------------------------------------------------------------------------------


/**
 * Input file stream operator overload
 * 
 * @param is is an instance of the standard input file stream
 * @param ca is an instance of the CellularAutomaton class
 * 
 * @return the same input file stream
 * 
 */
std::ifstream& operator>>(std::ifstream& is, CellularAutomaton& ca)
{
    unsigned rows, cols;	// integer values to change size of cellular automaton
    is >> rows >> cols;		// read first two lines into variables
    char temp_variable;

    CellularAutomaton temp(rows, cols);

    for (unsigned row=0; row<rows; ++row) {
    	for (unsigned col=0; col<cols; ++col) {
    	    is >> temp_variable;
    	    temp[row][col] = (temp_variable == '*');
    	}
    }
    ca = temp;    		// replace cellular automaton with new one
    return is;
}


//------------------------------------------------------------------------------


/**
 * This function iterates over the surrounding 9 cells
 * ignores the center one and calculates the amount of 
 * living cells, saving the updated value in the next 
 * matrix by indexing
 * 
 * @param row is integer for subscripting
 * @param col is integer for subscripting the subscription
 * 
 * @return void
 * 
 */
void CellularAutomaton::update_cell(int row, int col)
{
    int total_living_cells = 0;
    // surr_r stands for surrounding row and surr_c for column
    for (int surr_r=row-1; surr_r<row+2; ++surr_r) {
	for (int surr_c=col-1; surr_c<col+2; ++surr_c) {
	    // ignore counting current cell
	    if (surr_r==row && surr_c==col) continue;
	    
	    // deal with negative numbers and modulo
	    // increment if living cell was found
	    if (this->current
		[(surr_r + this->get_rows()) % this->get_rows()]
		[(surr_c + this->get_cols()) % this->get_cols()])
		++total_living_cells;
	}
    }
    // more than 3 or less than 2 dies in next life
    // 2 neighbours maintains the current status and with 3 creates life
    this->next[row][col] = (total_living_cells <= 3 && total_living_cells >= 2) ?
	(total_living_cells == 2) ? this->current[row][col] : true : false;
}


//------------------------------------------------------------------------------


/**
 * Incrementation operator overload
 * iterates over the whole current matrix, calculates each of the cells
 * value in next life by calling update_cell, updates the matrices
 * and sleeps for timer amount of time
 *
 * @return reference to same class instance
 * 
 */
CellularAutomaton& CellularAutomaton::operator++()
{
    for (int row=0; row<this->get_rows(); ++row) {
	for (int col=0; col<this->get_cols(); ++col) {
	    // check cells surrounding it in modulo "size"
	    this->update_cell(row, col);
	}
    }
    this->current = this->next;	// update matrices
    this->next = Matrix(this->get_rows(), this->get_cols());
    
    // set timeout function for visualization
    std::this_thread::sleep_for(std::chrono::milliseconds(this->timer));
    return *this;
}


//------------------------------------------------------------------------------


/**
 * Increment n times operator overload
 * Run the ++ incrementation n times
 * 
 * @param phases is the number of incrementations
 * 
 * @return reference to same instance
 * 
 */
CellularAutomaton& CellularAutomaton::operator+=(int phases)
{
    if (phases <= 0) return *this; // avoid invalid input
    for (;phases; phases--) {
	++(*this);
    }
    return *this;
}
