/**
 * PRG-Praktikum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3 
 *
 * Aufgabe 1 a) und b)
 *
 */


#include <iostream>
#include <cstdlib>
#include <array>


//------------------------------------------------------------------------------


std::array<std::array<int, 30>, 30> aufgabe1a1(unsigned size)
// function to create a two-dimensional array initialized with random ints
{
    // int** matrix = nullptr;
    // matrix = new int*[size];

    std::array<std::array<int, 30>, 30> matrix;

    for (unsigned rol=0; rol<size; ++rol) {
	for (unsigned col=0; col<size; ++col) {
	    // generate random value between [0, 9]
	    matrix[rol][col] = (std::rand() % 10); 
	}
    }
    return matrix;
}


//------------------------------------------------------------------------------


const char* aufgabe1a2(std::array<std::array<int, 30>, 30> data,
		       unsigned int size)
// copy data from two-dimensional static array to one-dimensional dynamic array
// of chars to simplify printing process
{
    char *matrix_verbose = new char[size*size+size];

    for (unsigned int rol=0; rol<size; ++rol) {
	for (unsigned int col=0; col<size; ++col) {
	    matrix_verbose[rol+col] = (char)data[rol][col];
	}
    }
    return matrix_verbose;
}


//------------------------------------------------------------------------------


void aufgabe1a3(const char* data, unsigned int size)
// output string intercalated by new line characters
{
    for (unsigned int rol=0; rol<size; ++rol) {
	for (unsigned int col=0; col<size; ++col) {
	    std::cout << data[rol+col];
	}
	std::cout << std::endl;
    }
}


//------------------------------------------------------------------------------


int main(int argc, const char *argv[])
 try
 {
     unsigned int size = 30;
     std::array<std::array<int, 30>, 30> matrix = aufgabe1a1(size);
     const char* matrix_verbose = aufgabe1a2(matrix, size);
     aufgabe1a3(matrix_verbose, size);
     return 0;
 }

 catch (std::exception& e)
 {
     std::cout << e.what() << std::endl;
     return 1;
 }

 catch (...)
 {
     std::cerr << "Something failed" << std::endl;
     return 2;
 }
