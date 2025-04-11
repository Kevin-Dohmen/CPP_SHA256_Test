#ifndef SHA256_H
#define SHA256_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include "binOps.h"

class SHA256 {
public:
    SHA256() = delete;

    static uint8_t* hash(uint8_t* data, size_t dataLen, size_t* outLen);
};

#endif