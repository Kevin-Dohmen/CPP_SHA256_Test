#ifndef SHA256_H
#define SHA256_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include "binOps.h"

class SHA256 {
public:
    SHA256() = delete;

    static std::vector<uint8_t> hash(const std::vector<uint8_t> data);
};

#endif