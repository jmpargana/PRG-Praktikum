/** 
 * PRG-Praktikum
 * Author: Joao Pargana 6807391
 * 
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//------------------------------------------------------------------------------


/**
 * Matrix template
 * this class contains a template for a matrix with all 
 * its needed methods (all the operator overloads)
 * currently the template is commented feature is commented,
 * since for this exercise we have a specific type
 * 
 * @param matrix is a two dimensional vector
 * 
 */

// template <typename T>
class Matrix {

public:    
    // all constructors
    Matrix();
    Matrix(unsigned);		// square matrix
    Matrix(unsigned, unsigned);	// regular matrix

    // constructor with all elements
    Matrix(std::vector<std::vector<bool> >&);
    Matrix(std::vector<std::vector<bool> >&&); // move with elements

    // copy and assignment constructors
    Matrix(Matrix&);		      // copy constructor
    Matrix(Matrix&&);
    
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

    // extras
    Matrix power(double);
    

    // getter for vector
    std::vector<bool>& operator[](unsigned);
    const std::vector<bool>& operator[](unsigned) const;

    // main mathods
    unsigned get_row_size() const;	// getter functions
    unsigned get_col_size() const;	// for matrix size

    bool square();		// square checker

    
private:
    std::vector<std::vector<bool> > matrix;
    
};


// input and output streams
// template<typename T>
std::ostream& operator<<(std::ostream&, const Matrix&);

// template<typename T>
std::istream& operator>>(std::istream&, Matrix&);

// input and output file streams
// template<typename T>
std::ofstream& operator<<(std::ofstream&, const Matrix&);

// template<typename T>
std::ifstream& operator>>(std::ifstream&, Matrix&);


#endif
