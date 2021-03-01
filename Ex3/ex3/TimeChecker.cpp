#include <iostream>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include <chrono>
#include <stack>
#include "Matrix.hpp"

#define INP_ERR "Invalid input."
#define INV_NUM_ARG "Invalid number of arguments.\nOnly one argument requested."

typedef typename std::chrono::duration<double> dur;
static int checkInp(char* inp, int &castedInp);
static void printFcn(int size, dur t1, dur t2, dur t3, dur t4);
static void tic();
static dur toc();

/**
 * main function.
 */
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << INV_NUM_ARG << std::endl;
        return 1;
    }
    int size;
    if(checkInp(argv[1], size) == 1)
    {
        return 1;
    }

    Eigen::MatrixXd eigenMatrix1 = Eigen::MatrixXd::Random(size, size);
    Eigen::MatrixXd eigenMatrix2 = Eigen::MatrixXd::Random(size, size);

    std::vector<int> vec(size * size, 1);
    Matrix<int> matrix1((unsigned int)size, (unsigned int)size, vec);
    Matrix<int> matrix2((unsigned int)size, (unsigned int)size, vec);

    tic();
    eigenMatrix1 * eigenMatrix2;
    dur eigenMult = toc();
    tic();
    eigenMatrix1 + eigenMatrix2;
    dur eigenSum = toc();
    tic();
    matrix1 * matrix2;
    dur myMatrixMult = toc();
    tic();
    matrix1 + matrix2;
    dur myMatrixSum = toc();
    printFcn(size, eigenMult, eigenSum, myMatrixMult, myMatrixSum);
    return 0;
}

/**
 * Check legal input.
 * @param inp user's input
 * @param castedInp storage for user's input.
 * @return 0 upon success, 1 in case logical or invalid input.
 */
static int checkInp(char* inp, int &castedInp)
{
    std::stringstream sStream;

    sStream << inp;
    sStream >> castedInp;
    if(sStream.rdbuf()->in_avail() != 0)
    {
        std::cout << INP_ERR << std::endl;
        return 1;
    }
    if(castedInp > 500 || castedInp < 1)
    {
        std::cout << INP_ERR << std::endl;
        return 1;
    }
    return 0;
}


static std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;

/**
 * start ticking clock!
 */
static void tic()
{
    tictoc_stack.push(std::chrono::system_clock::now());
}

/**
 * @return time that elapsed since last tick.
 */
static dur toc()
{
    dur elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
    tictoc_stack.pop();
    return elapsed_seconds;
}

/**
 * print given data to user's screen.
 * @param size matrix size.
 * @param t1 time val
 * @param t2 time val
 * @param t3 time val
 * @param t4 time val
 */
static void printFcn(int size, dur t1, dur t2, dur t3, dur t4)
{
    std::cout << "size " << size << std::endl;
    std::cout << "eigen mult " << t1.count() << std::endl;
    std::cout << "eigen add " << t2.count() << std::endl;
    std::cout << "matlib mult " << t3.count() << std::endl;
    std::cout << "matlib add " << t4.count() << std::endl;
}
