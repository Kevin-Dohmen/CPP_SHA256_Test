#include <iostream>
#include <cstddef> // for size_t
#include <bitset>
#include <ctime>
#include <cstdlib> // for rand() and srand()
#include <chrono> // for std::chrono::high_resolution_clock
#include <fstream> // for file operations
#include <filesystem>

#include "sha256.h"
#include "base64.h"
#include "binOps.h"
#include "cycleCounter.h"
#include "timer.h"

int main(){

    Timer sha256Timer;
    Timer base64Timer;

    std::string input = " ";
    std::vector<uint8_t> data(input.begin(), input.end());

    sha256Timer.start();
    std::vector<uint8_t> hash = SHA256::hash(data);
    sha256Timer.stop();
    

    size_t* outputLength = new size_t(0);

    base64Timer.start();
    char* encoded = Base64::Encode(hash.data(), hash.size(), outputLength);
    base64Timer.stop();


    std::cout << "SHA256 Hash: ";
    for (size_t i = 0; i < hash.size(); i++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    std::cout << std::endl;
    std::cout << "Base64 Encoded: " << encoded << std::endl;

    std::cout << "\nSHA256:\n";
    sha256Timer.printElapsedTimeAndCycles();
    std::cout << "\nBase64:\n";
    base64Timer.printElapsedTimeAndCycles();

    return 0;
}

// interesting: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm
