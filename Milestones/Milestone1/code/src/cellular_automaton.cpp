/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * Aufgabe1 src file for c) d) and e) containing the cellular automaton class
 *
 */


#include "../include/cellular_automaton.h"
#include "../include/matrix.h"


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton()
    : current{Matrix<bool>(30, 30)}, next{Matrix<bool>(30, 30)}, timer{1} { }
// default constructor with size 30 square matrix


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int size)
    : current{Matrix<bool>(size, size)}, next{Matrix<bool>(size, size)},
      timer{1} { }
// square matrix constructor with a given size


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int rows, const int cols)
    :current{Matrix<bool>(rows, cols)}, next{Matrix<bool>(rows, cols)},
     timer{1} { }
// constructor with given dimensions


//------------------------------------------------------------------------------


CellularAutomaton::CellularAutomaton(const int rows,
				     const int cols,
				     const int timer)
    : current{Matrix<bool>(rows, cols)},
      next{Matrix<bool>(rows, cols)},
      timer{timer} { }
// constructor with all variables given


//------------------------------------------------------------------------------


std::vector<bool> CellularAutomaton::operator[](int index)
{
    return this->current[index];
}


//------------------------------------------------------------------------------


// getter functions
int CellularAutomaton::get_rows() { return this->current.get_row_size(); }
int CellularAutomaton::get_cols() { return this->current.get_col_size(); }


//------------------------------------------------------------------------------


template<typename T>
std::ostream& operator<<(std::ostream& os, CellularAutomaton& ca)
// output file stream operator overload
{
    for (int rol=0; rol<ca.get_rows(); ++rol) {
	for (int col=0; col<ca.get_cols(); ++col) {
	    os << ca[rol][col];
	}
	os << std::endl;
    }
    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::istream& operator>>(std::istream& is, CellularAutomaton& ca)
// input stream operator overload
{
    T temp;			// save input character in this variable
    for (int row; row<ca.get_rows(); ++row) {
	for (int col; col<ca.get_cols(); ++col) {
	    is >> temp;			  // input to variable
	    ca[row][col] = (temp == "*"); // save via ternary
	}
    }
    return is;
}


//------------------------------------------------------------------------------


template<typename T>
std::ofstream& operator<<(std::ofstream& os, const CellularAutomaton& ca)
// output file stream operator overload
{
    
    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::ifstream& operator>>(std::ifstream& is, CellularAutomaton& ca)
// input file stream operator overload
{
    
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
	    // deal with negative numbers
	    if (surr_r < 0) surr_r+=this->get_rows();
	    if (surr_c < 0) surr_r+=this->get_cols();
	    else {		// deal with modulo limits
		surr_r %= this->get_rows();
		surr_c %= this->get_cols();
	    }
	    // increment if living cell was found
	    if (this->current[surr_r][surr_c]) ++total_living_cells;
	}
    }
    this->next[row][col] = (total_living_cells > 3 || total_living_cells < 2);
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
    this->next = Matrix<bool>(this->get_rows(), this->get_cols());
    
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

