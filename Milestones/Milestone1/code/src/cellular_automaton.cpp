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


CellularAutomaton::CellularAutomaton()
    : current{Matrix(30, 30)}, next{Matrix(30, 30)}, timer{1} { }
// default constructor with size 30 square matrix


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int size)
    : current{Matrix(size, size)}, next{Matrix(size, size)},
      timer{1} { }
// square matrix constructor with a given size


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int rows, const int cols)
    :current{Matrix(rows, cols)}, next{Matrix(rows, cols)},
     timer{1} { }
// constructor with given dimensions


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int rows,
				     const int cols,
				     const int timer)
    : current{Matrix(rows, cols)},
      next{Matrix(rows, cols)},
      timer{timer} { }
// constructor with all variables given


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(CellularAutomaton& ca)
    : current{ca.current}, next{ca.next}, timer{ca.timer} { }
// copy constructor


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(CellularAutomaton&& ca)
    : current{std::move(ca.current)}, next{std::move(ca.next)}, timer{std::move(ca.timer)} { }


//------------------------------------------------------------------------------


CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& ca)
// assignment operation overload
{
    current = ca.current;
    next = ca.next;
    timer = ca.timer;
    return *this;
}


//------------------------------------------------------------------------------


CellularAutomaton& CellularAutomaton::operator=(CellularAutomaton&& ca) noexcept
// move operation overload assignment
{
    current = std::move(ca.current);
    next = std::move(ca.next);
    timer = std::move(ca.timer);
    return *this;
}


//------------------------------------------------------------------------------


std::vector<bool>& CellularAutomaton::operator[](int index)
// subscript operator for assinment
{
    return this->current[index];
}


//------------------------------------------------------------------------------


const std::vector<bool>& CellularAutomaton::operator[](int index) const
// subscript operation overload for const reading
{
    return this->current[index];
}


//------------------------------------------------------------------------------


// getter functions
int CellularAutomaton::get_rows() const { return this->current.get_row_size(); }
int CellularAutomaton::get_cols() const { return this->current.get_col_size(); }


//------------------------------------------------------------------------------


Matrix CellularAutomaton::get_matrix() { return this->current; }


//------------------------------------------------------------------------------


std::ostream& operator<<(std::ostream& os, CellularAutomaton const& ca)
// output file stream operator overload
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


std::istream& operator>>(std::istream& is, CellularAutomaton& ca)
// input stream operator overload
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


// std::ofstream& operator<<(std::ofstream& os, CellularAutomaton& ca)
// // output file stream operator overload
// {
//     char temp;
//     os << ca.get_rows() << '\n' << ca.get_cols() << '\n'; // output dimensions of cellular automaton

//     for (int row=0; row<ca.get_rows(); ++row) {
// 	for (int col=0; col<ca.get_cols(); ++col) {
// 	    temp = (ca[row][col]) ? '*' : 'o';
// 	    os << temp;
// 	}
// 	os << '\n';
//     }
//     return os;
// }


//------------------------------------------------------------------------------


std::ifstream& operator>>(std::ifstream& is, CellularAutomaton& ca)
// input file stream operator overload
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


void CellularAutomaton::update_cell(int row, int col)
// update next cell state in "next" matrix
{
    int total_living_cells = 0;
    // surr_r stands for surrounding row and surr_c for column
    for (int surr_r=row-1; surr_r<row+2; ++surr_r) {
	for (int surr_c=col-1; surr_c<col+2; ++surr_c) {
	    // ignore counting current cell
	    if (surr_r==row && surr_r==surr_c) continue;
	    
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


CellularAutomaton& CellularAutomaton::operator++()
// update cell in for next phase
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


CellularAutomaton& CellularAutomaton::operator+=(int phases)
// update n or "physes" steps
{
    if (phases <= 0) return *this; // avoid invalid input
    for (;phases; phases--) {
	++(*this);
    }
    return *this;
}

