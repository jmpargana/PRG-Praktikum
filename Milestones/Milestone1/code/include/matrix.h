/** 
 * PRG-Praktikum
 * Author: Joao Pargana 6807391
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//------------------------------------------------------------------------------


template <typename T>
class Matrix {

    // all constructors
    Matrix();
    Matrix(unsigned);		// square matrix
    Matrix(unsigned, unsigned);	// regular matrix

    // copy and assignment constructors
    Matrix(Matrix&);		      // copy constructor
    Matrix& operator=(const Matrix&); // assignment operator

    // move constructor and move operator
    Matrix& operator=(Matrix&&) noexcept;
    
    // destruction constructors
    ~Matrix();

    // operations
    Matrix operator+(Matrix&);	// addition
    Matrix operator-(Matrix&);	// subtraction
    Matrix operator*(Matrix&);	// multiplication
    Matrix transpose();		// verbose

    // all scalar operations
    Matrix operator+(double);
    Matrix operator-(double);
    Matrix operator*(double);
    Matrix operator/(double);

    // getter for vector
    std::vector<T>& operator[](int);

    // main mathods
    unsigned get_row_size();	// getter functions
    unsigned get_col_size();	// for matrix size

    bool square();		// square checker

    
private:
    std::vector<std::vector<T> > matrix;
    unsigned row_size, col_size;
    
};


// input and output streams
template<typename T>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);

template<typename T>
std::istream& operator>>(std::istream&, Matrix<T>&);

// input and output file streams
template<typename T>
std::ofstream& operator<<(std::ofstream&, const Matrix<T>&);

template<typename T>
std::ifstream& operator>>(std::ifstream&, Matrix<T>&);
