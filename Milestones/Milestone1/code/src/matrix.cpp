/**
 * PRG-Praktikum
 * Author: Joao Pargana 6807391
 *
 * Matrix class implementation will be needed throughout the project
 *
 */


#include "../include/matrix.hpp"


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix() { };	// empty initialization


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(unsigned n)    
    :row_size{n}, col_size{n},
     matrix{n, std::vector<T>(n)} { }
     // matrix construct to build n-square matrix of any type


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(unsigned n, unsigned m)
    :row_size{n}, col_size{m},
     matrix{n, std::vector<T>(m)} { }
     // matrix construct to build n*m matrix of any type


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> >& elements)
    : matrix{elements} { }
// create matrix with given elements


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T> >&& elements)
    : matrix{std::move(elements)} { }
// move elements and initialize matrix with them


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(Matrix& to_copy)
    : matrix{to_copy.matrix} { }
// matrix construct to copy matrix of any type


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::Matrix(Matrix&& to_copy)
    : matrix{std::move(to_copy.matrix)} { }


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& to_assign)
// matrix assignment operation overload template
{
    matrix = to_assign.matrix;
    return *this;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& to_move) noexcept
// matrix move operation overload assignment template
{
    matrix = std::move(to_move.matrix);
    return *this;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T>::~Matrix()
// matrix default destructor template
// its not needed, since vectors already and unsigned integers
// already have destructors by themselves which get called
// automatically when leaving scope
{
    
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& second)
// sum of matrix template
{
    // error detection
    if (this->row_size != second.get_row_size() ||
	this->col_size != second.get_col_size())
	throw std::runtime_error("Matrix sizes don't match");

    // iteration without iterators for easy subscription
    Matrix<T> sum(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    sum[i][j] = this->matrix[i][j] + second[i][j];
	}
    }
    return sum;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& second)
// matrix difference template
{
    // error detection
    if (this->row_size != second.get_row_size() ||
	this->col_size != second.get_col_size())
	throw std::runtime_error("Matrix sizes don't match");

    // iteration without iterators for easy subscription
    Matrix<T> difference(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    difference[i][j] = this->matrix[i][j] - second[i][j];
	}
    }
    return difference;
}


//------------------------------------------------------------------------------


// TODO: wrong implementation
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& second)
// matrix product template
{
    // error detection
    if (this->row_size != second.get_row_size() ||
	this->col_size != second.get_col_size())
	throw std::runtime_error("Matrix sizes don't match");

    // loop without iterators for easy subscription
    Matrix<T> product(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    product[i][j] = this->matrix[i][j] * second[i][j];
	}
    }
    return product;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::transpose()
// matrix transpose operation template
{
    Matrix<T> transposed_matrix(this->col_size, this->row_size);

    // get inverted values
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    transposed_matrix = this->matrix[j][i];
	}
    }
    return transposed_matrix;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::operator+(double scalar)
// matrix scalar product sum
{
    // error detection
    if (typeid(T) != typeid(scalar)) std::runtime_error("Impossible!\nDifferent types");

    Matrix<T> sum(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    sum[i][j] = this->matrix[i][j] + scalar;
	}
    }
    return sum;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::operator-(double scalar)
// matrix scalar difference
{
    // error detection
    if (typeid(T) != typeid(scalar)) std::runtime_error("Impossible!\nDifferent types");

    Matrix<T> difference(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    difference[i][j] = this->matrix[i][j] - scalar;
	}
    }
    return difference;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::operator*(double scalar)
// matrix scalar product
{
    // error detection
    if (typeid(T) != typeid(scalar)) std::runtime_error("Impossible!\nDifferent types");

    Matrix<T> product(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    product[i][j] = this->matrix[i][j] * scalar;
	}
    }
    return product;
}


//------------------------------------------------------------------------------



template<typename T>
Matrix<T> Matrix<T>::operator/(double scalar)
// matrix scalar division
{
    // error detection
    if (typeid(T) != typeid(scalar)) std::runtime_error("Impossible!\nDifferent types");

    Matrix<T> division(this->row_size, this->col_size);
    for (unsigned i=0; i<this->row_size; i++) {
	for (unsigned j=0; j<this->col_size; j++) {
	    division[i][j] = this->matrix[i][j] / scalar;
	}
    }
    return division;
}


//------------------------------------------------------------------------------


template<typename T>
Matrix<T> Matrix<T>::power(double value)
{
    if (value<1) throw std::runtime_error("invalid operation");
    if (value==1) return *this;

    // TODO: continue implementation

    return *this;
}


//------------------------------------------------------------------------------


template<typename T>
std::vector<T>& Matrix<T>::operator[](unsigned index)
// subscription operation overload
{
    // error detection
    if (index>this->row_size || index<0)
    	throw std::runtime_error("Out of range");

    return this->matrix[index];	// second subscription should work as expected
}


//------------------------------------------------------------------------------


// usefull public functions to access outside class
template<typename T>
unsigned Matrix<T>::get_row_size() { return row_size; }

template<typename T>
unsigned Matrix<T>::get_col_size() { return col_size; }


//------------------------------------------------------------------------------


// might be usefull in future
template<typename T>
bool Matrix<T>::square() { return (row_size == col_size); }


//------------------------------------------------------------------------------


template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
// overload output stream to print matrix in form of:
// matrix[0][0] matrix[o][1] ... matrix[o][j] \n (newline)
// matrix[1][0] ... \n
// ... \n
// matrix[i][0] ... \n
{
    for (auto& row : matrix.matrix) {
	for (auto& elem: row) {
	    os << elem;
	}
	os << std::endl;
    }
    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
// overload input stream operator
{
    
    return is;
}


//------------------------------------------------------------------------------


template<typename T>
std::ofstream& operator<<(std::ofstream& os, const Matrix<T>& matrix)
// overload output file stream operator to write in files
{

    return os;
}


//------------------------------------------------------------------------------


template<typename T>
std::ifstream& operator>>(std::ifstream& is, Matrix<T>& matrix)
// overload input file stream operator to read files
{
    
    return is;
}


template class Matrix<float>;
// template class Matrix<int>;
