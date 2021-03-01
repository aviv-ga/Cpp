#include <iostream>
#include <fstream>
#include "Arenstorf.h"
#include <sstream>

/** Messages to user */
#define POS_X_MSG "Enter initial pos x:\n"
#define POS_Y_MSG "Enter initial pos y:\n"
#define VEL_X_MSG "Enter initial vel x:\n"
#define VEL_Y_MSG "Enter initial vel y:\n"
#define TIME_MSG "Enter total time T:\n"
#define NUM_STEPS_MSG "Enter num of steps n:\n"
#define NUM_OF_STEPS_TO_SAVE_MSG "Enter num of steps to save:\n"
#define FILE_ERROR_MSG "Could not open file.\n Please enter a valid path.\n"
#define LOGICAL_ERR_MSG_1 "Logical input error! Make sure T, n, or m are positive!\n"
#define LOGICAL_ERR_MSG_2 "m can not be greater than n!\n"
#define INV_NUM_ARG_MSG "Invalid number of arguments inserted!\n"
#define INV_ARG_MSG "Invalid argument inserted!\n"
#define FILE_FORMAT_MSG "Invalid format of input file.\n"

/** DECLARATION */
static void userInput(const std::string msgArr1[], const std::string msgArr2[],
                      long double **inpArr1, int **inpArr2, bool &hasError, std::string &errMsg);
static void fileInput(long double **inpArr1, int **inpArr2, std::ifstream &inpFile,
                      bool &hasError, std::string &errMsg);
/**
 * main function.
 * Process user input and calculate Arenstorf course.
 */
int main(int argc, char* argv[])
{
    const std::string msgArr1[] = {POS_X_MSG, POS_Y_MSG, VEL_X_MSG, VEL_Y_MSG, TIME_MSG};
    const std::string msgArr2[] = {NUM_STEPS_MSG, NUM_OF_STEPS_TO_SAVE_MSG};

    long double posx, posy, velx, vely, t;
    int n, m;
    long double *inpArr1[] = {&posx, &posy, &velx, &vely, &t};
    int *inpArr2[] = {&n, &m};
    std::ofstream outFile;
    bool hasError = false;
    std::string errMsg;

    // User input:
    if (argc == 2)
    {
        outFile.open(argv[1]);
        if(outFile.fail())
        {
            std::cerr << FILE_ERROR_MSG;
            exit(1);
        }
        userInput(msgArr1, msgArr2, inpArr1, inpArr2, hasError, errMsg);
    }
    else if (argc == 3) // input via file.
    {
        std::ifstream inpFile;
        inpFile.open(argv[1]);
        if(inpFile.fail())
        {
            std::cerr << FILE_ERROR_MSG;
            return 1;
        }
        outFile.open(argv[2]);
        if(outFile.fail())
        {
            std::cerr << FILE_ERROR_MSG;
            inpFile.close();
            return 1;
        }
        fileInput(inpArr1, inpArr2, inpFile, hasError, errMsg);
    }
    else // num of program arguments is not 2 or 3.
    {
        std:: cerr << INV_NUM_ARG_MSG;
        return 1;
    }

    // Check if an error occured while reading input.
    if(hasError)
    {
        std::cerr << errMsg;
        outFile.close();
        return 1;
    }

    // logical input check.
    if(n < 0 || m < 0 || t < 0)
    {
        std::cerr << LOGICAL_ERR_MSG_1;
        return 1;
    }
    if(m > n)
    {
        std::cerr << LOGICAL_ERR_MSG_2;
        return 1;
    }

    auto unsignedN = (unsigned int)n;
    auto unsignedM = (unsigned int)m;
    long double dt = t / unsignedN;

    ArenstorfPoint init(posx, posy, velx, vely);
    Arenstorf::computeArenstorf(init, unsignedN, unsignedM, dt, outFile);

    outFile.close();
    return 0;
}


/**
 * Deal with user input for arenstorf course parameters.
 * @param msgArr1 array of msgs to the user.
 * @param msgArr2 array of msgs to the user.
 * @param inpArr1 array of pointers to place inputs
 * @param inpArr2 array of parameters to place inputs
 * @param hasError true if an error occured before, false otherwise.
 * @param errMsg first error to come up, its msg inserted here.
 */
static void userInput(const std::string msgArr1[], const std::string msgArr2[],
                      long double **inpArr1, int **inpArr2, bool &hasError, std::string &errMsg)
{
    std::string input;
    for(int i = 0; i < 5; i++)
    {
        std::cout << msgArr1[i];
        std::cin >> input;
        std::stringstream inpStream(input);
        // make sure stream is empty!
        if(!(inpStream >> *inpArr1[i]) || inpStream.rdbuf()->in_avail() != 0)
        {
            if(!hasError)
            {
                errMsg = INV_ARG_MSG;
                hasError = true;
            }
        }
        inpStream.str(std::string());
    }

    for(int i = 0; i < 2; i++)
    {
        std::cout << msgArr2[i];
        std::cin >> input;
        std::stringstream inpStream(input);
        if(!(inpStream >> *inpArr2[i]) || inpStream.rdbuf()->in_avail() != 0)
        {
            if(!hasError)
            {
                errMsg = INV_ARG_MSG;
                hasError = true;
            }
        }
    }
}

/**
 * Get input from file.
 * @param inpArr1 array of pointers to place inputs
 * @param inpArr2 array of pointers to place inputs
 * @param inpFile reference to a file stream
 * @param hasError true if an error occured, false otherwise.
 * @param errMsg contains the matching msg to the first err which has occured.
 */
static void fileInput(long double **inpArr1, int **inpArr2, std::ifstream &inpFile,
                      bool &hasError, std::string &errMsg)
{
    std::string input;
    std::string line;
    int numOfInput = 0;

    // first line extraction:
    std::getline(inpFile, line);
    std::stringstream lineStream(line);
    while(getline(lineStream, input, ','))
    {
        std::stringstream parsedInp(input);
        if (numOfInput < 4)
        {
            parsedInp >> *inpArr1[numOfInput];
            if (parsedInp.rdbuf()->in_avail() != 0)
            {
                if (!hasError)
                {
                    errMsg = INV_ARG_MSG;
                    hasError = true;
                }
            }
            numOfInput++;
        }
        else
        {
            if (!hasError)
            {
                errMsg = FILE_FORMAT_MSG;
                hasError = true;
            }
            break;
        }
    }
    if(line.back() == ',')
    {
        if (!hasError)
        {
            errMsg = FILE_FORMAT_MSG;
            hasError = true;
        }
    }

    numOfInput = 0;
    std::getline(inpFile, line);
    lineStream = std::stringstream(line);
    // second line extraction:
    while(getline(lineStream, input, ','))
    {
        std::stringstream parsedInp(input);
        if (numOfInput < 3)
        {
            if(numOfInput == 0)
            {
                parsedInp >> *inpArr1[4];
            }
            else
            {
                parsedInp >> *inpArr2[numOfInput - 1];
            }
            if (parsedInp.rdbuf()->in_avail() != 0)
            {
                if (!hasError)
                {
                    errMsg = INV_ARG_MSG;
                    hasError = true;
                }
            }
            numOfInput++;
        }
        else
        {
            if (!hasError)
            {
                errMsg = FILE_FORMAT_MSG;
                hasError = true;
            }
            break;
        }
    }
    if(line.back() == ',')
    {
        if (!hasError)
        {
            errMsg = FILE_FORMAT_MSG;
            hasError = true;
        }
    }

    // check if there is more data in file
    if(inpFile >> line)
    {
        if (!hasError)
        {
            errMsg = FILE_FORMAT_MSG;
            hasError = true;
        }
    }
    inpFile.close();
}

