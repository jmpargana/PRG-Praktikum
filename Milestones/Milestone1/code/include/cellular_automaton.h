/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * Aufgabe1 header file for c) d) and e) containing the cellular automaton class
 *
 */


#include <iostream>
#include <fstream>
#include <future>
#include <chrono>
#include <thread>


//------------------------------------------------------------------------------


template<typename T>
class CellularAutomaton {
public:

    class Proxy {
    public:
	Proxy(T* _array) : array{_array} { }
	T& operator[](int index) { return array[index]; }
	
    private:
	T* array;
    };

    
    // constructors
    CellularAutomaton()		// default constructor
	: current{new T[30][30]}, next{new T[30][30]}, size{30}, timer{1} { } 
    CellularAutomaton(const int _size)
	: current{new T[_size][size]}, next{new T[_size][size]},
	  size{_size}, timer{1} { }
    CellularAutomaton(const int _size, int timer)
	: current{new T[_size][size]}, next{new T[_size][size]},
	  size{_size}, timer{timer} { }

    // copy constructor
    CellularAutomaton(CellularAutomaton&);

    // move constructor
    

    // assignment operator
    CellularAutomaton& operator=(const CellularAutomaton&);

    // move assignment operator
    CellularAutomaton& operator=(CellularAutomaton&&) noexcept;

    // destructors
    ~CellularAutomaton() { delete[] next; delete[] current; }

    // time lapse with operator++ overloading 
    CellularAutomaton& operator++();
    CellularAutomaton& operator+=(int);

    // subscript operator for user
    Proxy operator[](int index) { return Proxy(current[index]); }
    
    int get_size() { return this->size; }
    void update_cell(int, int);	// check surrounding cells
    
    
private:
    T** current;
    T** next;
    int size;
    int timer;
    
};


//------------------------------------------------------------------------------


// output stream
template<typename T>
std::ostream& operator<<(std::ostream&, const CellularAutomaton<T>&);

// input stream
template<typename T>
std::istream& operator>>(std::istream&, CellularAutomaton<T>&);


// output file stream
template<typename T>
std::ofstream& operator<<(std::ostream&, const CellularAutomaton<T>&);

// input file stream
template<typename T>
std::ifstream& operator>>(std::ifstream&, CellularAutomaton<T>&);
