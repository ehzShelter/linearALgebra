#ifndef _HILLCipher_HPP_
#define _HILLCipher_HPP_

#include "inputValidate.hpp"
#include "linuxUtil.hpp"
#include "mathUtilities.hpp"
#include <climits>
#include <iomanip>
#include <stdexcept>
#include <string>

class Hill {
private:
    std::string encryptText;

public:
    // setter and getter of string
    void setEncryptText(void);
    // get encryptText text
    std::string getEncryptText(void);
    void splittingOnTheFly(MathUtility::VV&, std::string&, size_t tokens, size_t split, MathUtility::VV&, MathUtility::VV&);

    void tokenizer(std::string vec);
    void statementToken(void);
};

// Implementation of hill class
void Hill::setEncryptText(void)
{
    termios process = linuxUtil::setNotEchoingMode();
    this->encryptText = ValidateInput::inputData("message", ".+");
    linuxUtil::goBack(process);
}

// get encryptText text
std::string Hill::getEncryptText(void)
{
    return this->encryptText;
}

void Hill::splittingOnTheFly(MathUtility::VV& dimVariantMat, std::string& vec, size_t tokens, size_t split, MathUtility::VV& holder, MathUtility::VV& keyMatrix)
{
    for (size_t i = 0; i < tokens; i++) {
        // dynamically splittingOnTheFly the string
        std::copy_n(vec.begin(), split, std::back_inserter(dimVariantMat[i]));
        // change one dimensional container to two dimensional container
        holder = MathUtility::dimensionVariantReturn(dimVariantMat[i], split);

        std::cout << "Before encipher : " << std::endl;
        MathUtility::dimensionVariantPrint(holder, split);

        // doing multiple with keyMatrix
        MathUtility::VV heal = MathUtility::doMultiple(keyMatrix, holder);

        std::cout << "After encrypted : " << std::endl;
        MathUtility::dimensionVariantPrint(heal, split);

        // dynamically decreease the vector by using C++ erasing Template
        vec.erase(vec.begin(), vec.begin() + split);
    }
}

void Hill::tokenizer(std::string vec)
{
    size_t tokens{};
    size_t spaceFact{};

    if (vec.size() % 2 == 0) {
        tokens = vec.size() / 2;
        spaceFact = vec.size();
    } else if ((vec.size() % 2 != 0) && MathUtility::isPrime(vec.size())) {
        vec.resize(vec.size() + 1);
        tokens = (vec.size() / 2);
        spaceFact = vec.size();
    } else {
        tokens = vec.size() / 3;
        spaceFact = vec.size();
    }

    std::cout << "TOkensize : " << tokens << std::endl;
    size_t split = (spaceFact % 2 == 0) ? 2 : 3;
    MathUtility::VV twoD(tokens);

    MathUtility::VV holder(split, MathUtility::V(split, 0));

    MathUtility::VV keyMatrix = MathUtility::makeMatrix(split, split);

    std::cout << "Enter your Matrix(" << split << "X" << split << ")"
              << ", which will be used for Crypto -->";
    std::cout << std::endl;

    MathUtility::readMatrix(keyMatrix, std::cin);

    std::cout << std::endl;

    splittingOnTheFly(twoD, vec, tokens, split, holder, keyMatrix);
}

void Hill::statementToken()
{
    try {
        setEncryptText();
        std::string vec = this->encryptText;
        std::cout << std::endl;
        tokenizer(vec);
    } catch (...) {
        std::cout << "Something wrong there ! " << std::endl;
    }
}

#endif
