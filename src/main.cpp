#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstddef> // for size_t

#include "sha256.h"
#include "base64.h"
#include "timer.h"

int main(){
    Timer sha256Timer;
    Timer base64Timer;

    std::string filePath = "./tmp/inpt.txt";

    std::ifstream inFile;
    inFile.open(filePath, std::ios::binary);

    inFile.seekg(0, std::ios::end);
    std::streamsize fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    uint8_t* data = new uint8_t[fileSize];
    if (!inFile.read(reinterpret_cast<char*>(data), fileSize)) {
        std::cerr << "Error reading file. (" << filePath << ")" << std::endl;
        return 1;
    }

    inFile.close();

    size_t* hashLen = new size_t(0);
    sha256Timer.start();
    uint8_t* hash = SHA256::hash(data, fileSize, hashLen);
    sha256Timer.stop();

    size_t* b64len = new size_t(0);
    base64Timer.start();
    char* encoded = Base64::Encode(hash, *hashLen, b64len);
    base64Timer.stop();

    std::cout << std::endl;
    std::cout << "SHA256 hash (Base64): " << encoded << std::endl;

    std::cout << "\nSHA256:\n";
    sha256Timer.printElapsedTimeAndCycles();
    std::cout << "\nBase64:\n";
    base64Timer.printElapsedTimeAndCycles();

    return 0;
}

// interesting: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm
