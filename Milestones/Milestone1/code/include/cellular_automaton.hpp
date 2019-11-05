/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * Aufgabe1 header file for c) d) and e) containing the cellular automaton class
 *
 */

#ifndef CELLULAR_AUTOMATON_HPP
#define CELLULAR_AUTOMATON_HPP


#include "../include/matrix.hpp"
#include <future>
#include <chrono>
#include <thread>


//------------------------------------------------------------------------------


class CellularAutomaton {
public:
    // constructors
    CellularAutomaton();		// default constructor
    CellularAutomaton(const int);
    CellularAutomaton(const int, const int);
    CellularAutomaton(const int, const int, const int);

    // constructor with elements
    CellularAutomaton(std::vector<std::vector<bool> >&);
    CellularAutomaton(std::vector<std::vector<bool> >&&);

    // copy constructor
    CellularAutomaton(CellularAutomaton&);

    // move constructor
    CellularAutomaton(CellularAutomaton&&);

    // assignment operator
    CellularAutomaton& operator=(const CellularAutomaton&);

    // move assignment operator
    CellularAutomaton& operator=(CellularAutomaton&&) noexcept;

    // destructors
    ~CellularAutomaton() { }

    // subscript operation overload
    std::vector<bool>& operator[](int);
    const std::vector<bool>& operator[](int) const;

    // time lapse with operator++ overloading 
    CellularAutomaton& operator++();
    CellularAutomaton& operator+=(int);

    int get_rows() const;
    int get_cols() const;
    Matrix get_matrix();
    void update_cell(int, int);	// check surrounding cells
    
    
private:
    Matrix current, next;
    int timer;
    
};


//------------------------------------------------------------------------------


// output stream
std::ostream& operator<<(std::ostream&, CellularAutomaton const&);

// input stream
std::istream& operator>>(std::istream&, CellularAutomaton&);


// output file stream
std::ofstream& operator<<(std::ofstream&, CellularAutomaton const&);

// input file stream
std::ifstream& operator>>(std::ifstream&, CellularAutomaton&);


#endif
