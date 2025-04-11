#include <iostream>
#include <vector>
#include <string>
#include <cstddef> // for size_t

#include "sha256.h"
#include "base64.h"
#include "timer.h"

int main(){
    Timer sha256Timer;
    Timer base64Timer;

    std::string input;
    std::cout << "Enter input: ";
    std::getline(std::cin, input);
    std::vector<uint8_t> data(input.begin(), input.end());

    size_t* hashLen = new size_t(0);
    sha256Timer.start();
    uint8_t* hash = SHA256::hash(data.data(), data.size(), hashLen);
    sha256Timer.stop();

    size_t* b64len = new size_t(0);
    base64Timer.start();
    char* encoded = Base64::Encode(hash, *hashLen, b64len);
    base64Timer.stop();

    std::cout << std::endl;
    std::cout << "Base64 Encoded: " << encoded << std::endl;

    std::cout << "\nSHA256:\n";
    sha256Timer.printElapsedTimeAndCycles();
    std::cout << "\nBase64:\n";
    base64Timer.printElapsedTimeAndCycles();

    return 0;
}

// interesting: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm
