#include <iostream>
#include <cstddef> // for size_t
#include <bitset>

#include "base64.h"

int main(){
    Base64 b64;

    unsigned char* data = new unsigned char[6]{
        0b00100100,
        0b00010000,
        0b01000011,
        0b00000100,
        0b00010000,
        0b01100000
    };

    size_t* outputLen = new size_t(0);
    char* whee = b64.Encode(data, 6, outputLen);
    std::cout << "outputLen: " << *outputLen << std::endl;

    for (size_t i = 0; i < *outputLen; i++){
        std::cout << whee[i];
    }

    std::cout << std::endl;

    size_t* outputLen2 = new size_t(0);
    unsigned char* whaa = b64.Decode(whee, *outputLen, outputLen2);
    std::cout << "outputLen2: " << *outputLen2 << std::endl;

    for (size_t i = 0; i < *outputLen2; i++) {
        std::cout << std::bitset<8>(whaa[i]) << std::endl;
    }

    // cleanup
    delete[] whee;
    delete[] whaa;
    delete outputLen;
    delete outputLen2;

    return 0;
}

// interesting: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm
