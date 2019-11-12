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
#include <string>


//------------------------------------------------------------------------------


std::string menu = "\
Menu:\n\n\
\t1 -> Create random two dimensional Array\n\
\t2 -> Create long one dimensional Array\n\
\t3 -> Save to long one dimensional Array\n\
\t4 -> Print result\n\
\t0 -> Exit\n\
";
char input;
std::array<std::array<int, 30>, 30> matrix;
std::array<int, 30*30> matrix_verbose;


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


std::array<int, 30*30> aufgabe1a2(
				  std::array<std::array<int, 30>, 30>& data,
				  unsigned int size)
// copy data from two-dimensional static array to one-dimensional dynamic array
// of chars to simplify printing process
{
    std::array<int, 30*30> matrix_verbose;

    for (unsigned int row=0; row<size; ++row) {
	for (unsigned int col=0; col<size; ++col) {
	    matrix_verbose[row+col] = data[col][row];
	}
    }
    return matrix_verbose;
}


//------------------------------------------------------------------------------


void aufgabe1a3(std::array<int, 30*30>& data, unsigned int size)
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

     while (true) {
	 std::cout << menu << std::endl;
	 std::cin >> input;

	 switch (input) {
	 case '1': matrix = aufgabe1a1(size); break;
	 case '2': continue;
	 case '3': matrix_verbose = aufgabe1a2(matrix, size); break;
	 case '4': aufgabe1a3(matrix_verbose, size); break;
	 case '0': exit(0);
	 default: continue;
	 }
     }

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
