//
// Created by Aviv on 23/01/2018.
//

#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP

#include <vector>
#include <ostream>
#include "Complex.h"

#define RANGE_ERR "Inserted row or column is out of matrix bound!"
#define LOGICAL_ERR "Matrix dimension must be the same! "

template <class T>
/**
 * Definition of generic matrices.
 * @tparam T type of data that matrices hold.
 */
class Matrix
{
public:
    /**
     * Default constructor. Create 1X1 matrix with default type value.
     */
    Matrix() : _rows(1), _cols(1) , _members(1, T()) {};

    /**
     * Constructor of Matrix with given dimension. Initialize values with its default type value.
     * @param rows number os rows.
     * @param cols number of columns.
     */
    Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols), _members(rows * cols, T()) {};

    /**
     * Constructor of matrix with given dimension and given data.
     * @param rows number of rows.
     * @param cols number of columns.
     * @param cells vector data structure which holds data to insert.
     */
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T> &cells) :
            _rows(rows), _cols(cols), _members(cells)
    {
        if(cells.size() != rows * cols)
        {
            throw std::logic_error(LOGICAL_ERR);
        }
    }

    /**
     * Copy constructor.
     * @param rhs A given matrix to copy.
     */
    Matrix(const Matrix<T> &rhs)
    {
        _rows = rhs._rows;
        _cols = rhs._cols;
        _members = std::vector<T>(rhs._members);
    };

    /**
     * Move constructor.
     * @param rhs
     */
    Matrix(Matrix<T> && rhs) noexcept
    {
        _rows = rhs._rows;
        _cols = rhs._cols;
        std::swap(_members, rhs._members);
    }

    /**
     * Default destructor.
     */
    virtual ~Matrix() = default;

    /**
     * Print a given matrix to a given output stream.
     * @param os output stream.
     * @param matrix A given matrix to print to output stream..
     * @return output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        for(int row = 1; row <= matrix._rows; row++)
        {
            for(int col = 1; col <= matrix._cols; col++)
            {
                os << matrix.operator()(row, col) << "\t";
            }
            os << std::endl;
        }
        return os;
    }

    /**
     * Boolean operator to compare equality between two matrices.
     * @param rhs A given matrix.
     * @return true iff the matrices are equal, false otherwise.
     */
    bool operator==(const Matrix<T> &rhs) const
    {
        if(!hasSameDimension(rhs))
        {
            return false;
        }
        for(int i = 0; i < _members.size(); i++)
        {
            if(_members[i] != rhs._members[i])
            {
                return false;
            }
        }
        return true;
    }

    /**
     * Compare between two matrices.
     * @param rhs compare matrix.
     * @return true if every element of the matrix is equivalent to its corresponding cell in rhs.
     */
    bool operator!=(const Matrix &rhs) const
    {
        return !(this->operator==(rhs));
    }

    /**
     * Default operator = for matrices.
     * @param rhs A given matrix.
     * @return a reference to a copy of the given matrix.
     */
    Matrix<T>& operator=(const Matrix<T> &rhs) = default;

    /**
     * Addition between two matrices.
     * @param rhs A given matrix.
     * @return A matrix which is the outcome of addition operator.
     */
    Matrix<T> operator+(const Matrix<T> &rhs)
    {
        if(!hasSameDimension(rhs))
        {
            throw std::logic_error(LOGICAL_ERR);
        }
        Matrix<T> newMatrix(_rows, _cols);
        for(unsigned int row = 1; row <= _rows; row++)
        {
            for (unsigned int col = 1; col <= _cols; col++)
            {
                newMatrix.operator()(row, col) = operator()(row, col) + rhs.operator()(row, col);
            }
        }
        return newMatrix;
    }

    /**
     * Subtraction between two matrices.
     * @param rhs A given matrix.
     * @return A matrix which is the outcome of subtration operator.
     */
    Matrix<T> operator-(const Matrix<T> &rhs)
    {
        if(!hasSameDimension(rhs))
        {
            throw std::logic_error(LOGICAL_ERR);
        }
        Matrix<T> newMatrix(_rows, _cols);
        for(unsigned int row = 1; row <= _rows; row++)
        {
            for (unsigned int col = 1; col <= _cols; col++)
            {
                newMatrix.operator()(row, col) = operator()(row, col) - rhs.operator()(row, col);
            }
        }
        return newMatrix;
    }

    /**
     * Multipy 2 matrices.
     * @param rhs A given Matrix
     * @return the outcome of the mult operation.
     */
    Matrix<T> operator*(const Matrix<T> &rhs)
    {
        if(_cols != rhs._rows)
        {
            throw std::logic_error(LOGICAL_ERR);
        }
        Matrix<T> newMatrix(_rows, rhs._cols);
        for(unsigned int i = 1; i <= _rows; i++)
        {
            for(unsigned int j = 1; j <= rhs._cols; j++)
            {
                T sum = 0;
                for(unsigned int k = 1; k <= _cols; k++)
                {
                    sum += operator()(i, k) * rhs.operator()(k, j);
                }
                newMatrix.operator()(i, j) = sum;
            }
        }
        return newMatrix;
    }

    /**
     * Return a reference to the data at the given row and column.
     * @param rows matrix's row.
     * @param cols matrix's column.
     * @return reference to searched data.
     */
    T& operator()(unsigned int rows, unsigned int cols)
    {
        if(rows > _rows || cols > _cols)
        {
            throw std::out_of_range(RANGE_ERR);
        }
        return _members[((rows - 1) * _rows) + (cols - 1)];
    }

    /**
     * get the value of the the data at row, col.
     * @param rows given row.
     * @param cols given column.
     * @return data at row, col - return as const value.
     */
    const T& operator()(unsigned int rows, unsigned int cols) const
    {
        if(rows > _rows || cols > _cols)
        {
            throw std::out_of_range(RANGE_ERR);
        }
        return _members[((rows - 1) * _rows) + (cols - 1)];
    }


    /**
     * Calculate the transpose matrix. Throw logic_error if matrix is not square.
     * @return transpose matrix.
     */
    Matrix<T> trans()
    {
        if(!isSquareMatrix())
        {
            throw std::logic_error(LOGICAL_ERR);
        }
        Matrix<T> newMatrix(_rows, _cols);
        for(int i = 1; i <= _rows; i++)
        {
            for (int j = 1; j <= _cols; j++)
            {
                newMatrix.operator()(j, i) = operator()(i, j);
            }
        }
        return newMatrix;
    }

    typedef typename std::vector<T>::const_iterator constIterator;
    /**
     * @return an iterator that points to the first member of the matrix.
     */
    constIterator begin()
    {
        return _members.cbegin();
    }

    /**
     * @return an iterator that points to the last member of the matrix.
     */
    constIterator end()
    {
        return _members.cend();
    }

    /**
     * Check if matrix is square.
     * @return true iff matrix is square, false otherwise.
     */
    bool isSquareMatrix ()
    {
        return _rows == _cols;
    }

    /**
     * Check if given matrix has same dimension.
     * @param rhs a given matrix.
     * @return true iff dimension of the matrices is the same, false otherwise.
     */
    bool hasSameDimension(const Matrix<T> &rhs) const
    {
        return (_rows == rhs._rows && _cols == rhs._cols);
    }

    /**
     * @return Matrix's number of rows.
     */
    unsigned int rows() const
    {
        return _rows;
    }

    /**
     * @return Matrix's number of cols.
     */
    unsigned int cols() const
    {
        return _cols;
    }

private:
    /** Matrix number of rows. */
    unsigned int _rows;
    /** Matrix number of columns */
    unsigned int _cols;
    /** Matrix data storage. Stored in vector strature. */
    std::vector<T> _members;

};

template<>
/**
 * Special implementation for transpose matrix with members of class Complex.
 * @return The transpose matrix of a matrix with complex members.
 */
Matrix<Complex> Matrix<Complex>::trans()
{
    if(!isSquareMatrix())
    {
        throw std::logic_error(LOGICAL_ERR);
    }
    Matrix<Complex> newMatrix(_rows, _cols);
    for(unsigned int i = 1; i <= _rows; i++)
    {
        for (unsigned int j = 1; j <= _cols; j++)
        {
            newMatrix.operator()(j, i) = operator()(i, j).conj();
        }
    }
    return newMatrix;
}

#endif //EX3_MATRIX_HPP
