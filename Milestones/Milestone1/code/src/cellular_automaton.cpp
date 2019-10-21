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


//------------------------------------------------------------------------------


template<typename T>
std::ostream& operator<<(std::ostream& os, const CellularAutomaton<T>& ca)
{
    for (unsigned int rol=0; rol<ca.get_size(); ++rol) {
	for (unsigned int col=0; col<ca.get_size(); ++col) {
	    os << ca[rol][col];
	}
	os << std::endl;
    }
    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::istream& operator>>(std::istream& is, CellularAutomaton<T>& ca)
{
    T temp;			// save input character in this variable
    for (int row; row<ca.get_size(); ++row) {
	for (int col; col<ca.get_size(); ++col) {
	    is >> temp;			  // input to variable
	    ca[row][col] = (temp == "*"); // save via ternary
	}
    }
    return is;
}


//------------------------------------------------------------------------------


template<typename T>
std::ofstream& operator<<(std::ofstream& os, const CellularAutomaton<T>& ca)
{
    
    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::ifstream& operator>>(std::ifstream& is, CellularAutomaton<T>& ca)
{
    
    return is;
}


//------------------------------------------------------------------------------


template<typename T>
void CellularAutomaton<T>::update_cell(int row, int col)
// update next cell state in "next" matrix
{
    int total_living_cells = 0;
    // surr_r stands for surrounding row and surr_c for column
    for (unsigned int surr_r=row-1; surr_r<row+2; ++surr_r) {
	for (unsigned int surr_c=col-1; surr_c<col+2; ++surr_c) {	    
	    // deal with negative numbers
	    if (surr_r < 0) surr_r+=this->get_size();
	    if (surr_c < 0) surr_r+=this->get_size();
	    else {		// deal with modulo limits
		surr_r %= this->get_size();
		surr_c %= this->get_size();
	    }
	    // increment if living cell was found
	    if (this->current[surr_r][surr_c]) ++total_living_cells;
	}
    }
    this->next[row][col] = (total_living_cells > 3 || total_living_cells < 2);
}


//------------------------------------------------------------------------------


template<typename T>
CellularAutomaton<T>& CellularAutomaton<T>::operator++()
{
    for (int row=0; row<this->get_size(); ++row) {
	for (int col=0; col<this->get_size(); ++col) {
	    // check cells surrounding it in modulo "size"
	    this->update_cell(row, col);
	}
    }
    // set timeout function for visualization
    std::this_thread::sleep_for(std::chrono::milliseconds(this->timer));
    return *this;
}
