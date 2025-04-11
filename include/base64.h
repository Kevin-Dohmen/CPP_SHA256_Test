#ifndef BASE64_H
#define BASE64_H

#include <cstddef>
#include <cstdint>

class Base64 {
private:
    inline static char ByteToChar(unsigned char b);
    inline static uint8_t CharToByte(char c);
public:
    static char* Encode(const uint8_t* data, size_t dataLen, size_t* outLen);
    static uint8_t* Decode(const char* data, size_t input_length, size_t* output_length);
};

#endif