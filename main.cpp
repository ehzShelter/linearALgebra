#include "Utilities.hpp"
#include "hillCipher.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

typedef double mType;


int main(int argc, char* argv[])
{
    const std::string msg = "Proper usage: \"./MatrixDeterminant -f filename\" ";

    if (argc < 3 || argc > 3) {
        std::cout << msg;
        std::cout << std::endl;
        return -1;
    }

    // main execution Block
    try {
        if (argc == 3) {
            if (std::string(argv[1]) == "-f") {
                std::ifstream inputFile(argv[2]);

                if (inputFile.is_open()) {
                    size_t dimension{};
                    mType determinant{};
                    // first value in the file == matrix dimension
                    // inputFile >> dimension;
                    std::cin >> dimension;

                    util::Matrix<mType> matrix = util::makeMatrix<mType>(dimension, dimension);

                    // read matrix from file
                    // util::readMatrix(matrix, inputFile);
                    util::readMatrix(matrix, std::cin);

                    std::cout << "M = " << std::endl;
                    util::printMatrix(matrix);

                    std::ofstream tmp("results.txt", std::ios_base::app);
                    tmp << "M = " << std::endl;
                    util::printMatrix(matrix, tmp);

                    Hill chiper;

                    // LAPLACE EXPANSION
                    determinant = chiper.laplaceExpansion(matrix);
                    std::cout << "LaplaceExpansion::det(M) = " << determinant << std::endl;
                    tmp << "LaplaceExpansion::det(M) = " << determinant << std::endl;

                }
                // couldn't open file specified as second parameter of program invocation
                else {
                    std::cerr << "Couldn't open file : " << argv[2];
                    std::cout << std::endl;
                }
            }
            // wrong first argument -> show error message
            else {
                std::cerr << msg;
                std::cout << std::endl;
            }
        } else {
            //@ todo = proccess keyboard input
            std::cerr << msg;
            std::cout << std::endl;
        }
    } catch (...) {
        std::cerr << "something went wrong " << std::endl;
    }
}
