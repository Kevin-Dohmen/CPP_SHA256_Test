#include <iostream>
#include <cstddef> // for size_t
#include <bitset>
#include <ctime>
#include <cstdlib> // for rand() and srand()
#include <chrono> // for std::chrono::high_resolution_clock
#include <fstream> // for file operations
#include <filesystem>

#include "base64.h"
#include "binOps.h"
#include "cycleCounter.h"

int main(){

    size_t dataLen = 5000000;
    unsigned char* data = new unsigned char[dataLen];

    srand(static_cast<unsigned>(time(0)));
    for (size_t i = 0; i < dataLen; i++) {
        data[i] = static_cast<unsigned char>(rand() % 256);
    }

    size_t* outputLen = new size_t(0);

    auto est = std::chrono::high_resolution_clock::now();
    uint64_t es = CycleCounter::rdtsc();
    char* whee = Base64::Encode(data, dataLen, outputLen);
    uint64_t ee = CycleCounter::rdtsc();
    auto eet = std::chrono::high_resolution_clock::now();

    std::cout << "Encoded length: " << *outputLen << std::endl;

    // for (size_t i = 0; i < *outputLen; i++){
    //     std::cout << whee[i];
    // }

    std::cout << std::endl;

    size_t* outputLen2 = new size_t(0);

    auto dst = std::chrono::high_resolution_clock::now();
    uint64_t ds = CycleCounter::rdtsc();
    volatile unsigned char* whaa = Base64::Decode(whee, *outputLen, outputLen2);
    uint64_t de = CycleCounter::rdtsc();
    auto det = std::chrono::high_resolution_clock::now();

    std::cout << "Decoded Length: " << *outputLen2 << std::endl;

    // for (size_t i = 0; i < *outputLen2; i++) {
    //     std::cout << std::bitset<8>(whaa[i]) << (data[i] == whaa[i] ? "" : " ##") << std::endl;
    // }

    bool foundMismatch = false;
    for (size_t i = 0; i < *outputLen2; i++) {
        if (data[i] != whaa[i]) {
            std::cout << "Mismatch at index " << i << ": " << std::bitset<8>(data[i]) << " != " << std::bitset<8>(whaa[i]) << std::endl;
            foundMismatch = true;
        }
    }

    if (!foundMismatch) {
        std::cout << "No mismatches found!" << std::endl;
    }

    std::cout << std::endl;

    auto eDuration = std::chrono::duration_cast<std::chrono::duration<double>>(eet - est);
    auto dDuration = std::chrono::duration_cast<std::chrono::duration<double>>(det - dst);

    std::cout << "Encode cycles: " << ee - es << std::endl;
    std::cout << "Decode cycles: " << de - ds << std::endl;
    std::cout << "Encode time: " << eDuration.count() * 1000 << " ms" << std::endl;
    std::cout << "Decode time: " << dDuration.count() * 1000 << " ms" << std::endl;

    if (!std::filesystem::exists("./tmp")) {
        std::filesystem::create_directory("./tmp");
    }

    std::ofstream outFile("./tmp/the_great_random_b64.txt", std::ios::binary);

    if (outFile.is_open()) {
        outFile.write(whee, *outputLen);
        outFile.close();
        std::cout << "Encoded data written to the_great_random_b64.txt" << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }

    // cleanup
    delete[] whee;
    delete[] whaa;
    delete outputLen;
    delete outputLen2;

    return 0;
}

// interesting: https://www.simplilearn.com/tutorials/cyber-security-tutorial/sha-256-algorithm
